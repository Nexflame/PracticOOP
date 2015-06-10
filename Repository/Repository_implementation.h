/*
 * Repository.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: Nexflame
 */

#ifndef REPOSITORY_I_REPOSITORY_H_
#define REPOSITORY_I_REPOSITORY_H_

#include <fstream>
#include <iostream>
#include "ProductRepository.h"

template <class T>
ProductRepository<T>::ProductRepository(std::string _fileNameProduct, std::string _fileNameQuantity) :
fileNameProduct(_fileNameProduct), fileNameQuantity(_fileNameQuantity)
{
    // TODO Auto-generated constructor stub
    std::thread load(&ProductRepository<T>::_loadAll, this);
    load.detach();
}

template <class T>
ProductRepository<T>::~ProductRepository()
{
    // TODO Auto-generated destructor stub
    for (auto& elem : objects)
        delete elem;
}

template <class T>
const std::string& ProductRepository<T>::getFileNameProduct() const
{
    return fileNameProduct;
}

template <class T>
void ProductRepository<T>::setFileNameProduct(const std::string& fileName)
{
    this->fileNameProduct = fileName;
}


template <class T>
const std::string& ProductRepository<T>::getFileNameQunatity() const
{
    return fileNameQuantity;
}

template <class T>
void ProductRepository<T>::setFileNameQuntity(const std::string& fileName)
{
    this->fileNameQuantity = fileName;
}

template <class T>
const std::vector<T>& ProductRepository<T>::getObjects() const
{
    return objects;
}

template <class T>
const int ProductRepository<T>::getSize() const
{
    return objects.size();
}

template <class T>
void ProductRepository<T>::addObject(T& newObject)
{
    if (!newObject)
        return;

     objects.push_back(newObject);
}

template <class T>
const T ProductRepository<T>::findByID(const int& ID) const
{
    for (auto& currObj : objects)
        if (currObj->getId() == ID)
            return currObj;

    return NULL;
}

template <class T>
void ProductRepository<T>::save()
{
    _saveAll();
}

template <class T>
void ProductRepository<T>::_loadAll()
{
    repo_mtx.lock();


    if (getFileNameProduct().empty())
        return;

    std::ifstream loaderProducts;
    loaderProducts.open(getFileNameProduct().c_str(), std::ifstream::in);

    bool stillReading = true;
    while (stillReading)
    {
        T obj = new Product;

        if (loaderProducts >> *obj)
            addObject(obj);
        else
            stillReading = false;
    }

    loaderProducts.close();

    // LOAD QUANTITY
    if (getFileNameQunatity().empty())
        return;

    std::ifstream loaderQuantity;
    loaderQuantity.open(getFileNameQunatity().c_str(), std::ifstream::in);

    stillReading = true;
    while (stillReading)
    {
        int id;
        int cantitate;
        if (loaderQuantity >> id >> cantitate)
        {
            T obiectCurent = findByID(id);
            obiectCurent->setQuantity(cantitate);
        }
        else
            stillReading = false;
    }
    loaderQuantity.close();

    repo_mtx.unlock();
}

template <class T>
void ProductRepository<T>::_saveAll()
{
    repo_mtx.lock();
    if (getFileNameProduct().empty())
        return;

    std::ofstream writerProducts;
    writerProducts.open(getFileNameProduct().c_str(), std::ofstream::out);

    if (!writerProducts)
        return;

    for (auto& currObj : objects)
        if (currObj)
            writerProducts << *currObj << "\n";

    writerProducts.close();

    std::ofstream writerQuantity;
    writerQuantity.open(getFileNameQunatity().c_str(), std::ofstream::out);

    if (!writerQuantity)
        return;

    for (auto& currObj : objects)
        if (currObj)
            writerQuantity << currObj->getId() << " " << currObj->getQuantity() << "\n";

    writerQuantity.close();
    repo_mtx.unlock();
}

#endif

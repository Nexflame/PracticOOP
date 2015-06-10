/*
 * Repository.h
 *
 *  Created on: Apr 7, 2015
 *      Author: Nexflame
 */

#ifndef REPOSITORY_REPOSITORY_H_
#define REPOSITORY_REPOSITORY_H_

#include <string>
#include <vector>
#include <mutex>
#include "../Entity/Product.h"

template <class T>
class ProductRepository
{
public:
    explicit ProductRepository(std::string fileNameProduct, std::string fileNameQuantity);
    virtual ~ProductRepository();

    // Methods
    const std::string& getFileNameProduct() const;
    void setFileNameProduct(const std::string& fileName);

    const std::string& getFileNameQunatity() const;
    void setFileNameQuntity(const std::string& fileName);

    const std::vector<T>& getObjects() const;
    const int getSize() const;
    void addObject(T& newObject);
    const T findByID(const int& ID) const;
    void save();

private:
    std::string fileNameProduct;
    std::string fileNameQuantity;
    std::vector<T> objects;

    void _loadAll();
    void _saveAll();

    std::mutex repo_mtx;
};

#endif /* REPOSITORY_REPOSITORY_H_ */

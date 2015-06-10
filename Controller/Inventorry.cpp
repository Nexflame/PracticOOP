/*
 * Controller.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Nexflame
 */

#include "Inventorry.h"
//#include "../Repository/Repository_implementation.h"
#include <string.h>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cctype>
#include <cstring>

Inventorry::Inventorry(ProductRepository<Product*>* repo) :
repo(repo) { }

Inventorry::~Inventorry()
{
    if(repo)
        delete repo;
}

const std::vector<Product*>& Inventorry::GetAllObjects()
{
    return repo->getObjects();
}

void Inventorry::AddObject(Product*& obj)
{
    repo->addObject(obj);
    repo->save();
}

ProductRepository<Product*>*& Inventorry::getRepo()
{
    return repo;
}

const std::vector<Product*> Inventorry::SortObjects()
{
    std::vector<Product*> out = repo->getObjects();

    std::function<int(Product*, Product*)> cmp;

    cmp = [](Product* a, Product* b)->bool { return a->getNume() < b->getNume(); };

    std::sort(out.begin(), out.end(), cmp);
    return out;
}

// only here used
bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void Inventorry::UpdateObject(Product* pr, std::string name, std::string cantitate)
{
    if (is_number(cantitate))
    {
        int canti = std::atoi(cantitate.c_str());
        pr->setQuantity(canti);
        pr->setName(name);
        repo->save();
    }
    else
        throw ExceptionInv();
}

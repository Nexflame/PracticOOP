#include "Inventory.h"
#include <string.h>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cctype>
#include <cstring>

Inventory::Inventory(ProductRepository<Product*>* repo) :
repo(repo) { }

Inventory::~Inventory()
{
    if(repo)
        delete repo;
}

const std::vector<Product*>& Inventory::GetAllObjects()
{
    return repo->getObjects();
}

void Inventory::AddObject(Product*& obj)
{
    repo->addObject(obj);
    repo->save();
}

ProductRepository<Product*>*& Inventory::getRepo()
{
    return repo;
}

const std::vector<Product*> Inventory::SortObjects()
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

void Inventory::UpdateObject(Product* pr, std::string name, std::string cantitate)
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

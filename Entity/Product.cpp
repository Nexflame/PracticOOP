#include "Product.h"

Product::Product() : name(""), id(0), quantity(0) { }
Product::~Product() { }

bool Product::operator == (const Product& obj)
{
    return getId() == obj.getId();
}


bool Product::operator != (const Product& obj)
{
    return getId() != obj.getId();
}


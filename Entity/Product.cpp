#include "Product.h"

Product::Product() { }
Product::~Product() { }

std::istream& operator >> (std::istream& in, Product& obj)
{
    std::string _name;
    int _id;

    bool ok = false;

    if (in >> _id >> _name )
        ok = true;

    if (!ok)
        return in;

    obj.setName(_name);
    obj.setId(_id);
    obj.setQuantity(0);

    return in;
}

std::ostream& operator << (std::ostream& out, const Product& obj)
{
    out << obj.getId() << " " << obj.getNume();

    return out;
}

bool Product::operator == (const Product& obj)
{
    return getId() == obj.getId();
}


bool Product::operator != (const Product& obj)
{
    return getId() != obj.getId();
}


#include <string>

#ifndef ENTITY_OBJECT_OBJECT_H_
#define ENTITY_OBJECT_OBJECT_H_

class Product
{
public:
    Product();
    ~Product();

    int getId() const { return id; }
    int getQuantity() const { return quantity; }
    const std::string& getNume() const { return name; }

    void setId(int _id) { id = _id; }
    void setQuantity(int _quantity) { quantity = _quantity; }
    void setName(std::string _name) { name = _name; }

    friend std::istream& operator >> (std::istream& in, Product& obj);
    friend std::ostream& operator << (std::ostream& out, const Product& obj);

    bool operator == (const Product& obj);
    bool operator != (const Product& obj);

private:
    std::string name;
    int id;
    int quantity;
};

#endif

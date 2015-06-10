#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../Repository/Repository_implementation.h"
#include <functional>
#include <mutex>
#include <exception>

class Inventorry
{
public:
    explicit Inventorry(ProductRepository<Product*>* repo);
    virtual ~Inventorry();

    // Controller functionalities
    const std::vector<Product*> SortObjects();
    const std::vector<Product*>& GetAllObjects();
    
    void AddObject(Product*& obj);
    void UpdateObject(Product* pr, std::string name, std::string cantitate);

    ProductRepository<Product*>*& getRepo();

private:
    ProductRepository<Product*>* repo;
};

class ExceptionInv : public std::exception
{
public:
    ExceptionInv() { msg = "Cantitatea introdusa de utilizator trebuie sa fie numar intreg!";  }
    std::string getMsg() { return msg; }

private:
    std::string msg;
};

#endif /* CONTROLLER_H_ */

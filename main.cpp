#include "myclass.h"
#include <QtWidgets/QApplication>
#include <QtCore/QCoreApplication>

#include "Controller/Inventory.h"
#include "Entity/Product.h"
#include "UI/Window.h"

int _runUI(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProductRepository<Product*>* repo = new ProductRepository<Product*>("produse.txt", "cantitati.txt");
    Inventory* ctrl = new Inventory(repo);
    AppWindow* GUI = new AppWindow(ctrl);

    //GUI->setMinimumSize(2048, 1024);
    GUI->show();

    return a.exec();
}

int main(int argc, char *argv[])
{
    return _runUI(argc, argv);
}

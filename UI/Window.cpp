#include "Window.h"
#include <QtCore>
#include <QtGui>

AppWindow::AppWindow(Inventory* _ctrl, QWidget *parent)
    : QWidget(parent)
{
    ui.setupUI(this);

    this->ctrl = _ctrl;
    
    LinkSignalsToSlots();
    ReloadObjectList();
}

AppWindow::~AppWindow()
{

}

void AppWindow::LinkSignalsToSlots()
{
    QObject::connect(ui.buttonUpdate, SIGNAL(clicked()), this, SLOT(Update()));
}

void AppWindow::ReloadObjectList()
{
    std::vector<Product*> storeObjects = ctrl->SortObjects();

    QStandardItemModel* model = new QStandardItemModel(storeObjects.size(), 3);

    int k = 0;
    for (auto& obj : storeObjects)
    {
        int id = obj->getId();
        int cantitate = obj->getQuantity();
        std::string nume = obj->getNume();

        QString idQString = QString::number(id);
        QString quantityQString = QString::number(cantitate);
        QString numeQString = QString::fromStdString(nume);

        QStandardItem* idItem = new QStandardItem(idQString);
        QStandardItem* cantitateItem = new QStandardItem(quantityQString);
        QStandardItem* numeItem = new QStandardItem(numeQString);

        model->setItem(k, 0, idItem);
        model->setItem(k, 1, cantitateItem);
        model->setItem(k, 2, numeItem);
        k++;
    }
    
    // TO DO: Should delete old model ? How ?
    ui.Tabel->setModel(model);

    ui.Tabel->setColumnHidden(0, true);
    ui.Tabel->model()->setHeaderData(1, Qt::Horizontal, "Cantitate");
    ui.Tabel->model()->setHeaderData(2, Qt::Horizontal, "Nume");
}

void AppWindow::Update()
{
    QModelIndexList indexes = ui.Tabel->selectionModel()->selection().indexes();
    for (int i = 0; i < indexes.count(); ++i)
    {
        QModelIndex index = indexes.at(i);

        if (index.column() == 1)
        {
            int id = ui.Tabel->model()->data(ui.Tabel->model()->index(index.row(), 0)).toInt();
            QString ProductNameQ = ui.Tabel->model()->data(ui.Tabel->model()->index(index.row(), 2)).toString();
            std::string ProductName = ProductNameQ.toStdString();

            QString ProductQuantityQ = ui.Tabel->model()->data(ui.Tabel->model()->index(index.row(), 1)).toString();
            std::string ProductQuantity = ProductQuantityQ.toStdString();

            try
            {
                if (Product* pr = ctrl->getRepo()->findByID(id))
                    ctrl->UpdateObject(pr, ProductName, ProductQuantity);
            }
            catch (ExceptionInv& exc)
            {
                QString msg = QString::fromStdString(exc.getMsg());
                QMessageBox::critical(this, "Error", msg);
            }
            
        }
        
    }
    ReloadObjectList();
}


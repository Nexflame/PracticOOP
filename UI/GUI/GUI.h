#ifndef GUI_H_
#define GUI_H_

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>


class GUI
{
public:
    QStandardItemModel* createModel(QObject* parent)
    {
        const int numRows = 100;
        const int numColumns = 2;

        QStandardItemModel* model = new QStandardItemModel(numRows, numColumns);

        return model;
    }

    QVBoxLayout* mainLayout;
    QPushButton* buttonUpdate;

    QLineEdit* textExpr;
    QLabel* labelRezutat;
    QLabel* finalRezutat;

    QListWidget* List;
    QTableView* Tabel;

    void setupUI(QWidget* parent)
    {
        mainLayout = new QVBoxLayout();
        parent->setLayout(mainLayout);

        buttonUpdate = new QPushButton("Adauga Cantitate");
        mainLayout->addWidget(buttonUpdate);


        Tabel = new QTableView;
        Tabel->setModel(createModel(Tabel));
        mainLayout->addWidget(Tabel);
    }
};


#endif /* GUI_H_ */

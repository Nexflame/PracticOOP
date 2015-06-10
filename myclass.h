#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtWidgets/QWidget>
#include "ui_myclass.h"

class MyClass : public QWidget
{
    Q_OBJECT

public:
    MyClass(QWidget *parent = 0);
    ~MyClass();

private:
    Ui::MyClassClass ui;
};

#endif // MYCLASS_H

#ifndef APPGUI_H
#define APPGUI_H

#include <QWidget>
#include <QtWidgets>
#include <QtGui>
#include <qlabel.h>

#include <qmessagebox.h>
#include <qlistwidget.h>
#include <string>
#include <thread>

#include "Controller/Inventory.h"
#include "GUI/GUI.h"

using namespace std;

class AppWindow : public QWidget
{
    Q_OBJECT

public:
    AppWindow(Inventory* _ctrl, QWidget *parent = 0);
    ~AppWindow();

private:
    GUI ui;
    Inventory* ctrl;
    void LinkSignalsToSlots();
    void ReloadObjectList();

private slots:
    void Update();
};

#endif // APPGUI_H

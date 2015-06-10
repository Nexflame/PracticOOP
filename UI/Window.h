#ifndef STUDENTMANAGEMENTGUI_H
#define STUDENTMANAGEMENTGUI_H

#include <QWidget>
#include <QtWidgets>
#include <QtGui>
#include <qlabel.h>

#include <qmessagebox.h>
#include <qlistwidget.h>
#include <string>
#include <thread>

#include "Controller/Inventorry.h"
#include "GUI/GUI.h"

using namespace std;

class AppWindow : public QWidget
{
    Q_OBJECT

public:
    AppWindow(Inventorry* _ctrl, QWidget *parent = 0);
    ~AppWindow();

private:
    GUI ui;
    Inventorry* ctrl;
    void LinkSignalsToSlots();
    void ReloadObjectList();

private slots:
    void Update();
};

#endif // STUDENTMANAGEMENTGUI_H

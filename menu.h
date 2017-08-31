#include "menu_ui.h"
#include <QMainWindow>
#include "converter.h"
#include <QList>
#include <QStandardItemModel>
#ifndef MENU_H
#define MENU_H
class Menu: public QMainWindow, public Ui_Menu{
    Q_OBJECT 
    Converter converter;
    QList<QStandardItemModel*> list; 
    public:
    Menu();
    void setupSelf();
    double getInputDouble();
    std::string fromBoxText();
    std::string toBoxText();
    public slots:

    void changedType(int index);
    void editted(QString string);
    void update();
    void quitIt();
};

#endif
#include "ui_menu_ui.h"
#include <QMainWindow>
#include "converter.h"
#include <QList>
#include <QStandardItemModel>
#include "dialog.h"
#ifndef MENU_H
#define MENU_H
//Class that implemennts the Ui_Menu. The Ui_Menu is the form I made for the
//the interface. This class handles all the interactions with said interface and
//contains the necessary class (Converter) to handle the unit convertions as 
//well.

class Menu: public QMainWindow, public Ui_Menu{
    Q_OBJECT 
    Converter converter;
    QList<QStandardItemModel*> list; 
    Dialog *dial;
    std::string sPath;

    public:
    Menu();
    void setupSelf();
    double getInputDouble();
    std::string fromBoxText();
    std::string toBoxText();
    void checkCurrency();
    void writeToFile(std::string path);
    public slots:

    void changedType(int index);
    void editted(QString string);
    void update();
    void quitIt();
    void currencyAccept();
    void currencyReject();
    void currencyRead();
};

#endif

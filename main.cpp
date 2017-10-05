#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include "menu.h"

//File  where main is implemented.
//Does nothing other than create the menu and exec  the QT app

int main(int argc,char **argv){
    QApplication app(argc,argv);
    Menu menu;
    menu.show();
    return app.exec();


}
#endif

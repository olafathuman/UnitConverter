#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <QApplication>
#include "menu.h"
using namespace std;
int main(int argc,char **argv){
    QApplication app(argc,argv);
    Menu menu;
    menu.show();
    return app.exec();


}
#endif

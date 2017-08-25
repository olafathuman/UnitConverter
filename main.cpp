#include <iostream>
#include "converter.h"
#include <QApplication>
#include <QMainWindow>
#include "menu.h"
using namespace std;
int main(int argc,char **argv){
    QApplication app(argc,argv);
    QMainWindow men;
    men.show();
    Ui_Menu menu = Ui_Menu();
    menu.setupUi(&men);
    return app.exec();


}

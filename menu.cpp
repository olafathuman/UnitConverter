#include "menu.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDoubleValidator>
#include <QString>
#include <sstream>
#include <string>
#include "moc_menu.cpp"
#include "dialog.h"
#ifndef MENU_CPP
#define MENU_CPP
Menu::Menu(){
    
    setupUi(this);
    setupSelf(); 
}

void Menu::changedType(int index){
    fromBox->setModel(list.value(index));
    toBox->setModel(list.value(index));
    update();
}

void Menu::setupSelf(){
    this->statusBar()->setSizeGripEnabled(false);
    setFixedSize(size());
    typeBox->addItem("Distance");
    typeBox->addItem("Speed");
    typeBox->addItem("Weight");
    QStandardItemModel* current = new QStandardItemModel();
    current->appendRow(new QStandardItem("Miles"));
    current->appendRow(new QStandardItem("Kilometers"));
    current->appendRow(new QStandardItem("Centimeters"));
    current->appendRow(new QStandardItem("Inches"));
    list.append(current);
    current = new QStandardItemModel();
    current->appendRow(new QStandardItem("km/h"));
    current->appendRow(new QStandardItem("mi/h"));
    current->appendRow(new QStandardItem("m/s"));
    list.append(current);
    current = new QStandardItemModel();  
    current->appendRow(new QStandardItem("Kilograms"));
    current->appendRow(new QStandardItem("Pounds"));
    list.append(current);
    inputLine->setValidator(new QDoubleValidator());
    fromBox->setModel(list.value(0));
    toBox->setModel(list.value(0));
    connect(typeBox,SIGNAL(activated(int)),static_cast<Menu*>(this),SLOT(changedType(int)));
    connect(inputLine,SIGNAL(textChanged(QString)),static_cast<Menu*>(this),SLOT(editted(QString)));
    connect(fromBox,SIGNAL(activated(int)),static_cast<Menu*>(this),SLOT(update()));
    connect(toBox,SIGNAL(activated(int)),static_cast<Menu*>(this),SLOT(update()));
    connect(exitButton,SIGNAL(released()),static_cast<Menu*>(this),SLOT(quitIt()));
}
void Menu::editted(QString string){
    double input = string.toDouble();
    double result = converter.convert(typeBox->currentIndex(),fromBoxText(),toBoxText(),input);
    std::ostringstream s;
    s << result;
    resultLabel->setText(QString::fromStdString(s.str()));
}

void Menu::update(){
    double input = getInputDouble(); 
    double result = converter.convert(typeBox->currentIndex(),fromBoxText(),toBoxText(),input);
    std::ostringstream s;
    s << result;
    resultLabel->setText(QString::fromStdString(s.str()));
}
std::string Menu::fromBoxText(){
    return fromBox->currentText().toUtf8().constData();
}
std::string Menu::toBoxText(){
    return toBox->currentText().toUtf8().constData();
}

double Menu::getInputDouble(){
    QString string=inputLine->displayText();
    return string.toDouble();
}

void Menu::quitIt(){
    close();
}

void checkCurrency(){
    dial = new Dialog();
    connect(dial,SIGNAL(accepted()),this,currencyAccept());
    connect(dial,SIGNAL(rejected()),this,currencyReject());  
}

void currencyAccept(){
    converter.updateCurrency();
    dial.close();   
}
void currencyReject(){
    
}

#endif

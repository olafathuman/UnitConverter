#include "menu.h"
#include <QLocale>
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

//Constructor for the Menu class. sets the Local to one that handles string to
//double and vice-versa the way i want it to.
Menu::Menu(){
    QLocale::setDefault(QLocale::Portuguese);
    sPath="CurrentRates.txt";
    setupUi(this);
    setupSelf(); 
}

void Menu::changedType(int index){
    fromBox->setModel(list.value(index));
    toBox->setModel(list.value(index));
    update();
}
//Function that sets ups everything the menu needs.
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
    checkCurrency();
}

//Function called when something is written in the input field.
void Menu::editted(QString string){
    double input = string.toDouble();
    double result = converter.convert(typeBox->currentText().toUtf8().constData(),fromBoxText(),toBoxText(),input);
    std::ostringstream s;
    s << result;
    resultLabel->setText(QString::fromStdString(s.str()));
}
//Function called whenever the result needs to be updated.
void Menu::update(){
    double input = getInputDouble(); 
    double result = converter.convert(typeBox->currentText().toUtf8().constData(),fromBoxText(),toBoxText(),input);
    std::ostringstream s;
    s << result;
    resultLabel->setText(QString::fromStdString(s.str()));
}
//Function that returns the item in the fromBox as a string.
std::string Menu::fromBoxText(){
    return fromBox->currentText().toUtf8().constData();
}
//Function same asa above for toBox.
std::string Menu::toBoxText(){
    return toBox->currentText().toUtf8().constData();
}

//Get value in the input field as a double.
double Menu::getInputDouble(){
    QString string=inputLine->displayText();
    return string.toDouble();
}

//Function that closes the main window.
void Menu::quitIt(){
    close();
}
//Function that opens up the dialog asking if we should download data or not.
void Menu::checkCurrency(){
    dial = new Dialog();
    std::string str = converter.getDateFromFile(sPath);
    if(str.compare("ERROR") != 0){
        dial->setDate(str);
        connect(dial,SIGNAL(rejected()),this,SLOT(currencyRead())); 
    }
    else{
        connect(dial,SIGNAL(rejected()),this,SLOT(currencyReject())); 
    }
    connect(dial,SIGNAL(accepted()),this,SLOT(currencyAccept()));
}
//Function that is called if we click yes on the dialog.
void Menu::currencyAccept(){
    dial->close();
    converter.updateCurrency();
    typeBox->addItem("Currency");
    
    list.append(converter.getUnits());
    writeToFile(sPath);
}
//Function that is called if no is pressed on the dialog without a data file.
void Menu::currencyReject(){
   dial->close ();
}
//Function that is called if no is pressed on the dialog with a data file.
void Menu::currencyRead(){
    dial->close();
    converter.readFromFile(sPath);
    typeBox->addItem("Currency");
    list.append(converter.getUnits());
}
//Function that writes currency data to a file.
void Menu::writeToFile(std::string path){
    converter.writeToFile(path);
}
#endif

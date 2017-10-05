#include <map>
#include <vector>
#include <QStandardItemModel>
#ifndef CURRENCY_H
#define CURRENCY_H
//Here I define the currency module for the application.
//The CurrencyHandle class handles everything in terms of currency unit 
//conversion.

class CurrencyHandler{
    
    
    std::map<std::string,double> toEurRates;
    std::map<std::string,double> fromEurRates;
    std::string sPath;
    std::string url;
    std::string date;
    bool set=false;
    public:
        CurrencyHandler();
        double getToRate(std::string str);
        double getFromRate(std::string str);
        std::string getDate();
        std::vector<std::string> listify(std::string str);
        std::vector<std::string>cleanList(std::vector<std::string> ls);
        void fillMap(std::vector<std::string> ls);
        void update();
        QStandardItemModel* getUnits();
        void printAll();
        void writeToFile(std::string path);
        void readFromFile(std::string path);
        void setDate(std::string d);
        std::string getDateFromFile(std::string path);
};


#endif

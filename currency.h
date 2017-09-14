#include <map>
#include <vector>
#include <QStandardItemModel>
#ifndef CURRENCY_H
#define CURRENCY_H
class CurrencyHandler{
    
    
    std::map<std::string,double> toEurRates;
    std::map<std::string,double> fromEurRates;
    std::string path;
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
};


#endif

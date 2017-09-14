#include <string>
#include <currency.h>
#include <QStandardItemModel>
#ifndef CONVERTER_H
#define CONVERTER_H
#define WEIGHT 2
#define SPEED 1
#define DISTANCE 0
#define CURRENCY 3
class Converter{
    double pound2kg;
    double kg2pound;
    double mile2km;
    double km2mile;
    double inch2cm;
    double cm2inch;
    double kph2mph;
    double mph2kph;
    CurrencyHandler currency; 
    public:
        Converter();
        double convertLb2Kg(double lb);
        double convertKg2Lb(double kg);
        double convertMi2Km(double mi);
        double convertKm2Mi(double km);
        double convertIn2Cm(double in);
        double convertCm2In(double cm);
        double convertMi2Cm(double mi);
        double convertMi2In(double mi);
        double convertKm2Cm(double km);
        double convertCm2Km(double cm);
        double convertKm2In(double km);
        double convertCm2Mi(double cm);
        double convertIn2Km(double in);
        double convertIn2Mi(double in);
        double convertKph2Mph(double kph);
        double convertKph2Ms(double kph);
        double convertMph2Kph(double mph);
        double convertMph2Ms(double mph);
        double convertMs2Kph(double ms);
        double convertMs2Mph(double ms);
        double fromEur(std::string coin, double value);
        double toEur(std::string coin, double value);
        void updateCurrency();
        void readCurrency();
        std::string getDate();
        double convert(std::string type,std::string from, std::string to,double value);
        QStandardItemModel* getUnits();
        void printAll();
};

#endif

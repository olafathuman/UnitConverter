#include <string>

#ifndef CONVERTER_H
#define CONVERTER_H


class Converter{
    double pound2kg;
    double kg2pound;
    double mile2km;
    double km2mile;
    double inch2cm;
    double cm2inch;
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
        double convert(int index,std::string from, std::string to,double value);

};
#endif

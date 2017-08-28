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
        double convert(int index,std::string from, std::string to,double value);

};
#endif

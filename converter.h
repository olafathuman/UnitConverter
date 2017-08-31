#include <string>

#ifndef CONVERTER_H
#define CONVERTER_H
#define WEIGHT 2
#define SPEED 1
#define DISTANCE 0

class Converter{
    double pound2kg;
    double kg2pound;
    double mile2km;
    double km2mile;
    double inch2cm;
    double cm2inch;
    double kph2mph;
    double mph2kph;
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
        double convert(int index,std::string from, std::string to,double value);
};
#endif

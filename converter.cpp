#include "converter.h"
#include <string>

Converter::Converter(){
    double I=1;
    pound2kg=0.45359237;
    kg2pound=I/pound2kg;
    mile2km=1.609344;
    km2mile=I/mile2km;
    inch2cm=2.54;
    cm2inch=I/inch2cm;
}

double Converter::convertLb2Kg(double lb){
    double aux = lb*pound2kg;
    return aux;
}
double Converter::convertKg2Lb(double kg){

    return kg*kg2pound;
}
double Converter::convertMi2Km(double mi){
    return mi*mile2km;
}
double Converter::convertKm2Mi(double km){
    return km*km2mile;
}
double Converter::convertIn2Cm(double in){
    return in*inch2cm;
}
double Converter::convertCm2In(double cm){
    return cm*cm2inch;
}

double Converter::convert(int index,std::string from, std::string to,double value){
    if(from.compare(to)==0){
        return value;
    }
    switch(index){
        case 0:
            if (from.compare("Kilograms")==0){
                if(to.compare("Pounds")==0){
                    return convertKg2Lb(value);
                        }

            }
            else if(from.compare("Pounds")==0){
                if(to.compare("Kilograms")==0){
                    return convertLb2Kg(value);
                }
            }
        }
    return value;
}

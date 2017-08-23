#include "converter.h"

Converter::Converter(){
    pound2kg=0.45359237;
    kg2pound=1/pound2kg;
    mile2km=1.609344;
    km2mile=1/mile2km;
    inch2cm=2.54;
    cm2inch=1/inch2cm;
}

float Converter::convertLb2Kg(float lb){
    return lb*pound2kg;
}
float Converter::convertKg2Lb(float kg){

    return kg*kg2pound;
}
float Converter::convertMi2Km(float mi){
    return Mi*mile2km;
}
float Converter::convertKm2Mi(float km){
    return km*km2mile;
}
float Converter::convertIn2Cm(float in){
    return in*inch2cm;
}
float Converter::convertCm2In(float cm){
    return cm*cm2inch;
}

#include "converter.h"
#include "currency.h"
#include <string>
#include "curler.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <iostream>

//Implementation of the converter class.

Converter::Converter(){
    double I=1;
    pound2kg=0.45359237;
    kg2pound=I/pound2kg;
    mile2km=1.609344;
    km2mile=I/mile2km;
    inch2cm=2.54;
    cm2inch=I/inch2cm;
    mph2kph=1.609344;
    kph2mph=1/mph2kph;
}

//Function that converts pounds to kilograms
double Converter::convertLb2Kg(double lb){
    double aux = lb*pound2kg;
    return aux;
}

//Function that converts kilograms to pounds
double Converter::convertKg2Lb(double kg){

    return kg*kg2pound;
}

//Function that converts miles to kilometers
double Converter::convertMi2Km(double mi){
    return mi*mile2km;
}

//Function that converts kilometers to miles
double Converter::convertKm2Mi(double km){
    return km*km2mile;
}

//Function that converts inches to centimeters
double Converter::convertIn2Cm(double in){
    return in*inch2cm;
}

//Function that converts centimeters to inches
double Converter::convertCm2In(double cm){
    return cm*cm2inch;
}

//Function that converts miles to centimeters
double Converter::convertMi2Cm(double mi){
    return convertKm2Cm(convertMi2Km(mi));
}

//Function that converts miles to inches
double Converter::convertMi2In(double mi){
    return convertCm2In(convertMi2Cm(mi));
}

//Function that converts kilometers to centimeters
double Converter::convertKm2Cm(double km){
    return km*100;
}

//Function that converts centimeters to kilometers
double Converter::convertCm2Km(double cm){
    return cm/100;
}

//Function that converts kilometers to inches
double Converter::convertKm2In(double km){
    return convertCm2In(convertKm2Cm(km));
}

//Function that converts centimeters to miles
double Converter::convertCm2Mi(double cm){
    return convertKm2Mi(convertCm2Km(cm));
}

//Function that converts inches to kilometers
double Converter::convertIn2Km(double in){
    return convertCm2Km(convertIn2Cm(in));
}

//Function that converts inches to miles
double Converter::convertIn2Mi(double in){
    return convertCm2Mi(convertIn2Cm(in));
}

//Function that converts kilometers per hour to miles per hour
double Converter::convertKph2Mph(double kph){
    return kph*kph2mph;
}

//Function that converts kilometers per hour to meters per second
double Converter::convertKph2Ms(double kph){
    return ((kph*1000)/60)/60;
}

//Function that converts miles per hour to kilometers per hour
double Converter::convertMph2Kph(double mph){
    return mph*mph2kph;
}

//Function that conerts miles per hour to meters per second
double Converter::convertMph2Ms(double mph){
    return convertKph2Ms(convertMph2Kph(mph));
}

//Function that converts meters per second to kilometers per hour
double Converter::convertMs2Kph(double ms){
    return ((ms/1000)*60)*60;
}

//Function that converts meters per second to miles per hour
double Converter::convertMs2Mph(double ms){
    return convertKph2Mph(convertMs2Kph(ms));
}

//Function that converts any given value from any given unit
//to the desired unit.
double Converter::convert(std::string type,std::string from, std::string to,double value){
    
    //If input and output units are the same, return the value
    if(from.compare(to)==0){
        return value;
    }
    //otherwise, we need to know what the type of units we're using
    if(type.compare("Weight")==0){
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
    else if(type.compare("Distance")==0){
            if(from.compare("Miles")==0){
                if(to.compare("Kilometers")==0){
                    return convertMi2Km(value);
                }
                else if(to.compare("Inches")==0){
                    return convertMi2In(value);
                        }
                else if(to.compare("Centimeters")==0){
                    return convertMi2Cm(value);
                }

            }

            else if(from.compare("Kilometers")==0){
                if(to.compare("Miles")==0){
                    return convertKm2Mi(value);
                }
                else if(to.compare("Centimeters")==0){
                    return convertKm2Cm(value);
                }
                else if(to.compare("Inches")==0){
                    return convertKm2In(value);
                }

            }
            else if(from.compare("Centimeters")==0){
                    if(to.compare("Kilometers")==0){
                        return convertCm2Km(value);
                    }
                    else if(to.compare("Miles")==0){
                        return convertCm2Mi(value);
                    }
                    else if(to.compare("Inches")==0){
                        return convertCm2In(value);
                    }
                    }
            else if(from.compare("Inches")==0){
                if (to.compare("Kilometers")==0){
                    return convertIn2Km(value);
                }
                else if(to.compare("Miles")==0){
                    return convertIn2Mi(value);
                }
                else if(to.compare("Centimeters")==0){
                    return convertIn2Cm(value);
                }
            }
    }
    else if(type.compare("Speed")==0){
            if (from.compare("km/h")==0){
                if(to.compare("mi/h")==0){
                    return convertKph2Mph(value);
                }
                else if(to.compare("m/s")==0){
                    return convertKph2Ms(value);
                }
            }
            else if(from.compare("mi/h")==0){
                if(to.compare("km/h")==0){
                    return convertMph2Kph(value);
                }
                else if(to.compare("m/s")==0){
                    return convertMph2Ms(value);
                }
            }
            else if(from.compare("m/s")==0){
                if(to.compare("km/h")==0){
                    return convertMs2Kph(value);
                }
                else if(to.compare("mi/h")==0){
                    return convertMs2Mph(value);
                }
            }
    }
    //Currency is the only one implemented differently
    //When I started converting units, i thought one function per pair of units
    //was reasonable. However, for currency, I'd have far too many functions. 
    //So the solution was to use a dictionary with the rates from any unit of
    //currency to Euros.
    else if(type.compare("Currency")==0){
        //if we're converting from Euros to another unit, I use the fromEur 
        //function.
        if(from.compare("EUR")==0){
            return fromEur(to,value);        
            }
        //If we're converting To Euros instead, I use the toEur function.
        else if(to.compare("EUR")==0){
            return toEur(from,value);
        }
        //If we're neither converting from or to Euros, we have to convert the
        //input value to the Euro equivalent, then convert it to the desired
        //unit.
        else{
            return fromEur(to,toEur(from,value));
        }
    }
//Code should never reach here, but, in the off chance it does, it'll return
//the value without modifying it.
    return value;
}

//Function that given value Euros, returns the equivalent amount in the coin
//currency.
double Converter::fromEur(std::string coin, double value){
    return value*currency.getFromRate(coin);
}

//Function that given a value in coin currency, returns the equivalent value in
//euros.
double Converter::toEur(std::string coin, double value){
    return value*currency.getToRate(coin);
}

//Function that updates the currency module, fetching latest currency data.
void Converter::updateCurrency(){
   currency.update(); 
}

//Function that returns the current date on the currency module.
std::string Converter::getDate(){
    return currency.getDate();
}

//Function that returns the date in currency file in path. If no if fails to
//open said file, it will return "ERROR"
std::string Converter::getDateFromFile(std::string path){
    return currency.getDateFromFile(path);
}

//returns a list with all units of currency for use in the QT interface.
QStandardItemModel* Converter::getUnits(){
   return currency.getUnits();
}

//writes current rates to file in path.
void Converter::writeToFile(std::string path){
    currency.writeToFile(path);
}

//reads and uses rates found in path.
void Converter::readFromFile(std::string path){
    currency.readFromFile(path);

}

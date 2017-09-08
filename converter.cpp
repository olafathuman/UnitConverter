#include "converter.h"
#include <string>
#include "curler.h"
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

double Converter::convertMi2Cm(double mi){
    return convertKm2Cm(convertMi2Km(mi));
}
double Converter::convertMi2In(double mi){
    return convertCm2In(convertMi2Cm(mi));
}
double Converter::convertKm2Cm(double km){
    return km*100;
}
double Converter::convertCm2Km(double cm){
    return cm/100;
}
double Converter::convertKm2In(double km){
    return convertCm2In(convertKm2Cm(km));
}

double Converter::convertCm2Mi(double cm){
    return convertKm2Mi(convertCm2Km(cm));
}

double Converter::convertIn2Km(double in){
    return convertCm2Km(convertIn2Cm(in));
}

double Converter::convertIn2Mi(double in){
    return convertCm2Mi(convertIn2Cm(in));
}
double Converter::convertKph2Mph(double kph){
    return kph*kph2mph;
}
double Converter::convertKph2Ms(double kph){
    return ((kph*1000)/60)/60;
}
double Converter::convertMph2Kph(double mph){
    return mph*mph2kph;
}
double Converter::convertMph2Ms(double mph){
    return convertKph2Ms(convertMph2Kph(mph));
}
double Converter::convertMs2Kph(double ms){
    return ((ms/1000)*60)*60;
}
double Converter::convertMs2Mph(double ms){
    return convertKph2Mph(convertMs2Kph(ms));
}


double Converter::convert(int index,std::string from, std::string to,double value){
    if(from.compare(to)==0){
        return value;
    }
    switch(index){
        case WEIGHT:
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
            break;
        case DISTANCE:
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
            break;
        case SPEED:
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

    return value;
}

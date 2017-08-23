#ifndef CONVERTER_H
#define CONVERTER_H
class Converter{
    float pound2kg;
    float kg2pound;
    float mile2km;
    float km2mile;
    float inch2cm;
    float cm2inch;
    public:
        Converter();
        float convertLb2Kg(float lb);
        float convertKg2Lb(float kg);
        float convertMi2Km(float mi);
        float convertKm2Mi(float km);
        float convertIn2Cm(float in);
        float convertCm2In(float cm);


};
#endif

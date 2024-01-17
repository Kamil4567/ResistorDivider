#ifndef RESISTOR_DIVIDER_H
#define RESISTOR_DIVIDER_H

#include <Arduino.h>

class ResistorDivider{
    private:
        float R1 = 1;
        float R2 = 1;
        int pinNumber = -1;
        int adcMaxValue = 1024;
    public:
        ResistorDivider();
        ResistorDivider(float resistor1, float resistor2);
        ResistorDivider(float resistor1, float resistor2, int pinNumber, int maxValue);
};










#endif

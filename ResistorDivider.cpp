#include "ResistorDivider.h"

ResistorDivider::ResistorDivider(){

}

ResistorDivider::ResistorDivider(float resistor1, float resistor2){
    this->R1 = resistor1;
    this->R2 = resistor2;
}

ResistorDivider::ResistorDivider(float resistor1, float resistor2, int pinNumber, int adcMaxValue){
    this->R1 = resistor1;
    this->R2 = resistor2;
    this->pinNumber = pinNumber;
    this->adcMaxValue = adcMaxValue;
}

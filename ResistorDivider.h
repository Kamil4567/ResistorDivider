#ifndef RESISTOR_DIVIDER_H
#define RESISTOR_DIVIDER_H

#include <Arduino.h>

/// @brief Class for reading voltage from analog input with resistor voltage divider.
/// 
/// Class can be used for reading voltage from analog input with voltage divider or
/// calculations alone.
///
/// Required parameters to get a reading from resistor divider input:
/// - Resistance of R1 in ohms
/// - Resistonce of R2 in ohms
/// - Max reading from ADC (1023 for 10bit ADC, 4095 for 12bit ADC, (2^n)-1 for n bit ADC)
/// - Max ADC voltage (5V, 3.3V etc.)
/// 
/// Calculations:
/// - Input voltage, required R1, R2 and output voltage
/// - Output voltage, required R1, R2 and input voltage
/// - R1, required R2, input voltage, outputVoltage
/// - R2, required R1, input voltage, outputVoltage
class ResistorDivider{
    private:
        /*
        Resistor divider wiring

        |------\           |------------|                     |------------|           /------|
        |  VIN  >----------|     R1     |----------|----------|     R2     |----------<  GND  |    
        |------/           |------------|          |          |------------|           \------|
                                                   |
                                                   |           /------|
                                                   \----------<  ADC  |
                                                               \------|
        */
        float R1 = 1; // value of R1 resistor in ohms
        float R2 = 1; // value of R2 resistor in ohms
        int pinNumber = -1; // analog input pin number
        int adcMaxValue = 1024; // max value of ADC reading
        float adcMaxVoltage = 5.0; // max ADC voltage
        float adcVoltageMultiplier = 1; // ADC voltage will be multiplied by this 
        float adcVoltageOffset = 0; // and this value will be added
    public:
        ResistorDivider(); // don't provide any values in the constructor, set them later with setters
        ResistorDivider(float resistor1, float resistor2); // specify only the resistor values(when using lib only for calculations)
        ResistorDivider(float resistor1, float resistor2, 
                        int pinNumber, int adcMaxValue, float adcMaxVoltage); // pass all parameters excluding calibration values
        ResistorDivider(float resistor1, float resistor2, 
                        int pinNumber, int adcMaxValue, 
                        float adcMaxVoltage, float adcVoltageMutiplier, 
                        float adcVoltageOffset); // pass all parametrs

        // SETTERS
        void setR1(float value); // set new R1 value
        void setR2(float value); // set new R2 value
        void setPin(int pinNumber); // set pin number
        void setADCMaxValue(int adcMaxValue); // set adc max value
        void setADCMaxVoltage(float adcMaxVoltage); // set adc max voltage
        void setADCMultiplier(float adcVoltageMutiplier); // set adc voltage multiplier
        void setADCOffset(float adcVoltageOffset); // set adc voltage offset
        // GETTERS
        float getR1(); // get R1 value
        float getR2(); // get R2 value
        int getPin(); // get pin number
        int getADCMaxValue(); // get ADC max value
        float getADCMaxVoltage(); // get ADC max voltage
        float getADCMultiplier(); // get ADC voltage multiplier
        float getADCOffset(); //get ADC voltage offset

        // VOLTAGE READING
        float readADC(); // read voltage on ADC input(not divider input)
        float read(); // get divider input voltage

        // CALCULATIONS
        float calculateInputVoltage(float outputVoltage); // calculate input voltage from divider based on R1, R2 and outputVoltage
        float calculateOutputVoltage(float inputVoltage); // calculate output voltage from divider based on R1, R2 and inputVoltage
        float calculateR1(float inputVoltage, float ouptutVoltage); // calculate R1 value based on R2, input&output voltage
        float calculateR2(float inputVoltage, float outputVoltage); // calculate R2 value based on R1, input&output voltage


};










#endif

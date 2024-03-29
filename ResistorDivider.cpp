#include "ResistorDivider.h"

/// @brief Initialize with all default parameters, set them later using setters
ResistorDivider::ResistorDivider(){}

/// @brief Initialize with R1 and R2 values only
/// @param resistor1 Value of R1 resistor in ohms
/// @param resistor2 Value of R2 resistor in ohms
ResistorDivider::ResistorDivider(float resistor1, float resistor2){
    this->R1 = resistor1;
    this->R2 = resistor2;
}

/// @brief Initialize with all parametrs excluding calibration values
/// @param resistor1 Value of R1 resistor in ohms
/// @param resistor2 Value of R2 resistor in ohms
/// @param pinNumber Pin where divider output is connected(pin needs to be able to read analog signal)
/// @param adcMaxValue Max value of ADC reading from selected pin
/// @param adcMaxVoltage Max ADC voltage on selected pin
/// @param sampleCount Amount of samples from ADC for average calculation
ResistorDivider::ResistorDivider(float resistor1, float resistor2, 
                                 int pinNumber, int adcMaxValue, 
                                 float adcMaxVoltage, int sampleCount){
    this->R1 = resistor1;
    this->R2 = resistor2;
    this->pinNumber = pinNumber;
    this->adcMaxValue = adcMaxValue;
    this->adcMaxVoltage = adcMaxVoltage;
    this->sampleCount = sampleCount;
}

/// @brief Initialize with all parametrs
/// @param resistor1 Value of R1 resistor in ohms
/// @param resistor2 Value of R2 resistor in ohms
/// @param pinNumber Pin where divider output is connected(pin needs to be able to read analog signal)
/// @param adcMaxValue Max value of ADC reading from selected pin
/// @param adcMaxVoltage Max ADC voltage on selected pin
/// @param sampleCount Amount of samples from ADC for average calculation
/// @param adcVoltageMultiplier Voltage measurements are multiplied by this value
/// @param adcVoltageOffset This value will be added to every measurement
ResistorDivider::ResistorDivider(float resistor1, float resistor2, 
                                 int pinNumber, int adcMaxValue, 
                                 float adcMaxVoltage, int sampleCount,
                                 float adcVoltageMultiplier, float adcVoltageOffset){
    this->R1 = resistor1;
    this->R2 = resistor2;
    this->pinNumber = pinNumber;
    this->adcMaxValue = adcMaxValue;
    this->adcMaxVoltage = adcMaxVoltage;
    this->sampleCount = sampleCount;
    this->adcVoltageMultiplier = adcVoltageMultiplier;
    this->adcVoltageOffset = adcVoltageOffset;
}

///////////////////////////////
//          SETTERS          //
///////////////////////////////

/// @brief Set the value of R1 resistor in ohms
/// If the value is zero, the R1 value will not be changed
/// @param value R1 resistance in ohms
void ResistorDivider::setR1(float value){
    if(value != 0) this->R1 = value;
}

/// @brief Set the value of R2 resistor in ohms
/// If the value is zero, the R2 value will not be changed
/// @param value R2 resistance in ohms
void ResistorDivider::setR2(float value){
    if(value != 0) this->R2 = value;
}

/// @brief Set the pin number
/// @param pinNumber Pin number which will be used to read divider output voltage
void ResistorDivider::setPin(int pinNumber){
    this->pinNumber = pinNumber;
}

/// @brief Set the ADC max value
/// If the value is zero, the value will not be changed
/// @param adcMaxValue Max value of ADC reading from the selected pin
void ResistorDivider::setADCMaxValue(int adcMaxValue){
    if(adcMaxValue != 0) this->adcMaxValue = adcMaxValue;
}

/// @brief Set the ADC max voltage
/// If the value is zero, the value will not be changed
/// @param adcMaxVoltage Max voltage of ADC on selected pin
void ResistorDivider::setADCMaxVoltage(float adcMaxVoltage){
    if(adcMaxVoltage != 0) this->adcMaxVoltage = adcMaxVoltage;
}

/// @brief Set ADC voltage multiplier
/// @param adcVoltageMultiplier Value by which every measurement is multiplied
void ResistorDivider::setADCMultiplier(float adcVoltageMultiplier){
    this->adcVoltageMultiplier = adcVoltageMultiplier;
}

/// @brief Set ADC voltage offset
/// @param adcVoltageOffset Value added to every measurement
void ResistorDivider::setADCOffset(float adcVoltageOffset){
    this->adcVoltageOffset  = adcVoltageOffset;
}

/// @brief Set sample count
/// @param sampleCount Amount of samples when calculating average
void ResistorDivider::setSampleCount(int sampleCount){
    this->sampleCount = sampleCount;
}


///////////////////////////////
//          GETTERS          //
///////////////////////////////

/// @brief Get value of R1 resistor in ohms
float ResistorDivider::getR1(){
    return this->R1;
}

/// @brief Get value of R2 resistor in ohms
float ResistorDivider::getR2(){
    return this->R2;
}

/// @brief Get pin number
int ResistorDivider::getPin(){
    return this->pinNumber;
}

/// @brief Get ADC max value
int ResistorDivider::getADCMaxValue(){
    return this->adcMaxValue;
}

/// @brief Get ADC max voltage
float ResistorDivider::getADCMaxVoltage(){
    return this->adcMaxVoltage;
}

/// @brief Get ADC voltage multiplier
float ResistorDivider::getADCMultiplier(){
    return this->adcVoltageMultiplier;
}

/// @brief Get ADC voltage offset
float ResistorDivider::getADCOffset(){
    return this->adcVoltageOffset;
}

/// @brief Get sample count
int ResistorDivider::getSampleCount(){
    return this->sampleCount;
}

////////////////////////////////////////
//          VOLTAGE READINGS          //
////////////////////////////////////////

/// @brief Returns voltage on ADC input pin
/// Before returning the measurement result, voltage multiplier and offset are applied
float ResistorDivider::readADC(){
    unsigned long readingSum = 0;
    for(int i = 0; i < this->sampleCount; i++){
        readingSum += analogRead(this->pinNumber);
    }
    int adcReading = readingSum / this->sampleCount;
    float adcVoltage = ((float)adcReading * this->adcMaxVoltage) / ((float)this->adcMaxValue);
    adcVoltage *= this->adcVoltageMultiplier;
    adcVoltage += this->adcVoltageOffset;
    return adcVoltage;
}

/// @brief Returns voltage at the resistor divider input
float ResistorDivider::read(){
    float outVoltage = this->readADC();
    float inVoltage = this->calculateInputVoltage(outVoltage);
    return inVoltage;
}

////////////////////////////////////
//          CALCULATIONS          //
////////////////////////////////////

/// @brief Calculates input voltage based on outputVoltage, R1 and R2 values
/// @param outputVoltage Output voltage from the divider
float ResistorDivider::calculateInputVoltage(float outputVoltage){
    float inputVoltage = (outputVoltage * (this->R1 + this->R2)) / this->R2;
    return inputVoltage;
}

/// @brief Calculates output voltage based on inputVoltage, R1 and R2 values
/// @param inputVoltage Divider input voltage
float ResistorDivider::calculateOutputVoltage(float inputVoltage){
    float outputVoltage = (inputVoltage * this->R2) / (this->R1 + this->R2);
    return outputVoltage;
}

/// @brief Calculates R1 value based on input voltage, output voltage and R2 value
/// @param inputVoltage Divider input voltage
/// @param outputVoltage Divider output voltage
float ResistorDivider::calculateR1(float inputVoltage, float outputVoltage){
    float r1 = (this->R2 * (inputVoltage - outputVoltage)) / outputVoltage;
    return r1;
}

/// @brief Calculates R2 value based on input voltage, output voltage and R1 value
/// @param inputVoltage Divider input voltage
/// @param outputVoltage Divider output voltage
float ResistorDivider::calculateR2(float inputVoltage, float outputVoltage){
    float r2 = (outputVoltage * this->R1) / (inputVoltage - outputVoltage);
    return r2;
}


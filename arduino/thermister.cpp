#include "thermistor.h“
// Temperature for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25 
// Number of ADC samples
#define NUMSAMPLES              5
#define ADC_RESOLUTION         4095

THERMISTOR::THERMISTOR(uint8_t adcPin, uint16_t nomRes, uint16_t bCoef, uint16_t serialRes) {    
  analogPin = adcPin;  
  nominalResistance = nomRes;  
  bCoefficient = bCoef;  
  serialResistance = serialRes;
}
int THERMISTOR::read(void){  
  uint8_t i;  uint16_t sample;  float average = 0; 
  for (i=0; i< NUMSAMPLES; i++)  {    
        sample = analogRead(analogPin);    
        average += sample;    delay(10);  
  }  
  average /= NUMSAMPLES;
  average = ADC_RESOLUTION / average - 1;  
  average = serialResistance * average;
  float steinhart = average / nominalResistance;     // (R/Ro)
  steinhart = log(steinhart);                                 // ln(R/Ro)
  steinhart /= bCoefficient;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)  
  steinhart = 1.0 / steinhart;                 // Invert  
  steinhart -= 273.15;                         // convert to C
  return (int)(steinhart * 10);
}

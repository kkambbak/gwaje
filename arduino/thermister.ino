#include "thermistor.h"
// Analog pin used to read the NTC
#define NTC_PIN               36

// Thermistor object
THERMISTOR thermistor(NTC_PIN,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

// Global temperature reading
uint16_t temp; void setup()
{
  Serial.begin(115200);
}
 void loop()
{
  temp = thermistor.read();   // Read temperature

  Serial.print("Temp in 1/10 ºC : ");
  Serial.println(temp);

  delay(5000);
}

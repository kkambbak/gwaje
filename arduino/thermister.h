#include "Arduino.h“
#define DEFAULT_NUM_SAMPLES  10
#define DEFAULT_BCOEF        3950
#define DEFAULT_NOMINAL_RES 10000
#define DEFAULT_NOMINAL_RES 10000
class THERMISTOR { 
   public:    
   /**     * Nominal resistance     */    
   uint16_t nominalResistance;    
   /**     * Serial resistance     */    
   uint16_t serialResistance;     
   /**     * Analog pin     */    
   uint16_t analogPin;    
  /**     * Beta coefficient of the thermistor     */    
   uint16_t bCoefficient;    
  /**     * THERMISTOR     *      * Class constructor     *     * 
     @param adcPin Analog pin where the thermistor is connected     * 
     @param nomRes Nominal resistance at 25 degrees Celsius     * 
     @param bCoef beta coefficient of the thermistor     * 
     @param serialRes Value of the serial resistor     */ 
    THERMISTOR(uint8_t adcPin, uint16_t nomRes, uint16_t bCoef, uint16_t serialRes);    
    /**     * read     *     * Read temperature from thermistor     *     * 
         @return temperature in 0.01 ºC     */    
    int read(void);
};

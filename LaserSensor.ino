#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;


// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

//#define LONG_RANGE


// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

//#define HIGH_SPEED
#define HIGH_ACCURACY


/*
Board: Firebeetle ESP32
SDA：I2C’s data-wire, connect to IO21 of ESP32.
SCL：Clock pin of I2C, connect to IO22 of ESP32.
GND to GND
VIN to 3V3
*/


void laserSensorSetup()
{
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
  Serial.println("Laser Sensor setup complete");
}

int laserSensor() {
  
  Serial.print("LaserSensor Distance [cm]: ");
  Serial.println(sensor.readRangeSingleMillimeters() / 10);
  if (sensor.timeoutOccurred()) { 
    Serial.print(" TIMEOUT"); 
    return 0;
  }
  return sensor.readRangeSingleMillimeters() / 10;
  
}

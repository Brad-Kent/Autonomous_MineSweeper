#include <Arduino.h>
#include <Magnetometer.h>

Magnetometer magnetometer;
void setup(void)
{
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");

  /* Initialise the sensor */
  if(!magnetometer.mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }

  /* Display some basic information on this sensor */
  magnetometer.displaySensorDetails();
}


void loop()
{
    magnetometer.readMag();
}

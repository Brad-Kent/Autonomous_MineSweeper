#include <Arduino.h>
#include <Wire.h>
#include <math.h>

int HMC5883L_ADDRESS = 0x3C>> 1;
int CONFIGURATION_REGISTERB=0x01;
int MODE_REGISTER=0x02;
int DATA_REGISTER_BEGIN=0x03;
int MODE_INSTRUCTION=0x00; //Continuous-Measurement Mode
int REGISTERB_INSTRUCTION=0x40;//± 1.9 Ga Gain
int RawDATA[6];  //Array used for storing the raw data reading from X, Y and Z data resister


class Magnetometer
{
public:
    int getDirection()
    {
       int i,XAxis,YAxis,ZAxis;
       double angle;
       delay(100);
       //Set the Mode Register
       Wire.beginTransmission(HMC5883L_ADDRESS);
       Wire.write(MODE_REGISTER);
       Wire.write(MODE_INSTRUCTION);
       Wire.endTransmission();
       delay(10);

       //Set Configuration Register B
       Wire.beginTransmission(HMC5883L_ADDRESS);
       Wire.write(CONFIGURATION_REGISTERB);
       Wire.write(REGISTERB_INSTRUCTION);
       Wire.endTransmission();
       delay(10);

       //Read data from Data Register 03H-08H
       Wire.beginTransmission(HMC5883L_ADDRESS);
       Wire.write(DATA_REGISTER_BEGIN);
       Wire.endTransmission();
       Wire.requestFrom(HMC5883L_ADDRESS,6);
       delay(100);
       if(6<= Wire.available())    // if 6 bytes were received
      {
        for(i=0;i<6;i++)
        {
          RawDATA[i]=Wire.read();
         }
      }
       //Get the raw data of X axis and Y axis
       XAxis=RawDATA[0]*256+RawDATA[1];
       YAxis=RawDATA[4]*256+RawDATA[5];

       //Calculate the angle between X axis and the South Direction
       angle=atan2((double)YAxis,(double)XAxis)*180/3.14+180;
       Serial.println("The angle between X axis and the South direction");
       Serial.println(angle,2);
       delay(10);
    }
    int getMagneticReading();

private:
    int direction;
    int MagneticReading;
    // Put in pins
};

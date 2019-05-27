#include <Arduino.h>
//  Compass v1.0b_testcode
#include <Wire.h>
#include <math.h>

int QMC5883L_ADDRESS = 0x1A>> 1;

int SET_RESET_PERIOD_REGISTER=0x0B;
int SET_RESET_PERIOD_REGISTER_INSTRUCTION=0x01;
int CONTROL_REGISTER_1=0x09;
int CONTROL_REGISTER_1_INSTRUCTION=0x0D; //Continus Measurment Mode and 200HZ data output rate
int DATA_REGISTER_BEGIN=0x00;
int RawDATA[6];  //Array used for storing the raw data reading from X, Y and Z data resister

class Magnetometer
{
    void getData()
     {
       int i,XAxis,YAxis,ZAxis;
       double angle;
       delay(100);
       //Set the SET/RESET Period Register
       Wire.beginTransmission(QMC5883L_ADDRESS);
       Wire.write(SET_RESET_PERIOD_REGISTER);
       Wire.write(SET_RESET_PERIOD_REGISTER_INSTRUCTION);
       Wire.endTransmission();
       delay(10);

       //Set Configuration Register 1
       Wire.beginTransmission(QMC5883L_ADDRESS);
       Wire.write(CONTROL_REGISTER_1);
       Wire.write(CONTROL_REGISTER_1_INSTRUCTION);
       Wire.endTransmission();
       delay(10);

       //Read data from Data Register 00H-05H
       Wire.beginTransmission(QMC5883L_ADDRESS);
       Wire.write(DATA_REGISTER_BEGIN);
       Wire.endTransmission();
       Wire.requestFrom(QMC5883L_ADDRESS,6);
       delay(100);

      if(6<= Wire.available())    // if 6 bytes were received
      {
        for(i=0;i<6;i++)
        {
            RawDATA[i]=Wire.read();
            Serial.print(RawDATA[i]);
            Serial.print(" : ");
        }
           Serial.println();
        }
       //Get the raw data of X axis and Y axis
       XAxis=RawDATA[1]*256+RawDATA[0];
       YAxis=RawDATA[3]*256+RawDATA[2];

       //Calculate the angle between X axis and the South Direction
       angle=atan2((double)YAxis,(double)XAxis)*180/3.14+180;
       // Serial.println("The angle between X axis and the South direction");
       // Serial.println(angle,2);
       delay(1000);
    }
};

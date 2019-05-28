#include <Arduino.h>
#include <Magnetometer.h>
#include <DriveSystem.h>
#include <Servo.h>
#include <Ultrasonic.h>

void fucntionTest();
void calabrateMag();
Magnetometer magnetometer;
Ultrasonic sonic(4,5);
Servo servo;
DriveSystem driveSystem(12, 13, 10, 11);

void setup(void)
{
  //Serial.begin(9600);

  // Magnetometer...
  // Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  // if(!magnetometer.mag.begin())
  // {
  //   Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
  //   while(1);
  // }  magnetometer.displaySensorDetails();

  servo.attach(3);
  servo.write(90);
}

void loop()
{
    calabrateMag();
    fucntionTest();
}

bool inRangeOfMine = false;
int xTarget = -370; // +- 50
int distances[] = {0, 0, 0};
int botDirection = 0;

void fucntionTest()
{
    magnetometer.readMag();
    int temp = magnetometer.event.magnetic.x;

    if(temp >= (xTarget+50) && temp <= (xTarget-50))
    {
        inRangeOfMine = true;
    }

    botDirection = magnetometer.headingDegrees;

    // Get Dir and Distances
    int servoAngle = 0;
    servo.write(0);
    for(int i = 0; i < 3; i++)
    {
        sonic.ping();
        distances[i] = sonic.getDistance();
        servo.write(servoAngle);
        servoAngle += 90;
    }
}

void pinPointMine()
{
    int readings[] = {0,0,0};
    driveSystem.turnLeft();

    for(int i = 0; i < 3; i++)
    {
        driveSystem.turnRight();
        delay(500);
        magnetometer.readMag();
        readings[i] = magnetometer.event.magnetic.x;

    }
}
void calabrateMag()
{
    int turnTime = 6000;
    driveSystem.turnLeft();
    delay(turnTime);
    driveSystem.turnRight();
    delay(turnTime);
}

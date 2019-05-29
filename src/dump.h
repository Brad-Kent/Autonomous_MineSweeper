#include <Arduino.h>

void servoAndSonic()
{
    int delayLen = 1000;
    Serial.println(sonic.getDistance());
    delay(delayLen);
    sonicServo.write(0);
    Serial.println(sonic.getDistance());
    delay(delayLen);
    sonicServo.write(90);
    Serial.println(sonic.getDistance());
    delay(delayLen);
    sonicServo.write(180);
    Serial.println(sonic.getDistance());
    delay(delayLen);
    sonicServo.write(90);
    Serial.println(sonic.getDistance());
    delay(delayLen);
}

bool inRangeOfMine = false;
int xTarget = 370;
int distances[] = {0, 0, 0};
int botDirection = 0;

void fucntionTest()
{
    magnetometer.readMag();
    int temp = magnetometer.x;

    if(temp >= (xTarget+50) && temp <= (xTarget-50))
    {
        inRangeOfMine = true;
    }
    botDirection = magnetometer.headingDegrees;

    // Get Dir and Distances
    int servoAngle = 0;
    for(int i = 0; i < 3; i++)
    {
        sonic.ping();
        distances[i] = sonic.getDistance();
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
        readings[i] = magnetometer.x;
    }
}

void calabrateMag()
{
    int turnTime = 6000;
    driveSystem.turnLeft();
    delay(turnTime);
    driveSystem.turnRight();
    delay(turnTime);
    driveSystem.stop();
}

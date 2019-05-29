#include <Arduino.h>
#include <SparkFun_MAG3110.h>
#include <DriveSystem.h>
#include <Ultrasonic.h>
#include <AFMotor.h>
#include <Servo.h>


MAG3110 mag           = MAG3110    ();
DriveSystem motors    = DriveSystem(12, 13, 10, 11);
Ultrasonic ultrasonic = Ultrasonic (2, 3);
Servo servoUltrasonic = Servo      ();
Servo servoMarking    = Servo      ();

int testMode = 4;
int led      = 3;

int distances[]   = {0, 0, 0}; // Foward, Right, Left
int servoAngles[] = {90, 180, 0};

int detectionDistance = 30;
int turnTime = 2000;
int travelTime = 2000;

int checkDirection(int angle);
int getDirection();
void updateDistances();
void demoFunctions();

void setup()
{
    servoUltrasonic.attach(7);
    servoMarking   .attach(6);
    servoUltrasonic.write(90);
    servoMarking   .write(90);

    mag.initialize(); //Initializes the mag sensor
    mag.start     (); //Puts the sensor in active mode
}

void loop()
{

    if(digitalRead(testMode)) demoFunctions();

    // Update Distance
    motors.stop();
    updateDistances();

    // Update Direction
    getDirection();
    if (1)
    {
        motors.goBackwards();
        delay(travelTime);
    }
    else if(2)
    {
        motors.turnLeft();
        delay(turnTime);
    }
    else if(3)
    {
        motors.turnRight();
        delay(turnTime);
    }
    else
    {
        motors.goFoward();
    }

    // Detect for Landmines
    if(magDetect())
    {
        digitalWrite(led, HIGH);
        markLandmine();
        motors.goBackwards();
        delay(travelTime);
    }

}

void updateDistances()
{
    for(int i=0; i < (sizeof(distances)); i++)
        distances[i] = checkDirection(servoAngles[i]);
}

int getDirection()
{
    if (distances[0] < detectionDistance)
        return 1; // Go Back
    else if(distances[1] >= distances[2])
        return 2; // Go Right
    else if(distances[2] > distances[1])
        return 3; // Go Left
    else
        return 0; // Go Foward
}

int checkDirection(int angle)
{
    servoUltrasonic.write(angle);
    delay(400);
    return ultrasonic.getDistance();
}

bool mag_detect()
{
    int x, y, z;
    if(mag.dataReady())
    {
        mag.readMag(&x, &y, &z);
        if(z <= -2400)
            return true;
    }
    else
    {
        return false;
    }
}

void marLandmine()
{
    servoMarking.write(0 ); delay(400);
    servoMarking.write(90); delay(400);
}

void demoFunctions()
{
    int duration = 2000;
    motors.goFoward   (); delay(duration);
    motors.goBackwards(); delay(duration);
    motors.turnLeft   (); delay(duration);
    motors.turnRight  (); delay(duration);

    checkDirection(0  ); delay(duration/2);
    checkDirection(180); delay(duration/2);
    checkDirection(90 ); delay(duration/2);
}

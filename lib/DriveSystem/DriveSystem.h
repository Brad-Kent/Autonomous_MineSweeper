#include <Arduino.h>

#define FOWARD HIGH
#define BACKWARD LOW

class DriveSystem
{
private:
    const int MotorA;
    const int MotorB;
    const int MotorASpeed;
    const int MotorBSpeed;

public:
    DriveSystem(int MotorA, int MotorB, int MotorASpeed, int MotorBSpeed):
        MotorA{MotorA}, MotorB{MotorB}, MotorASpeed{MotorASpeed}, MotorBSpeed{MotorBSpeed}
    {
        pinMode(MotorA, OUTPUT);
        pinMode(MotorB, OUTPUT);
        pinMode(MotorASpeed, OUTPUT);
        pinMode(MotorBSpeed, OUTPUT);
    }

    void stop()
    {
        digitalWrite(MotorASpeed, LOW);
        digitalWrite(MotorBSpeed, LOW);
    }

    void turnRight()
    {
        digitalWrite(MotorA, FOWARD);
        digitalWrite(MotorB, BACKWARD);
        activateMotors();
    }

    void turnLeft()
    {
        digitalWrite(MotorA, BACKWARD);
        digitalWrite(MotorB, FOWARD);
        activateMotors();
    }

    void goFoward()
    {
        digitalWrite(MotorA, FOWARD);
        digitalWrite(MotorB, FOWARD);
        activateMotors();
    }

    void goBackwards()
    {
        digitalWrite(MotorA, BACKWARD);
        digitalWrite(MotorB, BACKWARD);
        activateMotors();
    }

private:
    void activateMotors()
    {
        digitalWrite(MotorASpeed, HIGH);
        digitalWrite(MotorBSpeed, HIGH);
    }
    void setDirection(int motor, int direction)
    {

    }
};

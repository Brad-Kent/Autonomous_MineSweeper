
#include <DriveSystem.h>
#include <Arduino.h>
/*
    TODO: Make the go/backwards and possibly turing etc available to analogwrite if we ever use software speed control!
*/
#define FOWARD HIGH  // Try this with true & false & go /stop = 1 function with parameter and ! op
#define BACKWARD LOW

DriveSystem::DriveSystem(int MotorA, int MotorB, int MotorASpeed, int MotorBSpeed):
    MotorA{MotorA}, MotorB{MotorB}, MotorASpeed{MotorASpeed}, MotorBSpeed{MotorBSpeed}
{
    // Set AVR Pins Mode
    pinMode(MotorA, OUTPUT);
    pinMode(MotorB, OUTPUT);
    pinMode(MotorASpeed, OUTPUT);
    pinMode(MotorBSpeed, OUTPUT);
}

/*
    NOTE: do i need to call go everytime? i think changing the direction and leving the current on/off will be fine
*/
void DriveSystem::go()
{
    digitalWrite(MotorASpeed, HIGH);
    digitalWrite(MotorBSpeed, HIGH);
}

void DriveSystem::stop()
{
    digitalWrite(MotorASpeed, LOW);
    digitalWrite(MotorBSpeed, LOW);
}

void DriveSystem::goFoward()
{
    setDirection(FOWARD);
    go();
}

void DriveSystem::goBackwards()
{
    setDirection(BACKWARD);
    go();
}

void DriveSystem::turnRight()
{
    setDirection(FOWARD, BACKWARD);
    go();
}

void DriveSystem::turnLeft()
{
    setDirection(BACKWARD, FOWARD);
    go();
}

void DriveSystem::setDirection(int direction)
{
    setDirection(direction, direction);
}
void DriveSystem::setDirection(int directionA, int directionB)
{
    setDirection(MotorA, directionA, MotorB, directionB);
}
void DriveSystem::setDirection(int motorA, int directionA, int motorB, int directionB)
{
    digitalWrite(motorA, directionA);
    digitalWrite(motorB, directionB);
}

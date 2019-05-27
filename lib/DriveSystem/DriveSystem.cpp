
#include <DriveSystem.h>
#include <Arduino.h>

#define FOWARD HIGH
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


void DriveSystem::stop()
{
    digitalWrite(MotorASpeed, LOW);
    digitalWrite(MotorBSpeed, LOW);
}

void DriveSystem::goFoward()
{
    digitalWrite(MotorA, FOWARD);
    digitalWrite(MotorB, FOWARD);
    activateMotors();
}

void DriveSystem::goBackwards()
{
    digitalWrite(MotorA, BACKWARD);
    digitalWrite(MotorB, BACKWARD);
    activateMotors();
}

void DriveSystem::turnRight()
{
    digitalWrite(MotorA, FOWARD);
    digitalWrite(MotorB, BACKWARD);
    activateMotors();
}

void DriveSystem::turnLeft()
{
    digitalWrite(MotorA, BACKWARD);
    digitalWrite(MotorB, FOWARD);
    activateMotors();
}


void DriveSystem::activateMotors()
{
    digitalWrite(MotorASpeed, HIGH);
    digitalWrite(MotorBSpeed, HIGH);
}

void DriveSystem::setDirection(int motor, int direction)
{
    digitalWrite(motor, direction);
}

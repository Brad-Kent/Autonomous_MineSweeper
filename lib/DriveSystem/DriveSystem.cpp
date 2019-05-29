
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

<<<<<<< HEAD
=======
/*
    NOTE: do i need to call go everytime? i think changing the direction and leving the current on/off will be fine
*/
void DriveSystem::go()
{
    digitalWrite(MotorASpeed, HIGH);
    digitalWrite(MotorBSpeed, HIGH);
}
>>>>>>> refactor

void DriveSystem::stop()
{
    digitalWrite(MotorASpeed, LOW);
    digitalWrite(MotorBSpeed, LOW);
}

void DriveSystem::goFoward()
{
<<<<<<< HEAD
    digitalWrite(MotorA, FOWARD);
    digitalWrite(MotorB, FOWARD);
    activateMotors();
=======
    setDirection(FOWARD, BACKWARD);
    go();
>>>>>>> refactor
}

void DriveSystem::goBackwards()
{
<<<<<<< HEAD
    digitalWrite(MotorA, BACKWARD);
    digitalWrite(MotorB, BACKWARD);
    activateMotors();
=======
    setDirection(BACKWARD, FOWARD);
    go();
>>>>>>> refactor
}

void DriveSystem::turnRight()
{
<<<<<<< HEAD
    digitalWrite(MotorA, FOWARD);
    digitalWrite(MotorB, BACKWARD);
    activateMotors();
=======
    setDirection(FOWARD);
    go();
>>>>>>> refactor
}

void DriveSystem::turnLeft()
{
<<<<<<< HEAD
    digitalWrite(MotorA, BACKWARD);
    digitalWrite(MotorB, FOWARD);
    activateMotors();
}


void DriveSystem::activateMotors()
=======
    setDirection(BACKWARD);
    go();
}

void DriveSystem::setDirection(int direction)
>>>>>>> refactor
{
    setDirection(direction, direction);
}
<<<<<<< HEAD

void DriveSystem::setDirection(int motor, int direction)
{
    digitalWrite(motor, direction);
=======
void DriveSystem::setDirection(int directionA, int directionB)
{
    setDirection(MotorA, directionA, MotorB, directionB);
}
void DriveSystem::setDirection(int motorA, int directionA, int motorB, int directionB)
{
    digitalWrite(motorA, directionA);
    digitalWrite(motorB, directionB);
>>>>>>> refactor
}

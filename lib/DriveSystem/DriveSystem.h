#pragma once

class DriveSystem
{
private:
    const int MotorA;
    const int MotorB;
    const int MotorASpeed;
    const int MotorBSpeed;

public:
    DriveSystem(int MotorA, int MotorB, int MotorASpeed, int MotorBSpeed);
    void stop();
    void turnRight();
    void turnLeft();
    void goFoward();
    void goBackwards();
    void go();
    
private:
    void DriveSystem::setDirection(int direction);
    void DriveSystem::setDirection(int directionA,int directionB);
    void DriveSystem::setDirection(int motorA, int directionA, int motorB, int directionB);
};

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

private:
    void activateMotors();
    void setDirection(int motor, int direction);
};

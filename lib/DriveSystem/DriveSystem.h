#pragma once

class DriveSystem
{
private:
    const int MotorA;
    const int MotorB;
    const int MotorASpeed;
    const int MotorBSpeed;

    int userSpecified;

public:
    DriveSystem(int MotorA, int MotorB, int MotorASpeed, int MotorBSpeed);

    void stop();
    void goFoward   ();
    void goBackwards();
    void turnRight();
    void turnLeft ();


private:
    void activateMotors();
    void setDirection(int motor, int direction);
};

#include <Arduino.h>

class Ultrasonic
{
public:
    Ultrasonic(int trigPin, int echoPin):
        trigPin{trigPin}, echoPin{echoPin}
    {
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }

    int getDistance()
    {
        return this->distance;
    }

    void ping()
    {
        int duration;
        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);

        // Calculating the distance
        distance = duration*0.034/2;

        // Prints the distance on the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(distance);
    }

    // These Require servo
    void checkRight();
    void checkLeft();

private:
    const int trigPin;
    const int echoPin;
    int distance;
};

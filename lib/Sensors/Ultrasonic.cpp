#include <Ultrasonic.h>
#include <Arduino.h>

Ultrasonic::Ultrasonic(int trigPin, int echoPin):
    trigPin{trigPin}, echoPin{echoPin}
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    distance = 0;
}

double Ultrasonic::getDistance()
{
    return distance;
}

void Ultrasonic::ping()
{
    int duration;

    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Send sonic wave for 10ms
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // echoPin:wave input, pulseIn: returns sonic-wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = (duration*0.034)/2;
}

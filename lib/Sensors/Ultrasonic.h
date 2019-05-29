class Ultrasonic
{
public:
    Ultrasonic(int trigPin, int echoPin);
    int getDistance();
    void ping();

private:
    const int trigPin;
    const int echoPin;
    int distance;
};

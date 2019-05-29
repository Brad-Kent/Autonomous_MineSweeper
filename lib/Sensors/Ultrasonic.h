class Ultrasonic
{
public:
    Ultrasonic(int trigPin, int echoPin);
    double getDistance();
    void ping();
    
private:
    const int trigPin;
    const int echoPin;
    double distance;
};

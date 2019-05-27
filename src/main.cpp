#include <Arduino.h>
#include <DriveSystem.h>
#include <String.h>


String name("Hello");

void logme(String reply)
{
    Serial.print("Hello There ");
    Serial.println(reply);
}

void setup()
{
    Serial.begin(9600);

}
void loop()
{
    DriveSystem drive(1,2,3,4);
    drive.goBackwards();
    logme("Main");
    delay(1000);
}

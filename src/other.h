#include <main.h>
#include <AFMotor.h>
#include <Servo.h>
#include <SparkFun_MAG3110.h>
#include <AFMotor.h>

MAG3110 mag = MAG3110(); //Instantiate MAG3110
Servo servo_1;
Servo servo_2;
AF_DCMotor motor_left(3);
AF_DCMotor motor_right(4);
int fast_speed = 200;
int normal_speed = 150;
int turn_speed = 80;
int turn_time = 500;
int reverse_distance = 600;
int detect_distance = 30;
int x_min = 0;
int x_max = 0;
int y_min = 0;
int y_max = 0;
int z_min = 0;
int z_max = 0;
int mode = HIGH;
int standard_delay = 500;
int us_echo = A0; // define ultrasonic receive pin(Echo)
int us_trig = A1; // define ultrasonic sendpin(Trig)
int mode_pin = A2; // define mode select switch
int buzzer = A3;
int forward_distance = 0; // forward distance
int right_distance = 0; // right distance
int left_distance = 0; // left distance
int direction_choice = 0; // sets the directionchoice

// possible direction
int choose_forward = 8;
int choose_right = 6;
int choose_left = 4;
int choose_back = 2;


void setup()
{
    Serial.begin(9600);
    Serial.println("Team Yellow Landmine Detector Initialise...");
    pinMode(us_echo, INPUT);
    pinMode(us_trig, OUTPUT);
    pinMode(mode_pin, INPUT);
    pinMode(buzzer, OUTPUT);
    servo_1.attach(10);
    servo_2.attach(9);
    motor_left.setSpeed(20);
    motor_right.setSpeed(20);
    motor_left.run(RELEASE);
    motor_right.run(RELEASE);
    mag.initialize(); //Initializes the mag sensor
    mag.start();      //Puts the sensor in active mode
}

void set_mode()
{
  mode = digitalRead(mode_pin);
}
void mag_detect()
{
    int x, y, z;
    //Only read data when it's ready
    if(mag.dataReady())
    {
        //Read the data
        mag.readMag(&x, &y, &z);
        if(z <= -2400)
        {
            back();
            pause();
            digitalWrite(LED_BUILTIN, HIGH);
            tone(buzzer, 700, 600);
            Serial.print(" Landmine Detected ");
            mark_landmine();
            back();
            delay(standard_delay);
            turn_left();
            delay(standard_delay);
            Serial.print(" Avoiding Landmine... ");
        }
    }
}
void mag_detect_simple()
{
    int x, y, z;
    //Only read data when it's ready
    if(mag.dataReady())
    {
        //Read the data
        mag.readMag(&x, &y, &z);
        if(y <= y_min || y >= y_max || x <= x_min || x
        >= x_max || z <= z_min || z >= z_max)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            tone(buzzer, 700, 600);
            Serial.print(" Landmine Detected ");
        }
    }
}

void wall_detection()
{
  delay(250);
  test_forward_d();
  if(forward_distance < detect_distance)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    tone(buzzer, 2000, 400);
  }
  else
  {
      direction_choice = 1;
  }
}
void mark_landmine()
{
  Serial.print(" Marking Landmine... ");
  int pos;
  for (pos = 0; pos <= 90; pos += 1)
   {
        servo_1.write(pos);
        delay(15);
    }
  for (pos = 90; pos >= 0; pos -= 1)
   {
    servo_1.write(pos);
    delay(15);
    }
  Serial.print(" Landmine Marked ");
}

void advance()
{
  motor_left.setSpeed(normal_speed);
  motor_right.setSpeed(normal_speed);
  motor_left.run(FORWARD);
  motor_right.run(FORWARD);
  delay(600);
  motor_left.setSpeed(normal_speed);
  motor_right.setSpeed(normal_speed);
}
void turn_left()
{
  motor_left.setSpeed(turn_speed);
  motor_right.setSpeed(turn_speed);
  motor_left.run(BACKWARD);
  motor_right.run(FORWARD);
  delay(turn_time);
  motor_left.setSpeed(normal_speed);
  motor_right.setSpeed(normal_speed);
}
void turn_right()
{
  motor_left.setSpeed(turn_speed);
  motor_right.setSpeed(turn_speed);
  motor_left.run(FORWARD);
  motor_right.run(BACKWARD);
  delay(turn_time);
  motor_left.setSpeed(normal_speed);
  motor_right.setSpeed(normal_speed);
}
void pause()
{
  motor_left.run(RELEASE);
  motor_right.run(RELEASE);
  delay(250);
}
void back()
{
  motor_left.setSpeed(normal_speed);
  motor_right.setSpeed(normal_speed);
  motor_left.run(BACKWARD);
  motor_right.run(BACKWARD);
  delay(reverse_distance);
  motor_left.setSpeed(normal_speed);
  motor_right.setSpeed(normal_speed);
}
void test_forward_d()
{
    // test forward distance
    servo_2.write(90);
    digitalWrite(us_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(us_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(us_trig, LOW);
    float f_distance = pulseIn(us_echo, HIGH);
    f_distance = f_distance/29/2; //Speed of sound adjustment(29.155 microseconds per centimeter);
    //https://stackoverflow.com/questions/41501360/getting-distance-in-inches-and-cm-from-ultrasonic-sensor-in-arduino
    // debugging print to console
    Serial.print("Forward distance:");
    Serial.println(f_distance);
    forward_distance = f_distance;
}
void test_left_d()
{
   // test left distance
   servo_2.write(160);
   delay(250);
   digitalWrite(us_trig, LOW);
   delayMicroseconds(2);
   digitalWrite(us_trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(us_trig, LOW);
   float l_distance = pulseIn(us_echo, HIGH);
   l_distance = l_distance/5.8/10;
   // debugging print
   Serial.print("Left distance:");
   Serial.println(l_distance);
   left_distance = l_distance;
}
void test_right_d()
{
   // test right distance
   servo_2.write(30);
   delay(250);
   digitalWrite(us_trig, LOW);
   delayMicroseconds(2);
   digitalWrite(us_trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(us_trig, LOW);
   float r_distance = pulseIn(us_echo, HIGH);
   r_distance = r_distance/5.8/10;
   // debugging print
   Serial.print("Right distance:");
   Serial.println(r_distance);
   right_distance = r_distance;
}
void pause(int pause_time)
{
  motor_left.run(RELEASE);
  motor_right.run(RELEASE);
  delay(pause_time);
}
void obj_detect()
{
  //test the distance of different directions
  delay(50);
  test_forward_d();
  if(forward_distance < detect_distance)
  {
    pause(10);
    digitalWrite(LED_BUILTIN, HIGH);
    tone(buzzer, 2000, 400);
    back();
  }
  if(forward_distance < detect_distance+10)
  {
    back();
    pause();
    test_left_d();
    delay(50);
    test_right_d();
    delay(50);
    servo_2.write(90);
    delay(50);
    if(left_distance < right_distance)
    {
      direction_choice = choose_right;
    }
    if(left_distance > right_distance)
    {
      direction_choice = choose_left;
    }
    if (left_distance < 10 && right_distance < 10)
    {
      direction_choice = choose_back;
    }
    }
    else
    {
      direction_choice = choose_forward;
    }
}

void test_functions()
{
    Serial.println("Test mode activated: Prepare for simulation");
    tone(buzzer, 1000, 500);
    delay(standard_delay);
    advance();
    delay(standard_delay);
    pause(250);
    back();
    delay(standard_delay);
    pause(250);
    turn_left();
    delay(standard_delay);
    pause(250);
    turn_right();
    delay(standard_delay);
    pause(100);
    turn_right();
    delay(standard_delay);
    pause(250);
    turn_left();
    delay(standard_delay);
    pause(250);
    tone(buzzer, 1500, 600);
    delay(standard_delay);
    test_left_d();
    test_right_d();
    delay(standard_delay);
    servo_2.write(90);
    delay(standard_delay);
    tone(buzzer, 2000, 700);
    int i;
    for(i = 0 ; i <= 1000; i+=2)
    {
        wall_detection();
        mag_detect_simple();
        delay(30);
    }
}

void loop()
{
    servo_2.write(90); //reset servo to midline
    set_mode(); //test mode switch
    if(mode == HIGH) //Run test mode
    {
      test_functions();
    }
    else //Run normal mode
    {
         Serial.println("Run mode activated: Now searching for landmines...");
          mag_detect();
          obj_detect();
        if(direction_choice == 2)
        {
          back();
          turn_left();
          Serial.print(" Reverse ");
        }
        if(direction_choice == 6)
        {
          back();
          turn_right();
          Serial.print(" Right ");
        }
        if(direction_choice == 4)
        {
          back();
          turn_left();
          Serial.print(" Left ");
        }
        if(direction_choice == 8)
        {
          advance();
          Serial.print(" Advance ");
          Serial.print(" ");
      }
    }
}

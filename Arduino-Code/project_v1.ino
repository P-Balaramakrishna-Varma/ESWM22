#include <Timer.h>

#define number_of_holes 20
#define interruptPin 13

Timer t;
int i = 0;

// Motor A
int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;

// Setting PWM properties
const int freq = 5000;
const int pwmChannel = 0;
const int resolution = 8;
int motor_speed;


void setup()
{
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), counter, RISING);
    t.every(500, print_speed);

    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);

  
    // attach the channel to the GPIO to be controlled
    ledcSetup(pwmChannel, freq, resolution);

    ledcAttachPin(enable1Pin, pwmChannel);

    Serial.begin(115200);
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
     ledcWrite(pwmChannel, motor_speed);
    // testing
    Serial.print("Testing DC Motor...");
}

void loop()
{
    t.update(); // for rpm sensing

    // Move DC motor forward with increasing speed

    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    // analogWrite(enable1Pin, motor_speed);
    if(Serial.available())
    {
        motor_speed = (Serial.readString()).toInt();
        ledcWrite(pwmChannel, motor_speed);
    }

    Serial.print("motor speed : ");
    Serial.println(motor_speed);
    delay(1000);
}

void print_speed()
{
    Serial.print("Speed:  ");
    Serial.print(i * 120 / number_of_holes);
    Serial.println(" rpm");
    i = 0;
}

void counter()
{
    i++;
}
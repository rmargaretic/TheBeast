//Arduino UNO V1.0 and Adafruit V 1.0
// Included Arduino Dual Ultrasonic Sensor

//AFMotor library
#include <AFMotor.h>

//Pin Definition for the Arduino Dual Ultrasonic Sensor
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin

//Form a motor object, which maps to specific Adafruit pins
AF_DCMotor motor(2, MOTOR12_64KHZ);


void setup()
{
  Serial.begin(9600);

  //ultrasonic trigger and eco pin setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  Serial.println("Testing the motor");

  //constructor call
  motor.setSpeed(200);

  pinMode(2, INPUT);
  //External interrupt set-up
  attachInterrupt(0, Reverse, RISING); //(UNO interrupt 0) = pin2
}

void loop()
{
 //ultrasonic sensor variables
 long duration;
 long distance;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); 

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);

    //distance in cm
    distance = duration/58.2;

        if (distance >= 10)
        {
          digitalWrite(2, LOW);  //set interrupt
        }
        else
        {
          Serial.println("distance in cm");
          Serial.println(distance);
          digitalWrite(2, HIGH);  //make sure interrupt is low
        }
     Serial.print("Forward drive");
     motor.run(FORWARD);
     delay(100);

}

//Interrupt routine
void Reverse()
{
  motor.run(BACKWARD); //reverse
  Serial.println("Reversing");
}

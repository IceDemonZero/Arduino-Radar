#include <Servo.h>

#include <SR04.h>

#define TRIG 8 // Echo pin
#define ECHO 7 // Trig pin

//NOTE: remember to use 220 ohm resistors

int redLED = 11; // Red LED pin
int greenLED = 12; // Green LED pin
int button = 3; // The on button  pin
int servoPin = 5; // The servo arduino board pin
int position = 0; // The servos position
int distance; // Distance of objects
bool systemState; // The on/off state of the radar. False is off True is on.

Servo servo;
SR04 sensor = SR04(ECHO, TRIG);

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  servo.attach(servoPin);
  Serial.begin(9600);

  //System will be auto set to off
  off();
}

void on() {
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  systemState = true;
  while(systemState){
    if (position == 0) {
      while (position != 180) {
        servo.write(position);
        delay(90); // Delay process for 100 milliseconds
        distance = sensor.Distance();
        Serial.print("\nDegrees: ");
        Serial.print(position);
        Serial.print(" Distance: ");
        Serial.print(distance);
        Serial.print("cm");
        position++;
        if(position == 180){
          break;
        }
      }
    }
    
    if (position == 180) {
      while (position != 0) {
        servo.write(position);
        delay(90);
        distance = sensor.Distance();
        Serial.print("\nDegrees: ");
        Serial.print(position);
        Serial.print(" Distance: ");
        Serial.print(distance);
        Serial.print("cm");
        
        position--;

        if(position == 0){
          off();
        }
      }
    } 
  }
}

void off() {
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  systemState = false;
  servo.write(0);
}

void loop() {
  if (digitalRead(button) == LOW) {
    on();
  }
}

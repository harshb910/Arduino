#include <Servo.h>

// Define the pin for the servo signal
Servo myservo;
const int servo_pin = 9;

void setup() {
  Serial.begin(9600);         // Initialize serial communication
  myservo.attach(servo_pin);  // Attach the servo to pin 9
}

void loop() {
  int val = 0; // Initialize val to 0
  
  if (Serial.available() > 0) {
    val = Serial.parseInt();  // Parse integer input from Serial

    if (val >= 0 && val <= 180) {  // Ensure the value is within servo range
      Serial.println(val);    // Print the received value
      myservo.write(val);     // Set servo to the received angle
    } 
  }
  
  delay(1000); // Delay to avoid excessive looping
}

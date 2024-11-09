// Dependencies
#include <Servo.h>
#include <string.h>

Servo bottom_lid, container;

// PinConfiguration
const int IRSensor_signal = 7; // input
const int Buzzer = 8; // output
const int MetalSensor_signal = 12; // input
const int ledPin = 13;      // Built-in LED on Arduino
const int MoistureSensor_signal = A0; // analog input
const int bottom_lid_pin = 9; // output value for angle for bottom lid
const int container_pin = 10; // output value for angle for container lid

const String METAL = "metal";
const String DRY = "dry";
const String WET = "wet";


// Setup
void setup() {
  pinMode(IRSensor_signal, INPUT); // for detecting object
  pinMode(MetalSensor_signal, INPUT); // for detecting metal
  pinMode(ledPin, OUTPUT); // for output
  pinMode(Buzzer, OUTPUT); // for output
  bottom_lid.attach(bottom_lid_pin);  // Attach the bottom lid to pin 9
  container.attach(container_pin); // Attach the container to pin 10
  container.write(90);
  bottom_lid.write(0);
  Serial.begin(9600);
}

// Processing
void loop() {
  Serial.println("Starting");
  int is_empty = digitalRead(IRSensor_signal);
  Serial.print("IR Sensor OUTPUT: ");
  Serial.println(is_empty);
  delay(500);
  if(!is_empty){
    // object is present
    int metalSensorValue = digitalRead(MetalSensor_signal);  // Read the metal sensor output
    // if metal present metalSensorValue goes low as type is NPN
    if(metalSensorValue == LOW){
      // metal present
      Serial.println("Metal Detected");
      TurnOnBuzzer();
      segregate(METAL);
    }else{
      // metal not present
      Serial.println("No Metal");
      int dryness = analogRead(MoistureSensor_signal); // Read Soil Moisture Sensor
      Serial.print("Soil Moisture Sensor: ");
      Serial.println(dryness);
      if(dryness < 600){
        // wet waste
        Serial.println("Wet Waste Detected");
        TurnOnBuzzer();
        TurnOnBuzzer();
        segregate(WET);
      }else{
        // Dry Waste
        Serial.println("Dry Waste Detected");
        TurnOnBuzzer();
        TurnOnBuzzer();
        TurnOnBuzzer();
        segregate(DRY);
      }
    }
  }else{
    // object is not present
    Serial.println("Object is not present");
  }
  delay(2000);
}

void TurnOnBuzzer(){
  Serial.println("Buzzer Triggered");
  digitalWrite(Buzzer, HIGH);
  delay(200);
  digitalWrite(Buzzer, LOW);
  delay(200);
}

void segregate(String waste){
  if(waste == METAL){
    container.write(10);
    delay(1000);
    bottom_lid.write(180);
    delay(1500);
    bottom_lid.write(0);
    container.write(90);
  }else if(waste == WET){
    container.write(150);
    delay(1000);
    bottom_lid.write(180);
    delay(1500);
    bottom_lid.write(0);
    container.write(90);
  }else{
    delay(1000);
    bottom_lid.write(180);
    delay(1500);
    bottom_lid.write(0);
  }
  return;
}

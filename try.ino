// Dependencies
#include <Servo.h>

Servo bottom_lid, container;

// PinConfiguration
const int IRSensor_signal = 7; // input
const int Buzzer = 8; // output
const int MetalSensor_signal = 12; // input
const int ledPin = 13;      // Built-in LED on Arduino
const int MoistureSensor_signal = A0; // analog input
const int bottom_lid_pin = 9; // output value for angle for bottom lid
const int container_pin = 10; // output value for angle for container lid


// Setup
void setup() {
  pinMode(IRSensor_signal, INPUT); // for detecting object
  pinMode(MetalSensor_signal, INPUT); // for detecting metal
  pinMode(ledPin, OUTPUT); // for output
  pinMode(Buzzer, OUTPUT); // for output



  Serial.begin(9600);
}

// Processing
void loop() {
  Serial.println("Starting");
  int is_empty = digitalRead(IRSensor_signal);
  Serial.print("IR Sensor OUTPUT: ");
  Serial.println(is_empty);
  if(!is_empty){
    // object is present
    int metalSensorValue = digitalRead(MetalSensor_signal);  // Read the metal sensor output
    // if metal present metalSensorValue goes low as type is NPN
    if(metalSensorValue == LOW){
      // metal present
      Serial.println("Metal Detected");
      TurnOnBuzzer();
    }else{
      // metal not present
      Serial.println("No Metal");
      int dryness = analogRead(Moisture_signal); // Read Soil Moisture Sensor
      Serial.print("Soil Moisture Sensor: ");
      Serial.println(dryness);
      if(dryness < 600){
        // wet waste
        Serial.println("Wet Waste Detected");
        TurnOnBuzzer();
        TurnOnBuzzer();
      }else{
        // Dry Waste
        Serial.println("Dry Waste Detected");
        TurnOnBuzzer();
        TurnOnBuzzer();
        TurnOnBuzzer();
      }
    }
  }else{
    // object is not present
    Serial.println("Object is not present");
  }
  delay(1000);
}

void TurnOnBuzzer(){
  Serial.println("Buzzer Triggered")
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
  delay(500);
}

void TurnOnLED(){

}

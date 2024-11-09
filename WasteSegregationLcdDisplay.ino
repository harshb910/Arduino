// Dependencies
#include <Servo.h>
#include <string.h>
#include <LiquidCrystal.h>

Servo bottom_lid, container;

// PinConfiguration
const int IRSensor_signal = 7; // input
const int Buzzer = 8; // output
const int MetalSensor_signal = 13; // input
const int MoistureSensor_signal = A0; // analog input
const int bottom_lid_pin = 6; // output value for angle for bottom lid
const int container_pin = 10; // output value for angle for container lid
// For LCD
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;
const int contrastPin = 9; // D9 for contrast (Vo pin)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const String METAL = "metal";
const String DRY = "dry";
const String WET = "wet";


// Setup
void setup() {
  pinMode(IRSensor_signal, INPUT); // for detecting object
  pinMode(MetalSensor_signal, INPUT); // for detecting metal
  pinMode(Buzzer, OUTPUT); // for output
  bottom_lid.attach(bottom_lid_pin);  // Attach the bottom lid to pin 9
  container.attach(container_pin); // Attach the container to pin 10
  container.write(90);
  bottom_lid.write(0);
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  // Set initial contrast
  pinMode(contrastPin, OUTPUT);
  analogWrite(contrastPin, 100); // Adjust this value for optimal contrast
  // Display a message on the LCD
  lcd.print("Use Me!");
  lcd.setCursor(0, 1); // Move to the second row
  lcd.print("WasteSegregation");

  Serial.begin(9600);
}

// Processing
void loop() {
  // Display a message on the LCD
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); // Set cursor to the beginning of the first line
  lcd.print("Use Me!");
  lcd.setCursor(0, 1); // Move to the second row
  lcd.print("WasteSegregation");

  Serial.println("Starting");
  int is_empty = digitalRead(IRSensor_signal);
  Serial.print("IR Sensor OUTPUT: ");
  Serial.println(is_empty);
  delay(200);         
  if(!is_empty){
    // object is present
    int metalSensorValue = digitalRead(MetalSensor_signal);  // Read the metal sensor output
    Serial.print("Metal Sensor Value:");
    Serial.println(metalSensorValue);
    // if metal present metalSensorValue goes low as type is NPN
    if(metalSensorValue == LOW){
      // metal present
      Serial.println("Metal Detected");
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set cursor to the beginning of the first line
      // Display a message on the LCD
      lcd.print("Metal Waste");
      lcd.setCursor(0, 1); // Move to the second row
      lcd.print("Detected");
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
        lcd.clear(); // Clear the LCD screen
        lcd.setCursor(0, 0); // Set cursor to the beginning of the first line
        // Display a message on the LCD
        lcd.print("Wet Waste");
        lcd.setCursor(0, 1); // Move to the second row
        lcd.print("Detected");
        TurnOnBuzzer();
        TurnOnBuzzer();
        segregate(WET);
      }else{
        // Dry Waste
        Serial.println("Dry Waste Detected");
        lcd.clear(); // Clear the LCD screen
        lcd.setCursor(0, 0); // Set cursor to the beginning of the first line
        // Display a message on the LCD
        lcd.print("Dry Waste");
        lcd.setCursor(0, 1); // Move to the second row
        lcd.print("Detected");
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
  delay(1000);
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
    bottom_lid.write(170);
    delay(2000);
    bottom_lid.write(0);
    container.write(90);
  }else if(waste == WET){
    container.write(150);
    delay(1000);
    bottom_lid.write(170);
    delay(2000);
    bottom_lid.write(0);
    container.write(90);
  }else{
    delay(1000);
    bottom_lid.write(170);
    delay(2000);
    bottom_lid.write(0);
  }
  return;
}

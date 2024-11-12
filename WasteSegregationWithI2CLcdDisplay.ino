// Dependencies
#include <Servo.h>
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo bottom_lid, container;

// PinConfiguration
const int IRSensor_signal = 7; // input
const int Buzzer = 8; // output
const int MetalSensor_signal = 13; // input
const int MoistureSensor_signal = A0; // analog input
const int bottom_lid_pin = 6; // output value for angle for bottom lid
const int container_pin = 10; // output value for angle for container lid
// For LCD
// Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);


const String METAL = "metal";
const String DRY = "dry";
const String WET = "wet";


// Setup
void setup() {
  // Initialize the LCD
  lcd.init();
  // Turn on the backlight
  lcd.backlight();

  pinMode(IRSensor_signal, INPUT); // for detecting object
  pinMode(MetalSensor_signal, INPUT); // for detecting metal
  pinMode(Buzzer, OUTPUT); // for output
  bottom_lid.attach(bottom_lid_pin);  // Attach the bottom lid to pin 9
  container.attach(container_pin); // Attach the container to pin 10
  container.write(90);
  bottom_lid.write(0);

  Serial.begin(9600);
}

// Processing
void loop() {
  // Display a message on the LCD
  lcd.clear(); // Clear the LCD screen
  delay(200);   // Delay for LCD stability
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
      delay(200);   // Delay for LCD stability
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
        delay(200);   // Delay for LCD stability
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
        delay(200);   // Delay for LCD stability
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
  delay(800);
  lcd.clear();
  delay(200);   // Delay for LCD stability
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
    delay(1500);
    container.write(90);
  }else if(waste == WET){
    container.write(150);
    delay(1000);
    bottom_lid.write(170);
    delay(2000);
    bottom_lid.write(0);
    delay(1500);
    container.write(90);
  }else{
    delay(1000);
    bottom_lid.write(170);
    delay(2000);
    bottom_lid.write(0);
  }
  return;
}

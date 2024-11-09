#include <LiquidCrystal.h>

// Initialize the LiquidCrystal library with the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int contrastPin = 6;   // PWM pin for contrast control

void setup() {
  pinMode(contrastPin, OUTPUT);  // Set the contrast pin as output

  // Set an initial contrast level using PWM
  analogWrite(contrastPin, 100); // Adjust between 0-255 for best contrast

  lcd.begin(16, 2);              // Initialize a 16x2 LCD display
  lcd.print("Hello, Arduino!");   // Display message on the first line
  Serial.begin(9600);
}

void loop() {
  Serial.println("Starting");
  lcd.setCursor(0, 1);            // Move cursor to second line
  lcd.print("Hello");
  delay(1000);                    // Update every second
}

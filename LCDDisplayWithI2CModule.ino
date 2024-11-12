#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight
  lcd.backlight();
  
  // Display a message on the LCD
  lcd.setCursor(0, 0);        // Set the cursor to column 0, row 0
  lcd.print("Hello, Arduino!");
  
  lcd.setCursor(0, 1);        // Set the cursor to column 0, row 1
  lcd.print("I2C LCD Test");
}

void loop() {
  // You can add additional code to update the LCD here if needed
}

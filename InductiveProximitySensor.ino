// Define the pin for the sensor signal
const int sensorPin = 2;    // Connect Black wire to D2
const int ledPin = 13;      // Built-in LED on Arduino

void setup() {
  pinMode(sensorPin, INPUT);  // Set the sensor pin as input
  pinMode(ledPin, OUTPUT);    // Set the LED pin as output
  Serial.begin(9600);         // Initialize serial communication
}

void loop() {
  int sensorValue = digitalRead(sensorPin);  // Read the sensor output
  
  // If sensor detects metal (signal goes LOW)
  if (sensorValue == LOW) {
    digitalWrite(ledPin, LOW);  // Turn on LED
    Serial.println("Metal detected!");  // Print message to Serial Monitor
    digitalWrite(8, HIGH); // Buzzer
  } else {
    digitalWrite(ledPin, HIGH); // Turn off LED
    Serial.println("No Metal");
    digitalWrite(8, LOW); // Buzzer
  }
  
  delay(500);  // Small delay for stability
}

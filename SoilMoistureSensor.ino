
int Moisture_signal = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int moisture = analogRead(Moisture_signal);
  Serial.print("Soil Moisture Level: ");
  Serial.println(moisture);
  delay(200);
}

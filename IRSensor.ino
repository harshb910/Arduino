// Activating Buzzer at pin 8
int IRSensor_signal = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IRSensor_signal, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int object = digitalRead(IRSensor_signal);
  Serial.print("IR Sensor OUTPUT: ");
  Serial.println(object);
  if(!object){
    digitalWrite(8,HIGH);
  }else{
    digitalWrite(8, LOW);
  }
  delay(2000);
}

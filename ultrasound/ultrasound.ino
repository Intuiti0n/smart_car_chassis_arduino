/*
HC-SR04 Ping distance sensor
DANIEL GOMES
VCC to arduino 5v
GND to arduino GND
Echo to Arduino pin 13
Trig to Arduino pin 12
*/

#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10

void setup() {
  Serial.begin (115200);//Serial port speed in bps
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // 10 us HIGH trigPin to send emitter wave
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);//function to receive the bouncing signal and save the duration of the pulse.
  distance = (duration/2) *0.034;
  if (distance >= 200 || distance <= 0){//
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);//detect distance every 0.5 sec
}

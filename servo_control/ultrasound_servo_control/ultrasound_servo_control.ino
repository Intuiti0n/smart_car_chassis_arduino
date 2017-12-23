/* DANIEL GOMES
   SERVO CONTROL USING AN ULTRASSOUND HC-SR04
   ARDUINO UNO
   PINS USED:
   VCC -> 5V
   TRIG ->13
   ECHO ->12
   GND -> GND<
*/
#define PIN_TRIG 13
#define PIN_ECHO 12
#define PIN_SERVO 6     //SERVO SIGNAL PIN ON THE ARDUINO
#define PWMPERIOD 20000 //PWMPERIOD FOR THE SERVO TO WORK
#define MAX_ADC 1023 //max 10 bit value of the ADC
#define MAX_ANGLE 180 //max angle for this servo
#define ANGLE_ADC (MAX_ADC/MAX_ANGLE)

int pinServo = 6; //servo connected to digital pin 6 (can output PWM)
int myAngle;//angle of the servo
static unsigned short int pulseWidth = 0; //pulse width to be calculated to change angle
unsigned long int pwmperiod = 20000; //20000us=20ms is the pwm period of sg90 servo motor
static int incomingByte;   // for incoming serial data

static short int distance = 0;
static long int duration = 0;
/*
  Specifications
  • Weight: 9 g
  • Dimension: 22.2 x 11.8 x 31 mm approx.
  • Stall torque: 1.8 kgf·cm
  • Operating speed: 0.1 s/60 degree -> change loop to check this acording to the angle difference
  • Operating voltage: 4.8 V (~5V)
  • Dead band width: 10 µs
  • Temperature range: 0 ºC – 55 ºC
*/

//pulse is 20ms long
void servoPulse(int myAngle) {
  pinMode(PIN_SERVO, OUTPUT);
  if(myAngle>=180) myAngle=180;
  else if(myAngle<=0) myAngle=0;
  
  for (int i = 0; i < 10; i++) {
    short int pulse = (int) (myAngle * 11.12);
    digitalWrite(PIN_SERVO, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(PIN_SERVO, LOW);
    delayMicroseconds(PWMPERIOD - pulse);
  }
}

void check_ultrasound() {
  // Clears the trigPin
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(PIN_ECHO, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  if (distance > 400) distance = 400;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
}


void control_servo() {
  check_ultrasound();
  if (distance < 10) {
    servoPulse(0);
  }
  else {
    servoPulse(distance);
  }
  delay(60);
}

void setup() {
  pinMode(PIN_SERVO, OUTPUT);
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
}

void loop() {
  control_servo();
  delay(100);
}

/* DANIEL GOMES
   SERVO CONTROL USING A POTENTIOMETER
   ARDUINO UNO
   PINS USED: 6 -> SIGNAL FOR THE SERVO
   A0 -> MIDDLE PIN FOR POTENTIOMETER
*/

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

void servoPulse(int servoPin, int myAngle) {
  pinMode(PIN_SERVO, OUTPUT);
  for (int i = 0; i < 100; i++) {
    short int pulse = (int) (myAngle * 11.12);
    digitalWrite(PIN_SERVO, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(PIN_SERVO, LOW);
    delayMicroseconds(PWMPERIOD - pulse);
  }
}

void check_potentiometer() {
  short int adc_value = analogRead(A0);
  short int angle = (int) (adc_value / ANGLE_ADC);
  servoPulse(6, angle);
}


void setup() {
  pinMode(PIN_SERVO, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  check_potentiometer();
  delay(500);
}



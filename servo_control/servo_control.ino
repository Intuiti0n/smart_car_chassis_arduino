int pinServo= 6;//servo connected to digital pin 6 (can output PWM)
int myAngle;//angle of the servo
static unsigned short int pulseWidth=0;//pulse width to be calculated to change angle
unsigned long int pwmperiod=20000;//20000us=20ms is the pwm period of sg90 servo motor
static int incomingByte;   // for incoming serial data

void servoPulse(int servoPin, int myAngle){
    pinMode(servoPin,OUTPUT);
    for(int i=0;i<100;i++){
        short int pulse= (int) (myAngle*11.12);
        digitalWrite(servoPin,HIGH);
        delayMicroseconds(pulse);
        digitalWrite(servoPin,LOW);
        delayMicroseconds(pwmperiod-pulse);
   }
}

void setup(){
  pinMode(pinServo,OUTPUT);
  Serial.begin(115200);
}

void loop(){
  /*
        digitalWrite(pinServo,HIGH);
        delayMicroseconds(pulseWidth);
        digitalWrite(pinServo,LOW);
        delayMicroseconds(pwmperiod-pulseWidth);
        */
        servoPulse(6,0);
        delay(2000);
        servoPulse(6,90);
        delay(2000);
        servoPulse(6,180);
        delay(2000);
        servoPulse(6,0);
        delay(2000);
        servoPulse(6,45);
        delay(2000);
        servoPulse(6,90);
        delay(2000);
        servoPulse(6,135);
        delay(2000);
}   



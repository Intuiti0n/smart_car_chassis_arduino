//Autor : Daniel Gomes A74729


//Definicoes pinos Arduino ligados as entradas da Ponte H
int MA_1 = 4;
int MA_2 = 5;
int MB_1 = 7;
int MB_2 = 6;
int MC_1 = 9;
int MC_2 = 8;
int MD_1 = 10;
int MD_2 = 11;

//variaveis de sistema
volatile static char command = 'F';
char prevCommand = 'D';
unsigned long timer0 = 2000;  //Stores the time (in millis since execution started)
unsigned long timer1 = 0;  //Stores the time when the last command was received from the phone

// BTconnected will = false when not connected and true when connected
boolean BTconnected = false;
// connect the STATE pin to Arduino pin D4
const byte BTpin = 12;

void setup() {
  // set the BTpin for input
  pinMode(BTpin, INPUT);
  Serial.begin(115200);
  //Define os pinos como saida
  pinMode(MA_1, OUTPUT);
  pinMode(MA_2, OUTPUT);
  pinMode(MB_1, OUTPUT);
  pinMode(MB_2, OUTPUT);
  pinMode(MC_1, OUTPUT);
  pinMode(MC_2, OUTPUT);
  pinMode(MD_1, OUTPUT);
  pinMode(MD_2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // wait until the HC-05 has made a connection
  while (!BTconnected)
  {
    if ( digitalRead(BTpin) == HIGH)  {
      BTconnected = true;
    };
  }

  //Serial.println("HC-05 is now connected");
}
//andar para a frente
void forward() {
  digitalWrite(MA_1, HIGH);
  digitalWrite(MA_2, LOW);

  digitalWrite(MB_1, HIGH);
  digitalWrite(MB_2, LOW);

  digitalWrite(MC_1, HIGH);
  digitalWrite(MC_2, LOW);

  digitalWrite(MD_1, HIGH);
  digitalWrite(MD_2, LOW);
}

//andar para tras
void backward() {
  digitalWrite(MA_1, LOW);
  digitalWrite(MA_2, HIGH);

  digitalWrite(MB_1, LOW);
  digitalWrite(MB_2, HIGH);

  digitalWrite(MC_1, LOW);
  digitalWrite(MC_2, HIGH);

  digitalWrite(MD_1, LOW);
  digitalWrite(MD_2, HIGH);
}

//virar esquerda
void left() {
  digitalWrite(MA_1, LOW);
  digitalWrite(MA_2, HIGH);

  digitalWrite(MB_1, HIGH);
  digitalWrite(MB_2, LOW);

  digitalWrite(MC_1, HIGH);
  digitalWrite(MC_2, LOW);

  digitalWrite(MD_1, LOW);
  digitalWrite(MD_2, HIGH);
}

//virar direita
void right() {
  digitalWrite(MA_1, HIGH);
  digitalWrite(MA_2, LOW);

  digitalWrite(MB_1, LOW);
  digitalWrite(MB_2, HIGH);

  digitalWrite(MC_1, LOW);
  digitalWrite(MC_2, HIGH);

  digitalWrite(MD_1, HIGH);
  digitalWrite(MD_2, LOW);
}

void stop_car() {
  digitalWrite(MA_1, LOW);
  digitalWrite(MA_2, LOW);
  digitalWrite(MB_1, LOW);
  digitalWrite(MB_2, LOW);
  digitalWrite(MC_1, LOW);
  digitalWrite(MC_2, LOW);
  digitalWrite(MD_1, LOW);
  digitalWrite(MD_2, LOW);
}

void da_way(char d) {
  switch (d) {
    case 'F': forward();  break;
    case 'B': backward(); break;
    case 'L': left();     break;
    case 'R': right();    break;
    case 'D': stop_car(); break;
    default : stop_car(); break;
  }
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    if (command == 'B') digitalWrite(LED_BUILTIN, HIGH);
    timer1 = millis();
    Serial.println(command);
    //Change pin mode only if new command is different from previous.
      //Serial.println(command);
      da_way(command);
    /*
      else {
      timer0 = millis();  //Get the current time (millis since execution started).
      //Check if it has been 500ms since we received last command.
      if ((timer0 - timer1) > 500) {
        //More tan 500ms have passed since last command received, car is out of range.
        //Therefore stop the car and turn lights off.
        da_way('D');
      }
      }*/
  }
}

/*
Team 5 - Let It Go

Written By: Justin Law

*/

int S1 = 2; //solenoid 1 (leftmost red led) connected to digital pin2 
int S2 = 3; //solenoid 2 (red led) connected to digital pin3 
int S3 = 4; //solenoid 3 (red led) connected to digital pin4 
int S4 = 5; //solenoid 4 (red led) connected to digital pin5 
int M1a = 6; // pin6, motor 1, direction 1: leftmost green led (on top)
int M1b = 7; // pin7, motor 1, direction 2: leftmost yellow led (on bottom)
int M2a = 8; // pin8, motor 2, direction 1: middle green led (on top)
int M2b = 9; // pin9, motor 2, direction 2: middle yellow led (on bottom)
int M3a = 10;//pin10, motor 3, direction 1: rightmost green led (on top)
int M3b = 11;//pin11, motor 3, direction 2: rightmost yellow led (on bottom)
int SW1 = 12;//pin12, switch1 input
int SW2 = 13;//pin13, switch2 input

void setup()   
{                
  // initialize all the digital pins to be outputs:
  pinMode(S1, OUTPUT);      
  pinMode(S2, OUTPUT);     
  pinMode(S3, OUTPUT);     
  pinMode(S4, OUTPUT);     
  pinMode(M1a, OUTPUT);     
  pinMode(M1b, OUTPUT);     
  pinMode(M2a, OUTPUT);     
  pinMode(M2b, OUTPUT);     
  pinMode(M3a, OUTPUT);     
  pinMode(M3b, OUTPUT);     
  pinMode(SW1, INPUT);  // switch
  pinMode(SW2, INPUT);  // switch
}

void loop()
{
pulse_out(S1,5);
motor_on(1,1);
pulse_out(S1,10);
motor_on(1,2);
pulse_out(S1,5);
motor_on(1,1);
pulse_out(S1,5);
motor_on(1,2);
pulse_out(S1,15);
motor_on(1,1);
pulse_out(S1,10);
motor_on(1,2);
pulse_out(S1,5);
motor_on(1,1);
pulse_out(S1,10);
motor_on(1,2);
pulse_out(S1,10);
motor_on(1,1);
pulse_out(S1,10);
motor_on(1,2);
pulse_out(S1,15);
motor_on(1,1);
pulse_out(S1,10);
motor_on(1,2);
pulse_out(S1,5);
motor_on(1,1);
pulse_out(S1,5);
motor_on(1,2);
pulse_out(S1,10);
motor_on(1,1);
pulse_out(S1,15);
motor_on(1,2);
pulse_out(S1,10);
motor_on(1,1);
pulse_out(S1,15);
motor_on(1,2);
}

//Solenoid starts active, turns off then back on
void pulse_out(int numb, int duration){
  // This function will pulse a solenoid by releasing it from the active state (pulled in)
  //  for a short period of time and then returning it to the active state (pulled in)
  //  and then wait for the desired duration time (duration# * 200 mSec)
  digitalWrite(numb, LOW);
  delay(30);
  digitalWrite(numb, HIGH);
  delay(duration*200);
}

//Turn pecified motor on
void motor_on(int motor_numb, int motor_dir)
  {
  // This function will turn one of the motors on in the direction specified
  //  note: you do not need to call the motor_off() function to instantaneously change the direction of the 
  //  of the same motor, just call motor_on() with the new desired direction.
  if (motor_numb < 1 || motor_numb > 3) { // a check to see if the input is correct, if it's not then the program will flash all the lights
    error_flash(11); 
  }
  if (motor_dir == 1) {
    digitalWrite(motor_numb*2+4, HIGH);
    digitalWrite(motor_numb*2+5, LOW);
  }
  else if (motor_dir == 2) {
    digitalWrite(motor_numb*2+4, LOW);
    digitalWrite(motor_numb*2+5, HIGH);
  }
  else { // a check on the motor_dir value, if it's not a 1 or a 2 then it will flash all the red lights
    error_flash(5);
  }
}

//Turn motor off
void motor_off(int motor_numb){
  // This function will turn off one of the motors
  //  note: you do not need to call the motor_off() function to instantaneously change the direction of the 
  //  of the same motor, just call motor_on() with the new desired direction.
  if (motor_numb < 1 || motor_numb > 3) {
    error_flash(3); // a check on the motor_numb value, if it's not a 1 or 2 or 3 then it will flash 3 red lights 
  }
  digitalWrite(motor_numb*2+4, LOW);
  digitalWrite(motor_numb*2+5, LOW);
}

//All lights will flash if an error is found
void error_flash(int numb) {
  // this function will 
  int i;
  // if the initial error code is out of range then set it to flash all LEDs
  if ((numb > 11) || (numb<1)) {
    numb = 11;
  }
  for (i=2;i<=12;i++) {
    digitalWrite(i,LOW);
  }
  while (1==1) { // endless loop for flashing the lights
    for (i=2;i<=numb+1;i++) {
      digitalWrite(i,HIGH);
    }
    delay(200);
    for (i=2;i<=numb+1;i++) {
      digitalWrite(i,LOW);
    }
    delay(200);
  }
}

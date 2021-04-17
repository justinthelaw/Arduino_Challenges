/* 
** Title: Program for Playing Chime Machine Song
** Song: Let It Go
** Written by: Justin Law
*/

//Variables Declared
const int S1=2;  // solenoid 
const int M3a=6; // motor: forward direction
const int M3b=7; // motor: backward direction

//Personal Variables
int i;
int current_position; //current position of the motor/potentiometer
int desired_position; //desired position of the motor/potentiometer
int init_time;
int cur_time;
int analog_channel = A1; // potentiometer is connected to this channel
int k= 20; // "spring" stiffness (proportional gain value) 
int pause_time = 1500; // pause at each position
int pos1 = 801; // position 1 value in analog readings (0 -> 1023)– A
int pos2 = 588; // position 2 - B
int pos3 = 548; // position 3 - C
int pos4 = 670; // position 4 - D
int pos5 = 754; // position 5 - D#
int pos6 = 713; // position 6 - E
int pos7 = 626; // position 7 - F#
int pos8 = 507; // position 8 - G
int output = 0; // variable that contains output command to the motor (duty_cycle 0 -> 255)

//Ouput and Input Arguments
//Initialization of Digital Pins
void setup() {                
  pinMode(S1, OUTPUT); // solenoid 
  pinMode(M3a, OUTPUT); // motor: forward direction
  pinMode(M3b, OUTPUT); // motor: backward direction
  
  Serial.begin(9600); // serial port for data relay to computer
}

//Functions To Be Used 

/* Error Flashing */

void error_flash(int numb) { //a problem with program causes this function to be executed
  int i;
  if ((numb > 11) || (numb<1)) {
    numb = 11;
  }
  for (i=2;i<=11;i++) {
    digitalWrite(i,LOW);
  }
  while (1==1) { 
    for (i=2;i<=numb+1;i++) {
      digitalWrite(i,HIGH);
    }
    delay(200);
    for (i=2;i<=numb+1;i++) {
      digitalWrite(i,LOW);
    }
    Serial.println('ERROR: one of the inputs to a function is out of range');
    delay(200);
  }
}

/* Solonoid Default State */

void solenoids_in(void) { // keeps solenoid in
  digitalWrite(2,HIGH);
}

/* Solonoid Hits Note */

void pulse_out(int numb, int duration){ // pulses solenoid out
  digitalWrite(numb, LOW);
  delay(100);
  digitalWrite(numb, HIGH);
  delay(duration*1000);
}

/* Motor On */

void motor_on(int motor_numb, int motor_dir){ // motor is turned on to spin in direction specified
  if (motor_numb < 0 || motor_numb > 3) {
    error_flash(11); 
  }
  if (motor_dir == 1) {
    digitalWrite(motor_numb*10, HIGH);
    digitalWrite(motor_numb*11, LOW);
  }
  else if (motor_dir == 2) {
    digitalWrite(motor_numb*10, LOW);
    digitalWrite(motor_numb*11, HIGH);
  }
  else {
    error_flash(4);
  }
}

/* Motor Off */

void motor_off(int motor_numb){ // motor is turned off
  if (motor_numb < 0 || motor_numb > 3) {
    error_flash(3);
  }
  analogWrite(motor_numb*10, LOW);
  analogWrite(motor_numb*11, LOW);
}


//////////Loop To Be Executed To Play: Let It Go//////////

void loop() {
  Serial.println(current_position);
  solenoids_in();

  //move motor to start position
  desired_position = pos6;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    cur_time = millis();
    Serial.print("note 1 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
    //move motor to position
  desired_position = pos7;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 2 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
      //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 3 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos4;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 4 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 5 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos1;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 6 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 7 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos1;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 8 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 9 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 10 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos3;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 11 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos3;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 12 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 13 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos1;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 14 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 15 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos1;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 16 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 17 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos4;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 18 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 19 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos1;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 20 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 21 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 22 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos4;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 23 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 24 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 25 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 26 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 27 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos7;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 28 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos4;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 29 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 30 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos3;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 31 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos3;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 32 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 33 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos3;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 34 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 35 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos3;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 36 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos3;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 37 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos2;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 38 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
        //move motor to position
  desired_position = pos8;
  init_time = millis();
  cur_time = millis();
  
  while (cur_time-init_time < pause_time) {  //stay at the first position for the pause time
    // read the current position from the potentiometer (a value= 0 -> 1023)
    current_position = analogRead(analog_channel);
    
    // calculate the error between the current and desired position and multiply by k ("stiffness")
    output = abs(current_position - desired_position)*k;
    
    // if output value is greater than the max speed of the motor, set it equal to the motor's max speed
    if (output > 255) {
      output = 255;
    }
    
    // determine which direction the motor needs to turn and turn it at the desired duty_cycle
    if (current_position < desired_position) {
      analogWrite(10,output);
      digitalWrite(11, LOW);      
    }
    else if (current_position > desired_position) {
      analogWrite(11,output);
      digitalWrite(10, LOW);     
    }
    else {
      motor_off(1);
    }
    cur_time = millis();
    Serial.print("note 39 ");
    Serial.println(current_position);
  }
  
  //play note
  pulse_out(S1,0.5); // quickly release and then re-energize the solenoid and wait 1 duration time before pusle back in
  
  
}


  


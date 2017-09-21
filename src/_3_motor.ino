/*
int motor_run(const bool use_motor_A, auto motor_dir) {
  // run the motor in the forward direction at the desired pwm
  // @param: use_motor_A, true => will use the motorA pins
  // @param: motor_dir, direction to run the motor 
  // return: the sensed motor voltage
  unsigned int pwm_pin;
  unsigned int sense_pin;
  unsigned int pwm;
  
  if (use_motor_A) {
    digitalWrite(DIR_A, motor_dir); // set the supplied direction
    digitalWrite(BRAKE_A, LOW);  // turn off the brake
    pwm_pin = PWM_A;
    sense_pin = SENSE_A;
  } else {
    digitalWrite(DIR_B, motor_dir); // set the supplied direction
    digitalWrite(BRAKE_B, LOW);  // turn off the brake
    pwm_pin = PWM_B;
    sense_pin = SENSE_B;
  }  

  // check that the pwm value is within the desired threshholds
  if (pwm_desired <= 1) pwm = 0;
  else {
    pwm = (pwm_desired / 2) + 50;
  }
  
  analogWrite(pwm_pin, pwm);
  
  return analogRead(sense_pin);
}

void motor_stop(const bool use_motor_A) {
  // stops the desired motor
  // @param: use_motor_A, true => will use the motorA pins
  if (use_motor_A) {
    analogWrite(PWM_A, 0); // set the pwm to zero
    digitalWrite(BRAKE_A, HIGH);  // turn off the brake
  } else {
    analogWrite(PWM_B, 0); // set the pwm to zero
    digitalWrite(BRAKE_B, HIGH);  // turn off the brake
  }  
}*/

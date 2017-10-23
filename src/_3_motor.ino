void motor_stop() {
  // stops the desired motor

  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);

  myStepper.setSpeed(0);
  myStepper.step(0);
}

int motor_run(const bool use_motor_A, auto motor_dir) {
  // run the motor in the forward direction at the desired pwm
  // @param: use_motor_A, true => will use the motorA pins
  // @param: motor_dir, direction to run the motor 
  // return: the sensed motor voltage
  unsigned int pwm_pin;
  unsigned int sense_pin;
  unsigned int pwm;

  // check that the pwm value is within the desired threshholds
  if ((!e_stop_active) && (start_active == false)||(desired_speed <= 1)) {
    motor_stop();
  }
  
  else {
    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);
  
    pwm = (desired_speed / 2) + 50;

    myStepper.setSpeed(desired_speed);
    myStepper.step(stepsPerRevolution);
  }  
  
  return 0;
}


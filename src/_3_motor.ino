const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor

void motor_stop() {
  // stops the desired motor
  digitalWrite(SDA, LOW);
}

int motor_run(const int steps) {
  // run the motor in the forward direction at the desired pwm
  // @param: use_motor_A, true => will use the motorA pins
  // @param: motor_dir, direction to run the motor 
  // return: the sensed motor voltage
  const int stepsPerRevolution = 200;

  auto myStepper = new Stepper(stepsPerRevolution, 10, 11, 12, 13);

  // check that the pwm value is within the desired threshholds
  if (false) { //(e_stop_active) || (!start_active) || (desired_speed <= 1)) {
    motor_stop();
  } else {
    digitalWrite(SDA, HIGH);

    myStepper->setSpeed(desired_speed);
    myStepper->step(steps);
    digitalWrite(SDA, LOW);

    //motor_stop();

    delete myStepper;

    delay(2000);
  }  
  
  return 0;
}


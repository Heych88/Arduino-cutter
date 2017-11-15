
void motor_stop() {
  // stops the stepper motor and puts it in a low power state
  digitalWrite(SDA, LOW);
}

int motor_run(const int steps) {
  // run the motor in the forward direction at the desired pwm
  // @param: steps, number of steps to step the stepper motor
  // return: zero on completion
  const int stepsPerRevolution = 200;

  auto myStepper = new Stepper(stepsPerRevolution, 10, 11, 12, 13);

  // check that the pwm value is within the desired threshholds
  if ((e_stop_active) || (!start_active) || (desired_speed <= 1)) {
    motor_stop();
  } else {
    digitalWrite(SDA, HIGH);

    getSpeed();
  
    myStepper->setSpeed(desired_speed);
    myStepper->step(steps);
    digitalWrite(SDA, LOW);

    delete myStepper;
  }  
  
  return 0;
}


void motor_stop() {
  // stops the desired motor

  //digitalWrite(SDA, LOW);
  //digitalWrite(SCL, LOW); // Activating this will prevent the push buttons from working

  //myStepper.setSpeed(0);
  //myStepper.step(0);
}

int motor_run(const auto motor_dir) {
  // run the motor in the forward direction at the desired pwm
  // @param: use_motor_A, true => will use the motorA pins
  // @param: motor_dir, direction to run the motor 
  // return: the sensed motor voltage
  unsigned int pwm_pin;
  unsigned int sense_pin;
  unsigned int pwm;

  auto myStepper = new Stepper(stepsPerRevolution, 10, 11); //10, 11, 12, 13);

  // check that the pwm value is within the desired threshholds
  if ((e_stop_active) || (!start_active) || (desired_speed <= 1)) {
    motor_stop();
  } else {
    //digitalWrite(SDA, HIGH);

    myStepper->setSpeed(desired_speed);
    myStepper->step(2000);

    motor_stop();

    delete myStepper;

    delay(10000);
  }  
  
  return 0;
}


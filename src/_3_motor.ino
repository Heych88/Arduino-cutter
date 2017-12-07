int motor_loop_speed = getSpeed();

/*
 * Calculates the travel distance of the wheel per step of the stepper 
 * 
 * Args:
 *    distance: The required distance for the wheel to travel        
 *    
 * Returns:
 *    The step counts required to travel the distance
 */
int getDistanceCount(const int distance){
  
  float wheel_dist_per_step = (wheel_diam * PI) / stepsPerRevolution; // distance travelled per step
  return int(abs(distance / wheel_dist_per_step) + 0.5);
}

void motor_stop() {
  // stops the stepper motor and puts it in a low power state
  start_active = false;
  digitalWrite(SDA, LOW);
}

int motor_run(const int steps) {
  // run the motor in the forward direction at the desired pwm
  // @param: steps, number of steps to step the stepper motor
  // return: zero on completion
  const int stepsPerRevolution = 200;

  auto myStepper = new Stepper(stepsPerRevolution, 10, 11, 12, 13);

  // check that the pwm value is within the desired threshholds
  if ((e_stop_active) || (start_active == false) || (motor_loop_speed <= 1)) {
    motor_stop();
  } else {
    digitalWrite(SDA, HIGH);

    myStepper->setSpeed(desired_speed+2);
    myStepper->step(steps);
    digitalWrite(SDA, LOW);

    delete myStepper;
  }  
  
  return 0;
}



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
  return int((distance / wheel_dist_per_step) + 0.5);
}


/*
 * Stops the stepper motor and deactivates it to prevent current draw during non use.
 * 
 * Args:
 *    None
 *    
 */
void motor_stop() {
  start_active = false;
  digitalWrite(SDA, LOW);
}


/*
 * Initalises and runs the stepper motor to the desired distance.
 * 
 * Args:
 *    steps: number of steps to mover the motor.
 *    
 */
void motor_run(const int steps) {
  // check that the pwm value is within the desired threshholds
  if ((e_stop_active) || (start_active == false) || (desired_speed <= 1)) {
    motor_stop();
  } else {
    auto myStepper = new Stepper(stepsPerRevolution, 10, 11, 12, 13);
    
    digitalWrite(SDA, HIGH); // Enable the motor driver

    myStepper->setSpeed(desired_speed+2);
    myStepper->step(steps);
    digitalWrite(SDA, LOW);

    delete myStepper;
  }  
}


/*
void intEncodeA() {
  // Interrupt handler 
  encoderCount++;

  if (encoderCount % 50 == 0) {
    unsigned int diff = millis() - time_stamp;
    time_stamp = millis();
    motor_speed = wheel_dist_ppr * 50 * 1000 / diff;
  }
}*/

void intEStop() {

  if (digitalRead(E_STOP_BUT) == HIGH) {
    // Is a rising edge so E-Stop has been cleared
    e_stop_active = true;
  } else {
    e_stop_active = false;

    // turn off all motors and valves
    //motor_stop(true); // stop motor A
    //motor_stop(false); // stop motor B
    
  }
}



/*
 * E-stop interrupt to set the e-stop state. 
 * true => if e-stop has been pressed.
 * false => if estop has been deactived.
 * 
 * Args:
 *    None
 *    
 */
void intEStop() {

  // E-stop has been pressed when the digital pin is high
  if (digitalRead(E_STOP_BUT) == HIGH) {
    e_stop_active = true;
  } else {
    e_stop_active = false;
  }
  start_active = false;
  eStop();
}


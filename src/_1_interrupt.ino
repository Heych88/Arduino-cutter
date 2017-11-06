/*
void intEStop() {

  // E-stop has been pressed when the digital pin is high
  if (digitalRead(E_STOP_BUT) == HIGH) {
    e_stop_active = true;
  } else {
    e_stop_active = false;    
  }
}

void intButton() {

  delay(150);

  if(!digitalRead(START_BUT)){
    // Start stop button pressed
    start_active = !start_active;
    button = RUN;
  } else if (!digitalRead(UP_BUT)){
    // Up button pressed
    button = UP;
  } else if (!digitalRead(DOWN_BUT)){
    // Down button Press
    button = DOWN;
  } else if (!digitalRead(SELECT_BUT)){
    // Select button pressed
    button = SELECT;
  } else {
    button = NO_PRESS;
  }
}
*/

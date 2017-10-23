
void intEStop() {

  if (digitalRead(E_STOP_BUT) == HIGH) {
    // Is a rising edge so E-Stop has been cleared
    e_stop_active = true;
  } else {
    e_stop_active = false;    
  }
}

void intButton() {

  if(!digitalRead(START_BUT)){
    // Start stop button pressed
    start_active = !start_active;
    //if(start_active) {
    //  start_active = false;
    //} else {
    //  start_active = true;
    //}
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


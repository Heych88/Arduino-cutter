
void eStop() {
  // E-Stop is active so stop the machine
  
    //motor_stop(true); // stop motor A
    motor_stop(false); // stop motor B

    // dispaly E-Stop active
    printToScreen(estop_str, 0, 0, true, true);

}

void updateButton(const char button) {

  if (menu_selected) {
    // a previous menu was selected
    switch(state) {
      case MAIN:
        homeMenu();
        break;
      case SPEED:
        // update the system speed
        speedMenu(button);
        break;
      case QTY:
        // update the total number of pieces required
        qtyMenu(button);
        break;
      case LENGTH:
        // update the length of each piece
        lengthMenu(button);
        break;      
    }
    
  } else {
    // no menu selected so scroll or select a menu
    switch(button) {
      case UP:
        state++;
        if(state > LENGTH) state = LENGTH;
        break;
      case DOWN:
        state--;
        if(state < 0) state = 0;
        break;
      case SELECT:
        menu_selected = true;
        break;
      case RUN:
        break;
    }
    // update the display with the new menu
    if(button != NO_PRESS) setMenu();
  }
}

char pollButton() {

  char button = NO_PRESS;

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == LOW) e_stop_active = true;

  int pb_value = analogRead(SELECT_BUT); 

  if ((millis() - pb_time) >= 50) {
    pb_time = millis();
    if(pb_value < 10){
      // Start stop button pressed
      if(start_active) {
        start_active = false;
      } else {
        start_active = true;
      }

      while(analogRead(SELECT_BUT) < 10){
        // do nothing until the push button is released
        delay(20);
      }

      button = RUN;
      
    } else if (pb_value < 128){
      // Up button pressed
      button = UP;
    } else if (pb_value < 300){
      // Down button Press
      button = DOWN;
    } else if (pb_value < 500){
      // Left button press
      button = LEFT;
    } else if (pb_value < 700){
      // Select button pressed
      button = SELECT;
    } else {
       button = NO_PRESS;
    }
  } else {
     button = NO_PRESS;
  }

  if (button != NO_PRESS) updateButton(button);

  return button;
}




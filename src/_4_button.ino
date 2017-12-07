volatile int pb_debounce = 0;  // push button debounce time
char* estop_str = "E-STOP";

void eStop() {
  // E-Stop is active so stop the machine
  motor_stop();

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
      case PIERCE_LENGTH:
        // update the length of each piece
        pierceLengthMenu(button);
        break;
      case PIERCE_QTY:
        // update the number of pierces
        pierceQtyMenu(button);
        break;
      case CLEAR_QTY:
        clearQtyMenu(button);
        break;
      case PIERCE_DELAY:
        // update the delay for activating the pierce solenoid
        pierceDelayMenu(button);
        break;
      case CUT_DELAY:
        cutDelayMenu(button);
        break;
    }
  } else {
    // no menu selected so scroll or select a menu
    switch(button) {
      case UP:
        state++;
        break;
      case DOWN:
        state--;
        break;
      case SELECT:
        if(state != SPEED) menu_selected = true;
        break;
      case RUN:
        break;
    }
    state = max(min(state, MENU_SIZE), 0);
    
    // update the display with the new menu
    if((button != NO_PRESS) || (state == SPEED)) setMenu();
  }
}

char pollButton() {

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == HIGH) e_stop_active = true;

  // delay between button presses
  if ((millis() - pb_debounce) >= 150) {
    pb_debounce = millis(); 

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

    if ((button != NO_PRESS) || (state == SPEED)) updateButton(button);

    // Only accept held down push button inputs if a menu has been selected
    //if(!menu_selected || button == SELECT) button = NO_PRESS;
    while((!menu_selected) && ((!digitalRead(START_BUT)) || (!digitalRead(UP_BUT)) || 
          (!digitalRead(DOWN_BUT))) || (!digitalRead(SELECT_BUT))){
      delay(10);
    }
  }
}



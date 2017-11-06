// pushbutton char's for which button is pressed
#define SELECT 'S' // select / return button
#define RUN 'R' // stop start button (A)ctive
#define UP 'U' // up pushbutton
#define DOWN 'D' // down pushbutton
#define NO_PRESS 'N' // clears a button press

volatile char button; // tracks the button pressed
volatile int pb_debounce = 0;  // push button debounce time

void eStop() {
  // E-Stop is active so stop the machine
  motor_stop();

  // dispaly E-Stop active
  //printToScreen(estop_str, 0, 0, true, true);

}

void updateButton(const char button) {

  if (menu_selected) {
    // a previous menu was selected
    switch(state) {
      case MAIN:
        //homeMenu();
        break;
      case SPEED:
        // update the system speed
        //speedMenu(button);
        break;
      case QTY:
        // update the total number of pieces required
        //qtyMenu(button);
        break;
      case LENGTH:
        // update the length of each piece
        //lengthMenu(button);
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
    //if(button != NO_PRESS) setMenu();
  }
}

char pollButton() {

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == HIGH) e_stop_active = true;

  // delay between button presses
  if ((millis() - pb_debounce) >= 100) {
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

    if (button != NO_PRESS) updateButton(button);

    // Only accept held down push button inputs if a menu has been selected
    if(!menu_selected || button == SELECT) button = NO_PRESS;
  }
}



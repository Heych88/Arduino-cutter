
void printToScreen(const String str, const short col, const short row, const bool clear_row=true, const bool clear_screen=false) {
  // prints a string to the display in the defined cursor position
  // @param: str, string to print to screen
  // @param: col, display col position
  // @param: row, display row position
  // @param: clear_row, true => clears the display row, false => str will overlap current row text
  // @param: clear_screen, true => clears the screen

  if (clear_screen) {
    lcd.clear();
  } else if (clear_row) {
    lcd.setCursor(col, row);
    lcd.print(blank_line);
  }
  
  lcd.setCursor(col, row);
  lcd.print(str);
}

void homeMenu() {

  String qty_str = "Qty: " + String(qty_current) + "/" + String(qty_desired);
  printToScreen(qty_str, 0, 0, true, false);
  String len_str = String("Length: ") + String(cut_length) + String("mm");
  printToScreen(len_str, 0, 1, true, false);
}

void speedMenu(const char button) {
  // menu for setting the motor speed
  // @param: button, button that has been pressed.
  switch(button) {
    case UP:
      // up button pressed, increment the desired quantity
      pwm_desired++;
      if(pwm_desired > 100) pwm_desired = 100;
      break;
    case DOWN:
      // deincrement the desired quantity
      pwm_desired--;
      if(pwm_desired < 0) pwm_desired = 0;
      break;
    case SELECT:
      // return to home menu
      menu_selected = false;
      state = 0;
      break;
  }
  
  String qty_str = String("Set Speed:");
  printToScreen(qty_str, 0, 0, true, false);
  printToScreen(String(pwm_desired), 0, 1, true, false);
}

void qtyMenu(const char button) {
  // Quantity menu for setting the total number of pieces to cut
  // @param: button, button that has been pressed.
  switch(button) {
    case UP:
      // up button pressed, increment the desired quantity
      qty_desired++; 
      if(qty_desired > 1000) qty_desired = 1000;
      break;
    case DOWN:
      // deincrement the desired quantity
      qty_desired--;
      if(qty_desired < 0) qty_desired = 0;
      break;
    case SELECT:
      // return to home menu
      menu_selected = false;
      state = 0;
      break;
  }
  
  String qty_str = String("Set quantity:");
  printToScreen(qty_str, 0, 0, true, false);
  printToScreen(String(qty_desired), 0, 1, true, false);
}

void lengthMenu (const char button) {
  // Length menu for setting the length of each piece to cut
  // @param: button, button that has been pressed.
  switch(button) {
    case UP:
      // up button pressed, increment the piece length
      cut_length += 2; 
      if(cut_length > 1000) cut_length = 1000;
      break;
    case DOWN:
      // deincrement the piece length
      qty_desired -= 2;
      if(cut_length < 0) cut_length = 0;
      break;
    case SELECT:
      // return to home menu
      menu_selected = false;
      state = 0;
      break;
  }
  
  String qty_str = "Set length:";
  printToScreen(qty_str, 0, 0, true, false);
  String value_str = String(cut_length) + "mm";
  printToScreen(value_str, 0, 1, true, false);
}

void setMenu() {
  switch(state) {
    case MAIN:
      homeMenu();
      break;
    case SPEED:
      speedMenu(NO_PRESS);
      break;
    case QTY:
      qtyMenu(NO_PRESS);
      break;
    case LENGTH:
    lengthMenu(NO_PRESS);
      break;      
  }
}


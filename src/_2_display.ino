/************************************** Motor *****************************************/
int desired_speed = 60; // desired pwm rate of the motor

/************************************** Menu ******************************************/
bool menu_selected = false;  // keeps track if the user has enter a menu previously true => menu has been enter previously

/*********************************** Push Button **************************************/
// pushbutton char's for which button is pressed
#define SELECT 'S' // select / return button
#define RUN 'R' // stop start button (A)ctive
#define UP 'U' // up pushbutton
#define DOWN 'D' // down pushbutton
#define NO_PRESS 'N' // clears a button press

volatile char button; // tracks the button pressed

/**************************************************************************************/

// define the menu states classes
#define MAIN 0  // main menu state
#define SPEED 1 // speed menu state
#define QTY 2 // quantity menu state
#define LENGTH 3 // length of cut menu state

short state = MAIN; // the current system state

int qty_desired = 0; // total number of sleeves required for production
int qty_current = 0; // number of sleeves already produced
int cut_length = 0; // length of each piece


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
  lcd.noBlink();
}

void speedMenu(const char button) {
  // menu for setting the motor speed
  // @param: button, button that has been pressed.
  switch(button) {
    case UP:
      // up button pressed, increment the desired quantity
      desired_speed++;
      if(desired_speed > 100) desired_speed = 100;
      break;
    case DOWN:
      // deincrement the desired quantity
      desired_speed--;
      if(desired_speed < 0) desired_speed = 0;
      break;
    case SELECT:
      // return to home menu
      menu_selected = false;
      state = 0;
      break;
  }
  
  String qty_str = String("Set Speed:");
  printToScreen(qty_str, 0, 0, true, false);
  printToScreen(String(desired_speed), 0, 1, true, false);

  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
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

  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
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

  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
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


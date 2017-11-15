/************************************** Motor *****************************************/
int desired_speed = 60; // desired pwm rate of the motor

/****************************** drive wheel parameters ********************************/
const float wheel_diam = 61.0;  // diameter of the wheel
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor
const float wheel_dist_per_step = wheel_diam * PI / stepsPerRevolution; // distance travelled per step

/*********************************** Push Button **************************************/
// pushbutton char's for which button is pressed
#define SELECT 'S' // select / return button
#define RUN 'R' // stop start button (A)ctive
#define UP 'U' // up pushbutton
#define DOWN 'D' // down pushbutton
#define NO_PRESS 'N' // clears a button press

volatile char button; // tracks the button pressed

/************************************** Menu ******************************************/
bool menu_selected = false;  // keeps track if the user has enter a menu previously true => menu has been enter previously

// define the menu states classes
#define MAIN 0  // main menu state
#define CLEAR_QTY 1 // clear the already cut qty
#define SPEED 2 // speed menu state
#define QTY 3 // quantity menu state
#define LENGTH 4 // length of cut menu state
#define PIERCE_LENGTH 5 // length from edges of each pierce
#define PIERCE_QTY 6 // number of pierces
#define PIERCE_DELAY 7 // length from edges of each pierce
#define CUT_DELAY 8 // number of pierces

#define MENU_SIZE 8  // Number of menus that can be displayed

short state = MAIN; // the current system state

int qty_desired = 200; // total number of sleeves required for production
int qty_current = 0; // number of sleeves already produced
int cut_length = 25; // length of each piece
int pierce_length = 5; // length of each piece
int qty_pierce = 2; // length of each piece

bool clear_current_qty = false;

/**************************************************************************************/

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

int updateValue(const char button, int value, const int minimum, const int maximum){
  switch(button) {
    case UP:
      // up button pressed, increment the piece length
      value += 1; 
      break;
    case DOWN:
      // deincrement the piece length
      value -= 1; 
      break;
    case SELECT:
      // return to home menu
      menu_selected = false;
      state = 0;
      break;
  }

   value = max(min(value, maximum), minimum);
   return value;
}

void homeMenu() {

  String qty_str = "Qty: " + String(qty_current) + "/" + String(qty_desired);
  printToScreen(qty_str, 0, 0, true, false);
  String len_str = String("Length: ") + String(cut_length) + String("mm");
  printToScreen(len_str, 0, 1, true, false);
  lcd.noBlink();
}

void clearQtyMenu(const char button) {
  // menu for clearing current qty
  // @param: button, button that has been pressed.
  switch(button) {
    case UP:
      clear_current_qty = true;
      break;
    case DOWN:
      clear_current_qty = false;
      break;
    case SELECT:
      if(clear_current_qty) qty_current = 0;

      clear_current_qty = false;
    
      // return to home menu
      menu_selected = false;
      state = 0;
      break;
  }

  String qty_str = String("Clear Qty");
  printToScreen(qty_str, 0, 0, true, false);

  if(clear_current_qty){
    printToScreen("Yes", 0, 1, true, false);
  } else {
    printToScreen("No", 0, 1, true, false);
  }
  
  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
}

int getSpeed(){
  desired_speed = int(analogRead(TRIM_POT)/10);
  desired_speed = updateValue(NO_PRESS, desired_speed, 0, 100);
}

void speedMenu(const char button) {
  // menu for setting the motor speed
  // @param: button, button that has been pressed.

  getSpeed();
  
  String qty_str = String("Set Speed:");
  printToScreen(qty_str, 0, 0, true, false);
  printToScreen(String(desired_speed), 0, 1, true, false);
}

void qtyMenu(const char button) {
  // Quantity menu for setting the total number of pieces to cut
  // @param: button, button that has been pressed.
  
  qty_desired = updateValue(button, qty_desired, 0, 1000);
  
  String qty_str = String("Set quantity:");
  printToScreen(qty_str, 0, 0, true, false);
  printToScreen(String(qty_desired), 0, 1, true, false);

  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
}

void lengthMenu (const char button) {
  // Length menu for setting the length of each piece to cut
  // @param: button, button that has been pressed.
  
  cut_length = updateValue(button, cut_length, 0, 1000);
  
  String qty_str = "Set length:";
  printToScreen(qty_str, 0, 0, true, false);
  String value_str = String(cut_length) + "mm";
  printToScreen(value_str, 0, 1, true, false);

  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
}

void pierceLengthMenu (const char button) {
  // Length menu for setting the length of each piece to cut
  // @param: button, button that has been pressed.
  
  pierce_length = updateValue(button, pierce_length, 5, cut_length - 5);

  String pierce_str = "Set pierce dist:";
  printToScreen(pierce_str, 0, 0, true, false);
  String value_str = String(pierce_length) + "mm";
  printToScreen(value_str, 0, 1, true, false);

  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
}

void pierceQtyMenu (const char button) {
  // Length menu for setting the length of each piece to cut
  // @param: button, button that has been pressed.
  
  qty_pierce = updateValue(button, qty_pierce, 0, 2);

  String pierce_qty_str = "Set pierce qty:";
  printToScreen(pierce_qty_str, 0, 0, true, false);
  String value_str = String(qty_pierce);
  printToScreen(value_str, 0, 1, true, false);

  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
}

void pierceDelayMenu (const char button) {
  // Length menu for setting the length of each piece to cut
  // @param: button, button that has been pressed.
  
  pierce_delay = updateValue(button, pierce_delay, 50, 2000);

  String pierce_qty_str = "Set pierce delay";
  printToScreen(pierce_qty_str, 0, 0, true, false);
  String value_str = String(pierce_delay);
  printToScreen(value_str, 0, 1, true, false);

  // blink the cursor to indicate the menu has been selected
  if (menu_selected) lcd.blink();
}

void cutDelayMenu (const char button) {
  // Length menu for setting the length of each piece to cut
  // @param: button, button that has been pressed.
  
  cut_delay = updateValue(button, cut_delay, 50, 2000);

  String pierce_qty_str = "Set cut delay";
  printToScreen(pierce_qty_str, 0, 0, true, false);
  String value_str = String(cut_delay);
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
    case PIERCE_LENGTH:
      pierceLengthMenu(NO_PRESS);
      break;
    case PIERCE_QTY:
      pierceQtyMenu(NO_PRESS);
      break;
    case CLEAR_QTY:
      clearQtyMenu(NO_PRESS);
      break;
    case PIERCE_DELAY:
      pierceDelayMenu(NO_PRESS);
      break;
    case CUT_DELAY:
      cutDelayMenu(NO_PRESS);
      break;
  }  
}



#include <LiquidCrystal.h>
#include <Stepper.h>

/******************************** Push Buttons & E-Stop *******************************/
#define E_STOP_BUT 1
#define BUTTON_INTERRUPT 2
#define SELECT_BUT A3
#define UP_BUT 3
#define DOWN_BUT A1
#define START_BUT A2

volatile bool e_stop_active = false;

/*************************************** LCD *****************************************/
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9,8,6,7,4,5);

#define DISPLAY_ROWS 2
#define DISPLAY_COLS 16

char blank_line[DISPLAY_COLS];

/************************************ Solenoids **************************************/
#define SOLENOID_CUT A4
#define SOLENOID_PIERCE A5

/************************************ Solenoids **************************************/
#define TRIM_POT A0

/*************************************************************************************/

void setup() {

  // init motor parameters
  pinMode(SDA, OUTPUT);
  digitalWrite(SDA, LOW); // disable motor

  // init push buttons
  pinMode(SELECT_BUT, INPUT_PULLUP);
  pinMode(UP_BUT, INPUT_PULLUP);
  pinMode(DOWN_BUT, INPUT_PULLUP);
  pinMode(START_BUT, INPUT_PULLUP);
  pinMode(BUTTON_INTERRUPT, OUTPUT);

  // init solenoid parameters
  pinMode(SOLENOID_CUT, OUTPUT);
  pinMode(SOLENOID_PIERCE, OUTPUT);

  // set the E-stop button pin as an intterupt
  delay(500);
  pinMode(E_STOP_BUT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(E_STOP_BUT), intEStop, CHANGE);

  // set up the LCD's number of columns and rows:
  lcd.begin(DISPLAY_COLS, DISPLAY_ROWS);

  // create a blank string for clearing the text on one row of the LCD display
  for (int i=0; i < DISPLAY_COLS; i++) {
    blank_line[i] = ' ';
  }

  // Load the saved eeprom values
  getEepromValues();

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == HIGH) e_stop_active = true;
}


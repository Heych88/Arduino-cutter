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

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == HIGH) e_stop_active = true;
}



/*// LCD globals and parameters
  #define DISPLAY_ROWS 2
  #define DISPLAY_COLS 16

  /*char* speed_str = "Speed: %d%% ";
  char* qty_str = "Qty: %d/%d";
  char* total_str = "Total: %d ";
  char* length_str = "Length: %dmm ";*
  char blank_line[DISPLAY_COLS];

  // initialize the library with the numbers of the interface pins
  LiquidCrystal lcd(9,8,6,7,4,5); //(9, 8, 7, 6, 5, 4); // 8,9,4,5,6,7

  #define FORWARD LOW
  #define BACKWARD HIGH

  const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
  // initialize the stepper library on pins 8 through 11
  //Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);

  /*volatile int encoderCount = 0; // number of encoder revolutions
  volatile unsigned long time_stamp = millis(); // time between speed calculations
  volatile float motor_speed = 0; // the current speed of the motor*
  int desired_speed = 60; // desired pwm rate of the motor
  int qty_desired = 0; // total number of sleeves required for production
  int qty_current = 0; // number of sleeves already produced
  int cut_length = 0; // length of each piece

  /* drive wheel parameters
  const float wheel_diam = 61.0;  // diameter of the wheel
  const int ecode_ppr = 663; // number of encoder counts per revolution
  const float wheel_dist_ppr = wheel_diam * PI / ecode_ppr;*

  // Push buttons and E-Stop
  #define E_STOP_BUT 1
  char* estop_str = "E-STOP";
  volatile bool e_stop_active = false;

  #define BUTTON_INTERRUPT 2
  #define SELECT_BUT A3
  #define UP_BUT 3
  #define DOWN_BUT A1
  #define START_BUT A2
  volatile bool start_active = true;

  // pushbutton char's for which button is pressed
  #define SELECT 'S' // select / return button
  #define RUN 'R' // stop start button (A)ctive
  #define UP 'U' // up pushbutton
  #define DOWN 'D' // down pushbutton
  #define NO_PRESS 'N' // clears a button press

  // add a pushbutton delay
  unsigned long pb_time = 0;

  // define the menu states classes
  #define MAIN 0  // main menu state
  #define SPEED 1 // speed menu state
  #define QTY 2 // quantity menu state
  #define LENGTH 3 // length of cut menu state

  short state = MAIN; // the current system state
  unsigned short menu;
  bool menu_selected = false;  // keeps track if the user has enter a menu previously true => menu has been enter previously

  volatile char button; // tracks the button pressed


  // Solenoids
  #define SOLENOID_CUT A4
  #define SOLENOID_PIERCE A5


  void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(DISPLAY_COLS, DISPLAY_ROWS);

  // create a blank string for clearing the text on one row of the LCD display
  for (int i=0; i < DISPLAY_COLS; i++) {
    blank_line[i] = ' ';
  }

  pinMode(SELECT_BUT, INPUT_PULLUP);
  pinMode(UP_BUT, INPUT_PULLUP);
  pinMode(DOWN_BUT, INPUT_PULLUP);
  pinMode(START_BUT, INPUT_PULLUP);

  // init motor parameters
  pinMode(SDA, OUTPUT);

  // init solenoid parameters
  pinMode(SOLENOID_CUT, OUTPUT);
  pinMode(SOLENOID_PIERCE, OUTPUT);

  // set the E-stop button pin as an intterupt
  delay(500);
  pinMode(E_STOP_BUT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(E_STOP_BUT), intEStop, CHANGE);

  // set pin 2 as an intterupt for the E-stop
  pinMode(BUTTON_INTERRUPT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_INTERRUPT), intButton, CHANGE);

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == HIGH) e_stop_active = true;
  }*/


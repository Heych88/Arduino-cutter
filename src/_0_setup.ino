#include <LiquidCrystal.h>
#include <Stepper.h>

// LCD globals and parameters
#define INT_ENCODE_A 2
#define DISPLAY_ROWS 2
#define DISPLAY_COLS 16

char* speed_str = "Speed: %d%% ";
char* qty_str = "Qty: %d/%d";
char* total_str = "Total: %d ";
char* length_str = "Length: %dmm ";
char blank_line[DISPLAY_COLS];

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9,8,6,7,4,5); //(9, 8, 7, 6, 5, 4); // 8,9,4,5,6,7

// motor globals and parameters
#define FORWARD LOW
#define BACKWARD HIGH
// motor A
/*#define PWM_A 13
#define DIR_A 12
#define BRAKE_A 9
#define SENSE_A A0

// motor B
#define PWM_B 11
#define DIR_B 13
#define BRAKE_B 8
#define SENSE_B A1*/

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// initialize the stepper library on pins 8 through 11
Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);

volatile int encoderCount = 0; // number of encoder revolutions
volatile unsigned long time_stamp = millis(); // time between speed calculations
volatile float motor_speed = 0; // the current speed of the motor
int desired_speed = 60; // desired pwm rate of the motor
int qty_desired = 0; // total number of sleeves required for production
int qty_current = 0; // number of sleeves already produced
int cut_length = 0; // length of each piece

// drive wheel parameters
const float wheel_diam = 61.0;  // diameter of the wheel
const int ecode_ppr = 663; // number of encoder counts per revolution
const float wheel_dist_ppr = wheel_diam * PI / ecode_ppr;

// Push buttons and E-Stop
#define E_STOP_BUT 1
char* estop_str = "E-STOP";
volatile bool e_stop_active = false;

#define SELECT_BUT A3
#define UP_BUT 3
#define DOWN_BUT A1
#define START_BUT A2
bool start_active = true; //false;

// pushbutton char's for which button is pressed
#define SELECT 'S' // select / return button
#define RUN 'A' // stop start button (A)ctive
#define LEFT 'L' // left pushbutton
#define RIGHT 'R' // right pushbutton
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

//String[] = {"Speed", "Quantity", "Length"};

short state = MAIN; // the current system state
unsigned short menu;
bool menu_selected = false;  // keeps track if the user has enter a menu previously true => menu has been enter previously

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(DISPLAY_COLS, DISPLAY_ROWS);

  // create a blank string for clearing the text on one row of the LCD display
  for (int i=0; i < DISPLAY_COLS; i++) {
    blank_line[i] = ' ';
  }

  pinMode(SELECT_BUT, INPUT);
  pinMode(UP_BUT, INPUT);
  pinMode(DOWN_BUT, INPUT);
  pinMode(START_BUT, INPUT);

  // init motor parameters
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);

  // set pin 0 as an intterupt for the E-stop 
  delay(500);
  pinMode(E_STOP_BUT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(E_STOP_BUT), intEStop, CHANGE);
  
  // set pin 2 as an intterupt on the rising edge that calls he function intEncodeA() on the interrupt 
  //pinMode(INT_ENCODE_A, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(INT_ENCODE_A), intEncodeA, RISING);

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == HIGH) e_stop_active = true;
}


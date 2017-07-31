#include <LiquidCrystal.h>

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
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// motor globals and parameters
#define FORWARD LOW
#define BACKWARD HIGH
// motor A
#define PWM_A 3
#define DIR_A 12
#define BRAKE_A 9
#define SENSE_A A0

// motor B
#define PWM_B 11
#define DIR_B 13
#define BRAKE_B 8
#define SENSE_B A1

volatile int encoderCount = 0; // number of encoder revolutions
volatile unsigned long time_stamp = millis(); // time between speed calculations
volatile float motor_speed = 0; // the current speed of the motor
unsigned int pwm_desired = 60; // desired pwm rate of the motor

// drive wheel parameters
const float wheel_diam = 61.0;  // diameter of the wheel
const int ecode_ppr = 663; // number of encoder counts per revolution
const float wheel_dist_ppr = wheel_diam * PI / ecode_ppr;

// Push buttons and E-Stop
#define E_STOP_BUT 1
char* estop_str = "E-STOP";
volatile bool e_stop_active = false;

#define SELECT_BUT A0
#define UP_BUT A0
#define DOWN_BUT A0

#define START_BUT A0
bool start_active = false;

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

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(DISPLAY_COLS, DISPLAY_ROWS);

  // create a blank string for clearing the text on one row of the LCD display
  for (int i=0; i < DISPLAY_COLS; i++) {
    blank_line[i] = ' ';
  }

  // init motor parameters
  pinMode(PWM_B, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  pinMode(BRAKE_B, OUTPUT);

  // set pin 0 as an intterupt for the E-stop 
  delay(500);
  pinMode(E_STOP_BUT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(E_STOP_BUT), intEStop, CHANGE);
  
  // set pin 2 as an intterupt on the rising edge that calls he function intEncodeA() on the interrupt 
  pinMode(INT_ENCODE_A, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_ENCODE_A), intEncodeA, RISING);

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == LOW) e_stop_active = true;
}


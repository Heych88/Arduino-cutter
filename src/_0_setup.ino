#include <LiquidCrystal.h>

#define INT_ENCODE_A 2
#define DISPLAY_ROWS 2
#define DISPLAY_COLS 16

char* speed_str = "Speed: %d%% ";
char* qty_str_home = "Qty: %d/%d";
char* total_str = "Total: %d ";
char* length_str = "Length: %dmm ";
char blank_line[DISPLAY_COLS];

volatile int encoderCount = 0;
volatile unsigned long time_stamp = millis();

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // put your setup code here, to run once:
  
  // set up the LCD's number of columns and rows:
  lcd.begin(DISPLAY_COLS, DISPLAY_ROWS);

  // create a blank string for clearing the text on one row of the LCD display
  for (int i=0; i < DISPLAY_COLS; i++) {
    blank_line[i] = ' ';
  }

  // set pin 2 as an intterupt on the rising edge that calls he function intEncodeA() on the interrupt 
  pinMode(INT_ENCODE_A, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_ENCODE_A), intEncodeA, RISING);
}


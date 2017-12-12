/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 * 
 * Modified from the Arduino example eeprom_write.ino and 
 * arduino playground
 * https://playground.arduino.cc/Code/EEPROMReadWriteLong
 */

#include <EEPROM.h>

#define CUT_DELAY_ADDR 0
#define PIERCE_DELAY_ADDR 2
#define QTY_DESIRED_ADDR 4
#define CUT_LENGTH_ADDR 6
#define PIERCE_LENGTH_ADDR 8
#define PIERCE_QTY_ADDR 10
#define WHEEL_DIAM_ADDR 12
#define STEP_REV_ADDR 14
#define SOL_OFFSET_ADDR 16


int addr = 0;
int int_size = sizeof(int);

const int cut_delay = 200;  // delay between solenoid cutting and activation
const int pierce_delay = 200;

const int qty_desired = 1; // total number of sleeves required for production
const int cut_length = 50; // length of each piece
const int pierce_length = 7; // length of each piece
const int qty_pierce = 3; // length of each piece

const int wheel_diam = 61.0;  // diameter of the wheel
const int steps_per_revolution = 239;  // change this to fit the number of steps per revolution for your motor
const int pierce_sol_offset = 0;  // Offset between the cutting solenoid and the pierce solenoid.
                            // Pierce solenoid my be placed before the cut solenoid in the direction of travel.

/*
 * Splits int (16bit) values into bytes and stores them into 8bit EEPROM starting at the desired address.
 * 
 * Args:
 *    address: EEPROM address to store the values
 *    value: integer value to store at the address
 */
void eepromWrite(int address, int value)
{
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte one = (value & 0xFF);
  byte two = ((value >> 8) & 0xFF);

  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, one);
  EEPROM.write(address + 1, two);
}


void setup() {
  // initialize the LED pin as an output.
  pinMode(13, OUTPUT);

  // Clear the EEPROM
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  
  eepromWrite(CUT_DELAY_ADDR, cut_delay);
  eepromWrite(PIERCE_DELAY_ADDR, pierce_delay);
  eepromWrite(QTY_DESIRED_ADDR, qty_desired);
  eepromWrite(CUT_LENGTH_ADDR, cut_length);
  eepromWrite(PIERCE_LENGTH_ADDR, pierce_length);
  eepromWrite(PIERCE_QTY_ADDR, qty_pierce);
  eepromWrite(WHEEL_DIAM_ADDR, wheel_diam);
  eepromWrite(STEP_REV_ADDR, steps_per_revolution);
  eepromWrite(SOL_OFFSET_ADDR, pierce_sol_offset);

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
}

void loop() {
  
}

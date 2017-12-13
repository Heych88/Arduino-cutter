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

int cut_delay = 1234;  // delay between solenoid cutting and activation
int pierce_delay = 200;

int qty_desired = 1; // total number of sleeves required for production
int cut_length = 50; // length of each piece
int pierce_length = 7; // length of each piece
int qty_pierce = 3; // length of each piece

int wheel_diam = 61.0;  // diameter of the wheel
int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor
int pierce_sol_offset = 0;  // Offset between the cutting solenoid and the pierce solenoid.
                            // Pierce solenoid my be placed before the cut solenoid in the direction of travel.

/*
 * Reads EEPROM bytes and converts them into 16bit ints.
 * 
 * Args:
 *    address: EEPROM address to store the values
 *    value: integer value to store at the address
 * 
 */
int eepromRead(int address) {
  //Read the 4 bytes from the eeprom memory.
  int one = EEPROM.read(address);
  int two = EEPROM.read(address + 1);

  //Return the recomposed int by using bitshift.
  return one | two << 8;
}


/*
 * Splits int (16bit) values into bytes and stores them into 8bit EEPROM starting at the desired address.
 * 
 * Args:
 *    address: EEPROM address to store the values
 *    value: integer value to store at the address
 *    
 * Modified from the Arduino example eeprom_write.ino and 
 * arduino playground
 * https://playground.arduino.cc/Code/EEPROMReadWriteLong
 * 
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


void getEepromValues() {
  int addr = 0, int_size = sizeof(int);

  cut_delay = eepromRead(CUT_DELAY_ADDR);
  pierce_delay = eepromRead(PIERCE_DELAY_ADDR);
  qty_desired = eepromRead(QTY_DESIRED_ADDR);
  cut_length = eepromRead(CUT_LENGTH_ADDR);
  pierce_length = eepromRead(PIERCE_LENGTH_ADDR);
  qty_pierce = eepromRead(PIERCE_QTY_ADDR);
  wheel_diam = eepromRead(WHEEL_DIAM_ADDR);
  stepsPerRevolution = eepromRead(STEP_REV_ADDR);
  pierce_sol_offset = eepromRead(SOL_OFFSET_ADDR);
}

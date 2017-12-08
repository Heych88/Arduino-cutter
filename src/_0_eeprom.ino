#include <EEPROM.h>

int cut_delay = 1234;  // delay between solenoid cutting and activation
int pierce_delay = 200;

int qty_desired = 1; // total number of sleeves required for production
int cut_length = 50; // length of each piece
int pierce_length = 7; // length of each piece
int qty_pierce = 3; // length of each piece

int wheel_diam = 61.0;  // diameter of the wheel
int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor


//This function will return a 4 byte (32bit) long from the eeprom
//at the specified address to address + 3.
int eepromRead(int address) {
  //Read the 4 bytes from the eeprom memory.
  int one = EEPROM.read(address);
  int two = EEPROM.read(address + 1);

  //Return the recomposed int by using bitshift.
  return one | two << 8;
}


void getEepromValues() {
  int addr = 0, int_size = sizeof(int);

  cut_delay = eepromRead(addr);
  pierce_delay = eepromRead(addr + int_size);
  qty_desired = eepromRead(addr + 2 * int_size);
  cut_length = eepromRead(addr + 3 * int_size);
  pierce_length = eepromRead(addr + 4 * int_size);
  qty_pierce = eepromRead(addr + 5 * int_size);
  wheel_diam = eepromRead(addr + 6 * int_size);
  stepsPerRevolution = eepromRead(addr + 7 * int_size);
}

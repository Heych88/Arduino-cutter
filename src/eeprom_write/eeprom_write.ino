/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int addr = 0;
int int_size = sizeof(int);

const int cut_delay = 1234;  // delay between solenoid cutting and activation
const int pierce_delay = 200;

const int qty_desired = 1; // total number of sleeves required for production
const int cut_length = 50; // length of each piece
const int pierce_length = 7; // length of each piece
const int qty_pierce = 3; // length of each piece

const int wheel_diam = 61.0;  // diameter of the wheel
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor


//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + sizeof(int)
void EEPROMWritelong(int address, int value)
{
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte one = (value & 0xFF);
  byte two = ((value >> 8) & 0xFF);

  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, one);
  EEPROM.write(address + 1, two);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();
}


void setup() {
// initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  /** Empty setup. **/
  // initialize the LED pin as an output.
  pinMode(13, OUTPUT);

  // Clear the EEPROM
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  
  EEPROMWritelong(addr, cut_delay);
  EEPROMWritelong(addr + int_size, pierce_delay);
  EEPROMWritelong(addr + 2 * int_size, qty_desired);
  EEPROMWritelong(addr + 3 * int_size, cut_length);
  EEPROMWritelong(addr + 4 * int_size, pierce_length);
  EEPROMWritelong(addr + 5 * int_size, qty_pierce);
  EEPROMWritelong(addr + 6 * int_size, wheel_diam);
  EEPROMWritelong(addr + 7 * int_size, stepsPerRevolution);

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
}

void loop() {
  
}

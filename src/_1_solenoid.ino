#define ACTIVE_SOL HIGH
#define SOL_DELAY 200

volatile bool start_active = false; // tracks the state of if the system is running

void pierce_solenoid(){
  if(start_active) digitalWrite(SOLENOID_PIERCE, ACTIVE_SOL);
  delay(SOL_DELAY);
  digitalWrite(SOLENOID_PIERCE, !ACTIVE_SOL);
  delay(SOL_DELAY);
}

void cut_solenoid(){
  if(start_active) digitalWrite(SOLENOID_CUT, ACTIVE_SOL);
  delay(SOL_DELAY);
  digitalWrite(SOLENOID_CUT, !ACTIVE_SOL);
  delay(SOL_DELAY);
}


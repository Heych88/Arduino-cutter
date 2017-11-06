#define ACTIVE_SOL HIGH

volatile bool start_active = false; // tracks the state of if the system is running

void pierce_solenoid(){
  if(start_active) digitalWrite(SOLENOID_PIERCE, ACTIVE_SOL);
  delay(100);
  digitalWrite(SOLENOID_PIERCE, !ACTIVE_SOL);
}

void cut_solenoid(){
  if(start_active) digitalWrite(SOLENOID_CUT, ACTIVE_SOL);
  delay(100);
  digitalWrite(SOLENOID_CUT, !ACTIVE_SOL);
}


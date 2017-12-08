#define ACTIVE_SOL HIGH

int cut_delay = 200;  // delay between solenoid cutting and activation
int pierce_delay = 200;

volatile bool start_active = false; // tracks the state of if the system is running


/*
 * Activates and deactivate the piercing solenoid.
 * 
 * Args:
 *    None
 *    
 */
void pierce_solenoid(){
  if(start_active) digitalWrite(SOLENOID_PIERCE, ACTIVE_SOL);
  delay(pierce_delay);
  digitalWrite(SOLENOID_PIERCE, !ACTIVE_SOL);
  delay(pierce_delay);
}


/*
 * Activates and deactivate the cutting solenoid.
 * 
 * Args:
 *    None
 *    
 */
void cut_solenoid(){
  if(start_active) digitalWrite(SOLENOID_CUT, ACTIVE_SOL);
  delay(cut_delay);
  digitalWrite(SOLENOID_CUT, !ACTIVE_SOL);
  delay(cut_delay);
}


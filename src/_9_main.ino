
/*
 * Function to produce one sleeve with the desired sleeve settings. 
 * 
 * Args:
 *    None
 *    
 */
void runOneSleeve(){
  
  if(qty_pierce > 0) {
    motor_run(getDistanceCount(pierce_length - pierce_sol_offset) + 1);
    pierce_solenoid();
  
    if(qty_pierce == 2){
      motor_run(getDistanceCount(cut_length - (2 * pierce_length)));
      pierce_solenoid();
      motor_run(getDistanceCount(pierce_length + pierce_sol_offset) + 1);
    } else {
      motor_run(getDistanceCount(cut_length - pierce_length + pierce_sol_offset));
    }
  }else{
    motor_run(getDistanceCount(cut_length));
  }

  cut_solenoid(); // cut sleeve to desired length

  qty_current += 1;
}

/* 
 * main program loop 
 * 
 */
void loop() {
  
  if (e_stop_active) {
    start_active = false;
    // E-Stop is active so stop the machine
    eStop();
    state = MAIN;
    
    delay(1000);
    
  } else {
    // check if the start button is active to run the system
    if (start_active) {
      state = MAIN;
            
      while((qty_current < qty_desired) && (e_stop_active == false) && (start_active)) {
        // Normal running program
        pollButton();

        getSpeed(); // update the desired_speed
        if(desired_speed > 1) {
          runOneSleeve();
        } else {
          start_active = false;
        }

        homeMenu(); // update the display to show the current qty
        delay(100);
      }
      start_active = false;
    } 
    
    motor_stop();
    pollButton();

    if ((!menu_selected) && (state == MAIN)) homeMenu();
    if (!e_stop_active) delay(100);
  }
}


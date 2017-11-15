int run_one_sleeve(){
  // produces a single plastic sleeve

  if(qty_pierce > 0) {
    motor_run(pierce_length);
    pierce_solenoid();
  
    if(qty_pierce == 2){
      motor_run(abs(cut_length - (2 * pierce_length)));
      pierce_solenoid();
      motor_run(pierce_length);
    } else {
      motor_run(cut_length - pierce_length);
    }
  }else{
    motor_run(cut_length);
  }

  cut_solenoid(); // cut sleeve to desired length

  qty_current += 1;
}

// main program loop 
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
      while(qty_current < qty_desired){
        if ((e_stop_active) || (start_active == false)) break;

        state = MAIN;
        
        // Normal running program
        pollButton();
        run_one_sleeve();
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


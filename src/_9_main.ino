int run_one_sleeve(){
  // produces a single plastic sleeve

  if(qty_pierce > 0) {
    motor_run(pierce_length);
    pierce_solenoid();
  
    if(qty_pierce == 2){
      motor_run(cut_length - (qty_pierce * pierce_length));
      pierce_solenoid();
      motor_run(pierce_length);
    } else {
      motor_run(cut_length - pierce_length);
    }
  }else{
    motor_run(cut_length);
  }

  cut_solenoid(); // cut sleeve to desired length
}

// main program loop 
void loop() {

  //printToScreen(String(start_active), 0, 0);
  
  if (e_stop_active) {
    start_active = false;
    // E-Stop is active so stop the machine
    eStop();
    
    delay(1000);
    
  } else {
    // Normal running program
    pollButton();
    
    // check if the start button is active to run the system
    if (start_active) {
      // start running the system using motor B
      run_one_sleeve();
      delay(500);
    } else {
      motor_stop();
    }

    if ((!menu_selected) && (state == MAIN)) homeMenu();
    if (!e_stop_active) delay(100);
  }
}


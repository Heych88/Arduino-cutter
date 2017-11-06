int run_one_loop(){
  
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
      motor_run(1000);
      cut_solenoid();
    } else {
      motor_stop();
    }

    if ((!menu_selected) && (state == MAIN)) homeMenu();
    if (!e_stop_active) delay(100);
  }
}


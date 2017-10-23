// main program loop 
void loop() {
  
  if (e_stop_active) {
    start_active = false;
    // E-Stop is active so stop the machine
    eStop();
    
    delay(1000);
    
  } else {
    // Normal running program
    pollButton();

    start_active = true;
    
    // check if the start button is active to run the system
    if (start_active) {
      // start running the system using motor B
      motor_run(FORWARD);
    } else {
      motor_stop();
    }

    if ((!menu_selected) && (state == MAIN)) homeMenu();
    if (!e_stop_active) delay(100);
  }
}


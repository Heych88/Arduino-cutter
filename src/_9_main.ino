// main program loop 
void loop() {

  pollButton();
  if (e_stop_active) {
    start_active = false;
    // E-Stop is active so stop the machine
    eStop();
    
    delay(1000);
    
  } else {
    // Normal running program
    
    // check if the start button is active to run the system
    if (start_active) {
      // start running the system using motor B
      motor_run(false, FORWARD);
      //printToScreen("active", 0, 0, true, false);
    } else {
      // stop motor B
      motor_stop(false);
      //printToScreen("stopped", 0, 0, true, false);
    }

    if ((!menu_selected) && (state == MAIN)) homeMenu();
    if (!e_stop_active) delay(500);
  }
}


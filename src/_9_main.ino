// main program loop 
void loop() {
  
  if (e_stop_active) {
    // E-Stop is active so stop the machine
    eStop();
    
    delay(1000);
    
  } else {
    // Normal running program
    motor_run(false, FORWARD);
    printToScreen(speed_str, 0, 0, true, true);
    if (!e_stop_active) delay(2000);
    printToScreen(speed_str, 0, 1, false, false);
    if (!e_stop_active) delay(2000);
    printToScreen("ghgfhj", 0, 0, true, false);
    motor_stop(false);
    if (!e_stop_active) delay(2000);
  }
}


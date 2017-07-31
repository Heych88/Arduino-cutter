
void eStop() {
  // E-Stop is active so stop the machine
  
    //motor_stop(true); // stop motor A
    motor_stop(false); // stop motor B

    // dispaly E-Stop active
    printToScreen(estop_str, 0, 0, true, true);

}

void pollButton() {

  // check if E-stop is active
  if (digitalRead(E_STOP_BUT) == LOW) e_stop_active = true;

  int pb_value = analogRead(SELECT_BUT); 

  if ((millis() - pb_time) >= 200) {
    pb_time = millis();
    if(pb_value < 10){
      // Start stop button pressed
      if(start_active) {
        start_active = false;
      } else {
        start_active = true;
      }

      while(analogRead(SELECT_BUT) < 10){
        // do nothing until the push button is released
        delay(20);
      }
      
    } else if (pb_value < 128){
      // Up button pressed
      state++;
      if(state > 3) state = LENGTH;
    } else if (pb_value < 300){
      // Down button Press
      state--;
      if(state < 0) state = 0;
    } else if (pb_value < 500){
      // Left button press
    } else if (pb_value < 700){
      // Select button pressed
    } 

  }
}




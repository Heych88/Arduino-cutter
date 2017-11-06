

void intEStop() {

  // E-stop has been pressed when the digital pin is high
  if (digitalRead(E_STOP_BUT) == HIGH) {
    e_stop_active = true;
  } else {
    e_stop_active = false;
  }
  start_active = false;
  motor_stop();
}


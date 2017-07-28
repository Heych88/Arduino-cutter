// main program loop 
void loop() {
  // put your main code here, to run repeatedly:
  motor_run(false, FORWARD);
  printToScreen(speed_str, 0, 0, true, true);
  delay(2000);
  printToScreen(speed_str, 0, 1, false, false);
  delay(2000);
  printToScreen("ghgfhj", 0, 0, true, false);
  motor_stop(false);
  delay(2000);
}


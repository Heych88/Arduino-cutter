
void eStop() {
  // E-Stop is active so stop the machine
  
    //motor_stop(true); // stop motor A
    motor_stop(false); // stop motor B

    // dispaly E-Stop active
    printToScreen("stop", 0, 0, true, true);


}

//char pollButton() {
//  int value analogRead(
//}


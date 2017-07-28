
void intEncodeA() {
  // Interrupt handler 
  encoderCount++;

  /*if (encoderCount % 50 == 0) {
    unsigned int diff = millis() - time_stamp;
    time_stamp = millis();
    motor_speed = wheel_dist_ppr * 50 * 1000 / diff;
  }*/
}

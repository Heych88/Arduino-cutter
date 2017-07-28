
void printToScreen(const char* str, const short col, const short row, const bool clear_row=true, const bool clear_screen=false) {
  // prints a string to the display in the defined cursor position
  // @param: str, string to print to screen
  // @param: row, display row position
  // @param: col, display col position
  // @param: clear_row, true => clears the display row, false => str will overlap current row text
  // @param: clear_screen, true => clears the screen

  if (clear_screen) {
    lcd.clear();
  } else if (clear_row) {
    lcd.setCursor(col, row);
    lcd.print(blank_line);
  }
  
  lcd.setCursor(col, row);
  lcd.print(str);
}

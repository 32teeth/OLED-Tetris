/*
 *
 */
BUTTON LEFT = {A8, INPUT_PULLUP, HIGH, HIGH};
BUTTON ROTATE = {A7, INPUT_PULLUP, HIGH, HIGH};
BUTTON RIGHT = {A6, INPUT_PULLUP, HIGH, HIGH};

/*
** @method print_pins
** @desc create string buffer and dump to serial
*/
void print_pins() {
  char buffer[100];
  (String)sprintf(buffer,"LEFT:%d ROTATE:%d RIGHT:%d",LEFT.state, ROTATE.state, RIGHT.state);
  printComm(buffer);
}

/*
** @method set_pins
** @param button (Struct BUTTON)
** @desc set pin, pin mode and write initial button state
*/
void set_pins(BUTTON& button) {
  pinMode(button.pin, button.mode);
  digitalWrite(button.pin, button.state);
}

void set_pins() {
  set_pins(LEFT);
  set_pins(ROTATE);
  set_pins(RIGHT);
}

/*
** @method get_pins
** @param button (Struct BUTTON)
** @desc set button state
*/
void get_pins(BUTTON& button)
{
  button.state = digitalRead(button.pin);
}

void get_pins()
{
  get_pins(LEFT);
  get_pins(ROTATE);
  get_pins(RIGHT);

  #ifdef DEBUG
    // print_pins();
  #endif
}

/*
 *
 */
void controls() {
  /*
   *
   */
  if(ROTATE.state != ROTATE.last)
  {
    if(STATE == 1) {
      ROTATE.last = ROTATE.state;
      String state = ROTATE.state == LOW ? "ROTATE: Pressed" : "ROTATE: Released";
      if(ROTATE.state == LOW){rotate_tile();}
      printComm(state);
      //delay(100);
    }
    else {
      init_grid();
      display.display();
      delay(1000);
      STATE = 1;
    }
  }
  /*
   *
   */
  if(LEFT.state != LEFT.last)
  {
    LEFT.last = LEFT.state;
    String state = LEFT.last == LOW ? "LEFT: Pressed" : "LEFT: Released";
    printComm(state);
    //delay(100);
  }
  if(LEFT.state == LOW){move_tile(-1);}
  /*
   *
   */
  if(RIGHT.state != RIGHT.last)
  {
    RIGHT.last = RIGHT.state;
    String state = RIGHT.last == LOW ? "RIGHT: Pressed" : "RIGHT: Released";
    printComm(state);
    //delay(100);
  }
  if(RIGHT.state == LOW){move_tile(1);}
}

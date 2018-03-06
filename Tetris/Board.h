/*
 *
 */
void board_title() {
  display.drawRect(0, 0, 32, 11, WHITE);
  display.setCursor(5,7);
  display.print("Tetris");
}

/*
 *
 */
void board_next() {
  display.drawRect(0, 20, 32, 20, WHITE);
  display.setCursor(3,27);
  display.print("Next");
}

/*
 *
 */
void board_border() {
  display.drawLine(0, 127, 32, 127, WHITE);
}

/*
 *
 */
void board_score() {
  display.fillRect(0, 10, 32, 11, BLACK);
  display.drawRect(0, 10, 32, 11, WHITE);
  display.setCursor(3,17);
  //display.print(getPoints());
}

/*
 *
 */
void board(String type) {
  if(type.equals("title")){board_title();}
  if(type.equals("next")){board_next();}
  if(type.equals("border")){board_border();}
  if(type.equals("score")){board_score();}
}

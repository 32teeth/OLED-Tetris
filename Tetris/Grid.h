/*
 *
 */
void init_grid() {
  for(int y = 0; y < ROWS; y++){
    for(int x = 0; x < COLUMNS; x++) {
      GRID[x][y] = BLACK;
    }
  }
  if(STATE == 0)
  {
    display.setTextColor(WHITE);
    display.setCursor(8,72);
    display.print("Start");
    display.setCursor(8,82);
    display.print("Game");
  }
}

void over_grid() {
  for(int y = 0; y < ROWS; y++){
    for(int x = 0; x < COLUMNS; x++) {
      GRID[x][y] = WHITE;
    }
  }
display.fillRect(0, 62, 38, 26, BLACK);
display.setCursor(8, 72);
display.print("Game");
display.setCursor(8, 82);
display.print("Over");
}

/*
 *
 */
void display_grid() {
  static byte prevGrid[ROWS][COLUMNS]; // Static buffer to store previous grid state

  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      if (SIZE > 1) {
        if (GRID[x][y] != prevGrid[x][y]) {
          display.drawRect((x * SIZE) + X, (y * SIZE) + Y, SIZE, SIZE, BLACK);
          display.fillRect((x * SIZE) + X, (y * SIZE) + Y, SIZE - 1, SIZE - 1, GRID[x][y]);
          prevGrid[x][y] = GRID[x][y]; // Update the previous grid state
        }
      }
      else {
        if (GRID[x][y] != prevGrid[x][y]) {
          display.fillRect((x * SIZE) + X, (y * SIZE), SIZE, SIZE, GRID[x][y]);
          prevGrid[x][y] = GRID[x][y]; // Update the previous grid state
        }
      }
    }
  }
}

/*
 *
 */
void update_grid(int x, int y, uint16_t color) {
  GRID[x][y] = color;
}

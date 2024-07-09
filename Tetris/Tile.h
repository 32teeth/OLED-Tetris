/*
 *
 */
int current = random(7);
int next = random(7);
int rotation = 0;

TILE ACTIVE = {0, 0};

/*
 *
 */
void next_tile() {
  const byte shape[4] = {shapes[next][rotation][0],shapes[next][rotation][1],shapes[next][rotation][2],shapes[next][rotation][3]};

  display.fillRect(NX, NY, 4*(SIZE), 4*(SIZE), BLACK);
  for (byte i = 0; i < 4; i++) {
    for (short j = 3, d = 0; j != -1; j--, d++) {
      if (bitRead(shape[i], j) == 1) {
        if((SIZE) > 1) {
          display.drawRect(NX + (d*(SIZE)), NY + (i*(SIZE)), (SIZE), (SIZE), BLACK);
          display.fillRect(NX + (d*(SIZE)), NY + (i*(SIZE)), (SIZE)-1, (SIZE)-1, WHITE);
        }
        else {
          display.fillRect(NX + (d*(SIZE)), NY + (i*(SIZE)), (SIZE), (SIZE), WHITE);
        }
      }
    }
  }

  //ACTIVE.x = random(10-SIZE);
}

void clear_tile() {
  const byte shape[4] = {shapes[current][rotation][0],shapes[current][rotation][1],shapes[current][rotation][2],shapes[current][rotation][3]};
  for (byte i = 0; i < 4; i++) {
    for (short j = 3, d = 0; j != -1; j--, d++) {
      if (bitRead(shape[i], j) == 1) {
        update_grid((ACTIVE.x + d), (ACTIVE.y + i) - 1, BLACK);
        update_grid((ACTIVE.x + d), (ACTIVE.y + i), BLACK);
      }
    }
  }
  delay(50);
}

/*
 *
 */
void rotate_tile() {
  clear_tile();
  rotation++;
  if(rotation >= rotations[current]){rotation = 0;}
}

/*
 *
 */
void move_tile(int dir) {
void move_tile(int dir) {
  clear_tile();
  ACTIVE.x += dir;
  if (ACTIVE.x >= (COLUMNS - 4)) { ACTIVE.x = COLUMNS - 4; }
  if (ACTIVE.x <= 1) { ACTIVE.x = 1; }
  display_tile();
}

/*
 *
 */
void add_tile() {
  current = next;
  next = random(7);
  next_tile();
}

/*
 *
 */
bool tile_hit_bottom() {
  return ((ACTIVE.y) > ROWS - 5) ? true : false;
}

/*
 *
 */
bool tile_hit_collision() {
  short p[4];
  short shifted[4];

  for (byte i = 0; i < 3; i++) {
    shifted[i] = shapes[current][rotation][i + 1];
  }
  shifted[3] = 0;

  for (byte i = 0; i < 4; i++) {
    p[i] = shapes[current][rotation][i] - (shapes[current][rotation][i] & shifted[i]);
  }

  for (byte i = 0; i < 4; i++) {
    byte x = 0;
    for (short j = 3; j != -1; j--) {
      if (bitRead(p[i], j) == 1) {
        if (GRID[ACTIVE.x + x][max(0, ACTIVE.y + i + 1)] != BLACK) {
          if (max(0, ACTIVE.y + i + 1) - SIZE <= SIZE) {
            Serial.println("GAME OVER");
            STATE = 2;
            over_grid();
          }
          return true;
        }
      }
      x++;
    }
  }
  return false;
}

/*
 *
 */
void drop_tile() {
  static const byte shape[4][4] = {
    shapes[current][rotation][0], shapes[current][rotation][1],
    shapes[current][rotation][2], shapes[current][rotation][3]
  };

  if (ACTIVE.y >= 0) {
    clear_tile();

    for (byte i = 0; i < 4; i++) {
      for (short j = 3, d = 0; j != -1; j--, d++) {
        if (bitRead(shape[i], j) == 1) {
          update_grid((ACTIVE.x + d), (ACTIVE.y + i), WHITE);
        }
      }
    }
  }

  if (tile_hit_bottom() || tile_hit_collision()) {
    if (STATE != 2) {
      add_tile();
    }
    rotation = 0;
    ACTIVE.y = 0;
  }
  else {
    ACTIVE.y++;
  }
}

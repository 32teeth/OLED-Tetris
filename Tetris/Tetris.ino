/*
 *
 */
#define DEBUG

/*
 *
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/Picopixel.h>

/*
 *
 */
#include "Definitions.h";
#include "Timing.h";
#include "Structs.h";
#include "Comm.h";
#include "Pins.h";

/*
 *
 */
Adafruit_SSD1306 display(OLED_RESET);

/*
 *
 */
int GRID[COLUMNS][ROWS];
int STATE = 0; // 0 = Start, 1 = Playing, 2 = Game Over

/*
 *
 */
#include "Shapes.h"
#include "Grid.h"
#include "Tile.h"
#include "Board.h"
#include "Controls.h";

/*
 *
 */
void setup() {
  /*
   *
   */
  startComm();
  listenComm();
  printComm("\nReady\n");

  /*
   *
   */
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setFont(&Picopixel);
  display.setRotation(1);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  /*
   *
   */
  board("title");
  board("score");
board("next");
board("border");

init_grid();
next_tile();
add_tile();

set_pins();
}

void loop() {
  unsigned long now = millis();
  static unsigned long lastUpdateTime = 0;
  static const unsigned long updateInterval = 50; // Update display every 50 ms

  if (now - lastUpdateTime >= updateInterval) {
    lastUpdateTime = now;

    if (STATE == 1) {
      drop_tile();
    }
    if (STATE == 2) {
      over_grid();
    }

    // Optimize display updates
    bool needsUpdate = false;
    static byte prevGrid[ROWS][COLUMNS];
    static byte prevActive = current;
    static byte prevRotation = rotation;
    static byte prevActiveX = ACTIVE.x;
    static byte prevActiveY = ACTIVE.y;

    for (int y = 0; y < ROWS; y++) {
      for (int x = 0; x < COLUMNS; x++) {
        if (GRID[x][y] != prevGrid[x][y]) {
          needsUpdate = true;
          break;
        }
      }
      if (needsUpdate) break;
    }

    if (current != prevActive || rotation != prevRotation || ACTIVE.x != prevActiveX || ACTIVE.y != prevActiveY) {
      needsUpdate = true;
    }

    if (needsUpdate) {
      display_grid();
      memcpy(prevGrid, GRID, sizeof(GRID));
      prevActive = current;
      prevRotation = rotation;
      prevActiveX = ACTIVE.x;
      prevActiveY = ACTIVE.y;
    }
  }

  get_pins();
  controls();
}

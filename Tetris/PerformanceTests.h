#include <Arduino.h>

void test_drop_tile() {
  unsigned long start = micros();
  for (int i = 0; i < 1000; i++) {
    drop_tile();
  }
  unsigned long end = micros();
  Serial.print("Time to drop tile 1000 times: ");
  Serial.print(end - start);
  Serial.println(" microseconds");
}

void test_display_grid() {
  unsigned long start = micros();
  for (int i = 0; i < 1000; i++) {
    display_grid();
  }
  unsigned long end = micros();
  Serial.print("Time to display grid 1000 times: ");
  Serial.print(end - start);
  Serial.println(" microseconds");
}

void run_performance_tests() {
  test_drop_tile();
  test_display_grid();
  // Add more test cases as needed
}

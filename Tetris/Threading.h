#include <Arduino.h>

// Define a task for input handling
void inputTask(void* parameter) {
  while (true) {
    get_pins();
    controls();
    delay(50); // Add a small delay to avoid hogging the CPU
  }
}

// Define a task for rendering
void renderTask(void* parameter) {
  while (true) {
    display_grid();
    delay(50); // Add a small delay to avoid hogging the CPU
  }
}

// Initialize tasks in the setup function
void init_tasks() {
  xTaskCreate(inputTask, "Input Task", 128, NULL, 1, NULL);
  xTaskCreate(renderTask, "Render Task", 128, NULL, 1, NULL);
}

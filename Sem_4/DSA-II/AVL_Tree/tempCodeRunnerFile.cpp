#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


// Define the dimensions of the grid
#define WIDTH 80
#define HEIGHT 25

// Define the colors
#define BLACK 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

// Define the number of lights
#define NUM_LIGHTS 100

// Create a grid of lights
int grid[WIDTH][HEIGHT];

// Initialize the grid with random colors
void init_grid() {
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      grid[i][j] = rand() % 8;
    }
  }
}

// Update the grid with new colors
void update_grid() {
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      grid[i][j] = (grid[i][j] + 1) % 8;
    }
  }
}

// Draw the grid to the console
void draw_grid() {
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      switch (grid[i][j]) {
        case BLACK:
          printf(" ");
          break;
        case RED:
          printf("\033[31m#\033[0m");
          break;
        case GREEN:
          printf("\033[32m#\033[0m");
          break;
        case BLUE:
          printf("\033[34m#\033[0m");
          break;
        case YELLOW:
          printf("\033[33m#\033[0m");
          break;
        case MAGENTA:
          printf("\033[35m#\033[0m");
          break;
        case CYAN:
          printf("\033[36m#\033[0m");
          break;
        case WHITE:
          printf("\033[37m#\033[0m");
          break;
      }
    }
    printf("\n");
  }
}

// Main function
int main() {
  // Initialize the random number generator
  srand(time(NULL));

  // Initialize the grid
  init_grid();

  // Main loop
  while (1) {
    // Update the grid
    update_grid();

    // Draw the grid
    draw_grid();

    // Sleep for a short period of time
    Sleep(100000);
  }

  return 0;
}

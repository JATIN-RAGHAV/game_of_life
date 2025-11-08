#include "raylib.h"
#include "variables.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>

#ifndef HELPER
#define HELPER
void updMap(std::vector<std::vector<int>> &grid) {
  int rows = grid.size();
  int cols = grid[0].size();
  std::vector<std::vector<int>> killed;
  std::vector<std::vector<int>> alive;
  std::vector<std::vector<int>> neighbours = {{-1, -1}, {-1, +1}, {-1, 0},
                                              {+1, 0},  {+1, -1}, {+1, +1},
                                              {0, +1},  {0, -1}};
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      int n = 0;
      for (int k = 0; k < neighbours.size(); k++) {
        int nx = i + neighbours[k][0];
        int ny = j + neighbours[k][1];
        if (nx < 0 || nx > rows - 1 || ny < 0 || ny > cols - 1)
          continue;
        else {
          if (grid[nx][ny] == 1) {
            n += 1;
          }
        }
      }
      // std::cout << n << "|";
      if (grid[i][j] == 1 && n < 2) {
        // grid[i][j] = 0;
        killed.push_back({i, j});
        // std::cout << "Killed ";
      } else if (grid[i][j] == 1 && (n == 2 || n == 3))
        alive.push_back({i, j});
      else if (grid[i][j] == 1 && n > 3) {
        killed.push_back({i, j});
        // std::cout << "Killed ";
      } else if (grid[i][j] == 0 && n == 3)
        alive.push_back({i, j});
    }
  }
  for (int i = 0; i < killed.size(); i++) {
    int x = killed[i][0];
    int y = killed[i][1];
    grid[x][y] = 0;
  }
  for (int i = 0; i < alive.size(); i++) {
    int x = alive[i][0];
    int y = alive[i][1];
    grid[x][y] = 1;
  }
}

void spawnX(std::vector<std::vector<int>> &grid, int x) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  int rows = grid.size();
  int cols = grid[0].size();
  for (int k = 0; k < x; k++) {
    int r = (rand() % rows);
    int c = (rand() % cols);
    grid[r][c] = 1;
  }
}
void render_grid(std::vector<std::vector<int>> &grid) {
  // ClearBackground(BG_COLOR);
  Rectangle square = GetShapesTextureRectangle();
  square.height = square.width = CELL_SIZE;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      square.x = i * (CELL_SIZE) + (i + 1) * MARGIN;
      square.y = j * (CELL_SIZE) + (j + 1) * MARGIN;
      if (grid[i][j]) {
        DrawRectangleRounded(square, ROUNDED, CELL_SIZE, LIVING);
      } else {
        DrawRectangleRounded(square, ROUNDED, CELL_SIZE, DEAD);
      }
    }
  }
}
#endif

#ifndef USER_INPUT
#define USER_INPUT

void change_cell(std::vector<std::vector<int>> &grid, int state) {
  Vector2 location = GetMousePosition();
  int x = (location.x) / (CELL_SIZE + MARGIN);
  int y = (location.y) / (CELL_SIZE + MARGIN);
  if (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size()) {
    grid[x][y] = state;
  }
}

void take_grid_pos(std::vector<std::vector<int>> &grid,
                   std::vector<std::vector<int>> &pred_grid) {
  SetTargetFPS(INPUT_FPS);
  while (!WindowShouldClose()) {
    BeginDrawing();
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_F)) {
      break;
    }
    if (IsKeyPressed(QUIT)) {
      EndDrawing();
      CloseWindow();
      exit(0);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      change_cell(grid, 1);
      change_cell(pred_grid, 1);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      change_cell(grid, 0);
      change_cell(pred_grid, 0);
    }
    ClearBackground(BG_COLOR);
    render_grid(grid);
    render_grid(pred_grid);
    updMap(pred_grid);
    EndDrawing();
  }
  SetTargetFPS(FPS);
}
#endif

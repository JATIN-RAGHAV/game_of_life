#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <vector>

std::vector<std::vector<int>> updMap(std::vector<std::vector<int>> grid) {
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
  return grid;
}

std::vector<std::vector<int>> spawnX(std::vector<std::vector<int>> grid,
                                     int x) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  int rows = grid.size();
  int cols = grid[0].size();
  for (int k = 0; k < x; k++) {
    int nx = (rand() % (rows - 1)) + 1;
    int ny = (rand() % (rows - 1)) + 1;
    grid[nx][ny] = 1;
  }
  return grid;
}

int main(void) {
  const int margin = 3;
  const int sH = 1000;
  const int sW = 1000;
  const int screenWidth = sW + margin * 2;
  const int screenHeight = sH + margin * 2;
  const int cell_size = 10;
  const int grid_rows = sH / cell_size;
  const int grid_cols = sW / cell_size;
  InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
  Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
  int sensitivity = 100;
  SetTargetFPS(10);
  std::vector<std::vector<int>> grid;
  std::vector<int> temp;
  for (int i = 0; i < grid_rows; i++) {
    temp.clear();
    for (int j = 0; j < grid_cols; j++) {
      temp.push_back(0);
    }
    grid.push_back(temp);
  }
  // grid[0][0] = 2;
  grid[5][5] = 1;
  grid[6][7] = 1;
  grid[7][4] = 1;
  grid[7][5] = 1;
  grid[7][8] = 1;
  grid[7][9] = 1;
  grid[7][10] = 1;
  grid = spawnX(grid, 2000);
  // grid[7][7] = 1;
  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_RIGHT))
      ballPosition.x += GetFrameTime() * 2.0f * sensitivity;
    if (IsKeyDown(KEY_LEFT))
      ballPosition.x -= GetFrameTime() * 2.0f * sensitivity;
    if (IsKeyDown(KEY_UP))
      ballPosition.y -= GetFrameTime() * 2.0f * sensitivity;
    if (IsKeyDown(KEY_DOWN))
      ballPosition.y += GetFrameTime() * 2.0f * sensitivity;
    BeginDrawing();

    ClearBackground(DARKGRAY);

    DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

    // DrawCircleV(ballPosition, 50, MAROON);
    grid = updMap(grid);
    std::cout << "New Frame\n";
    for (int i = 0; i < grid_rows; i++) {
      for (int j = 0; j < grid_cols; j++) {
        // std::cout << i * cell_size << " " << j * cell_size << std::endl;
        if (grid[i][j] == 1) {
          DrawRectangle(j * cell_size + margin, i * cell_size + margin,
                        cell_size, cell_size, DARKBLUE);
        } else if (grid[i][j] == 2) {
          DrawRectangle(j * cell_size + margin, i * cell_size + margin,
                        cell_size, cell_size, RED);
        } else {
          DrawRectangle(j * cell_size + margin, i * cell_size + margin,
                        cell_size, cell_size, GRAY);
        }
        DrawRectangleLines(j * cell_size + margin, i * cell_size + margin,
                           cell_size, cell_size, DARKGRAY);
      }
    }

    EndDrawing();
  }
  CloseWindow();

  return 0;
}

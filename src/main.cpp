#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "helper.cpp"
#include "variables.hpp"

int main(void) {
        const int screenWidth = COLS*(CELL_SIZE) + (COLS+1)*MARGIN;
        const int screenHeight = ROWS*(CELL_SIZE) + (ROWS+1)*MARGIN;
        InitWindow(screenWidth, screenHeight, "Game of Life");
        std::vector grid(ROWS,std::vector<int>(COLS));
        int rate = 1;
        SetTargetFPS(FPS);
        take_grid_pos(grid);
        double time = 0;
        while (!WindowShouldClose()) {
                BeginDrawing();

                if(IsKeyPressed(KEY_S)){
                        take_grid_pos(grid);
                }
                if(IsKeyPressed(QUIT)){
                        EndDrawing();
                        break;
                }
                if(IsKeyPressed(KEY_DOWN)){
                        rate--;
                        if(rate<0){
                                rate = 0;
                        }
                }
                if(IsKeyPressed(KEY_UP)){
                        rate++;
                        if(rate>MAX_RATE){
                                rate = MAX_RATE;
                        }
                }
                time+=GetFrameTime();
                if((time*rate)>=1){
                        updMap(grid);
                        time = 0;
                }
                render_grid(grid);

                EndDrawing();
        }
        CloseWindow();

        return 0;
}

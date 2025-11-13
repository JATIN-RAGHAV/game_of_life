#include "camera.cpp"
#include "helper.cpp"
#include "rendering.cpp"
#include "raylib.h"
#include "start_screen.cpp"
#include "variables.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "camera.cpp"
bool running = true;
int main(void) {
        InitWindow(screenWidth, screenHeight, "Game of Life");
        std::vector grid(ROWS, std::vector<int>(COLS));
        int rate = 1;
        SetTargetFPS(FPS);
        show_start_screen(screenWidth, screenHeight);
        double time = 0;
        Camera2D camera;
        init_camera(camera);
        target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        bloom = LoadShader(0, TextFormat("./resources/bloom.fs", GLSL_VERSION));
        edit_mode(grid,camera);
        // this loop only runs the 'run' mode
        while (!WindowShouldClose()) {
                handle_run_inputs(grid, running,rate,camera);
                update_camera(camera);
                time += GetFrameTime();
                if ((time * rate) >= 1 && running){
                        updMap(grid);
                        time = 0;
                }
                render_grid(grid,camera);
        }
        CloseWindow();
        return 0;
}

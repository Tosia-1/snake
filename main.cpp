#include <iostream>
#include <unistd.h>
using namespace std;

#include "raylib.h"

int main()
{
    InitWindow(800, 450, "raylib example - basic window");
    int posX = 200;
    int posY = 200;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_RIGHT)) {
            posX += 2;
            cout << posX << endl;
        }
        if (IsKeyPressed(KEY_LEFT)) {
            posX -= 2;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        // Rectangle
        DrawFPS(20, 20);
        DrawRectangle(posX, posY, 120, 60, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


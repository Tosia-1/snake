#include <iostream>
#include <cmath>
#include <deque>
#include "raylib.h"

using namespace std;


enum Dir {N = 1, E, S, W};

class Block {
public:
    double x;
    double y;
    double length;

    void draw(int width) {
        DrawRectangle(round(x), round(y), round(length), width, DARKGREEN);
    }
};

int main() {
    InitWindow(800, 450, "snake");
    SetTargetFPS(30);

    int width = 20;
    int speed = 70; // pixels per second


    deque<Block> snake;
    snake.push_back({200, 200, 100});
    Dir direction{Dir::E};

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_RIGHT)) {
            direction = Dir::E;
        }
        if (IsKeyPressed(KEY_UP)) {
            direction = Dir::N;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            direction = Dir::S;
        }
        if (IsKeyPressed(KEY_LEFT)) {
            direction = Dir::W;
        }

        double frameTime = GetFrameTime();
        if (direction == Dir::E) {
            snake.at(0).x += speed * frameTime;
        }
        else if (direction == Dir::S) {
            snake.at(0).y += speed * frameTime;
        }
        else if (direction == Dir::N) {
            snake.at(0).y -= speed * frameTime;
        }
        else if (direction == Dir::W) {
            snake.at(0).x -= speed * frameTime;
        }
        //cout << frame_time << endl;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(20, 20);
        for (auto bl : snake) {
            bl.draw(width);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


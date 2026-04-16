#include <cassert>
#include <iostream>
#include <cmath>
#include <deque>
#include "raylib.h"

using namespace std;

enum Dir { N = 1, E, S, W };

class Block {
public:
    int x;
    int y;
    int length;
    Dir direction;

    void draw(int width, Color color) {
        if (direction == Dir::E || direction == Dir::W) {
            DrawRectangle(x, y, length, width, color);
        } else if (direction == Dir::N || direction == Dir::S) {
            DrawRectangle(x, y, width, length, color);
        }
    }

    void growTip(int d) {
        if (direction == Dir::N) {
            y -= d;
        } else if (direction == Dir::W) {
            x -= d;
        }
        length += d;
    }

    void shrinkBase(int d) {
        assert(d < length);
        if (direction == Dir::S) {
            y += d;
        } else if (direction == Dir::E) {
            x += d;
        }
        length -= d;
    }
};

class Snake {
    deque<Block> blocks;
    double deltaTime = 0;

public:
    int width;
    Color color;

    Snake(int initialLength, int width, Color color)
        : width{width},
          color{color} {
        blocks.push_back({100, 200, initialLength, Dir::E});
    }

    void draw() {
        for (auto block: blocks) {
            block.draw(width, color);
        }
    }

    void move(double speed, double currentTime);

    void updateDir() {
        Dir dir = blocks.back().direction;
        if (IsKeyPressed(KEY_RIGHT)) {
            turnEast();
        }
        if (IsKeyPressed(KEY_UP)) {
            turnNorth();
        }
        if (IsKeyPressed(KEY_DOWN)) {
            //direction = Dir::S;
        }
        if (IsKeyPressed(KEY_LEFT)) {
            //direction = Dir::W;
        }
    }

private:
    void turnNorth() {
        Block &head = blocks.back();
        assert(head.length >= width);
        if (head.direction == Dir::E) {
            head.length -= width;
            blocks.push_back({head.x + head.length, head.y, width, Dir::N});
        } else if (head.direction == Dir::W) {
            head.length -= width;
            head.x += width;
            blocks.push_back({head.x - width, head.y, width, Dir::N});
        }
    }

    void turnEast() {
        Block &head = blocks.back();
        if (head.direction == Dir::N) {
            head.length -= width;
            head.y += width;
            blocks.push_back({head.x, head.y - width, width, Dir::E});
        } else if (head.direction == Dir::W) {
            head.length -= width;
            blocks.push_back({head.x, head.y + head.length, width, Dir::E});
        }
    }
};

void Snake::move(double speed, double currentTime) {
    currentTime += deltaTime;
    int d = int(round(speed * currentTime));
    double updateTime = d / speed;
    deltaTime = currentTime - updateTime;

    blocks.back().growTip(d);

    while (d > 0) {
        Block &tail = blocks.front();
        assert(tail.length > 0);

        int dd = min(d, tail.length);
        d -= dd;

        if (tail.length <= dd) {
            blocks.pop_front();
        } else {
            tail.shrinkBase(dd);
        }
    }
}

int main() {
    InitWindow(800, 450, "snake");
    SetTargetFPS(120);

    double speed = 40; // pixels per second

    Snake snake{100, 20, DARKGREEN};
    //blocks.push_back({200, 200, 100, Dir::E});
    // deque<Block> snake;
    // Dir direction{Dir::E};

    while (!WindowShouldClose()) {
        //direction = updateDir(direction);
        double frameTime = GetFrameTime();
        //updatePos(snake.at(0), direction, speed, frameTime);
        snake.updateDir();
        snake.move(speed, frameTime);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(20, 20);
        snake.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

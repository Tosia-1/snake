#include <cassert>
#include <iostream>
#include <cmath>
#include <deque>
#include "raylib.h"

using namespace std;

enum Dir { N = 1, E, S, W };

class Block {
public:
    double x;
    double y;
    double length;
    Dir direction;

    void draw(int width, Color color) {
        if (direction == Dir::E || direction == Dir::W) {
            DrawRectangle(round(x), round(y), round(length), width, color);
        } else if (direction == Dir::N || direction == Dir::S) {
            DrawRectangle(round(x), round(y), width, round(length), color);
        }
    }
};

class Snake {
    deque<Block> blocks;

public:
    double initialLength;
    double width;
    Color color;

    Snake(double initialLength, double width, Color color)
        : initialLength{initialLength},
          width{width},
          color{color} {
        blocks.push_back({100, 200, initialLength, Dir::E});
    }

    void draw() {
        for (auto block: blocks) {
            block.draw(width, color);
        }
    }

    void move(double speed, double deltaTime);

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

void Snake::move(double speed, double deltaTime) {
    double d = speed * deltaTime;

    Block &head = blocks.back();
    if (head.direction == Dir::N) {
        head.y -= d;
    } else if (head.direction == Dir::W) {
        head.x -= d;
    }
    head.length += d;

    {
        Block &tail = blocks.front();
        if (tail.direction == Dir::S) {
            tail.y += d;
        } else if (tail.direction == Dir::E) {
            tail.x += d;
        }
    }

    while (d > 0) {
        Block &tail = blocks.front();
        assert(tail.length > 0);
        double dd = min(d, tail.length);
        tail.length -= dd;
        d -= dd;
        if (tail.length <= 0) {
            blocks.pop_front();
        }
    }

}


void updatePos(Block &block, Dir dir, double speed, double deltaTime) {
    double d = speed * deltaTime;
    if (dir == Dir::E) {
        block.x += d;
    } else if (dir == Dir::S) {
        block.y += d;
    } else if (dir == Dir::N) {
        block.y -= d;
    } else if (dir == Dir::W) {
        block.x -= d;
    }
}


int main() {
    InitWindow(800, 450, "snake");
    SetTargetFPS(120);

    int width = 20;
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

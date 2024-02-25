#include "raylib.h"

const Color snowColors[] = {{249, 249, 249, 255}, {237, 237, 237, 255}, {224, 224, 224, 255}};

struct tile
{
    Color snowColor;
    Rectangle hitBox;
    short type; // 0 for nothing 1 for snow
};

const int tileSize = 5;
struct tile tiles[256][144];

int totalSnowflakes;

void input() {
    // add snow
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        for (int x = 0; x < 256; x++) {
            for (int y = 0; y < 144; y++) {
                if (CheckCollisionPointRec(GetMousePosition(), tiles[x][y].hitBox) && tiles[x][y].type == 0) {
                    tiles[x][y].type = 1;
                    tiles[x][y].snowColor = snowColors[GetRandomValue(0, 2)];
                    totalSnowflakes++;
                }
            }
        }
    }
    // remove snow
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        for (int x = 0; x < 256; x++) {
            for (int y = 0; y < 144; y++) {
                if (CheckCollisionPointRec(GetMousePosition(), tiles[x][y].hitBox) && tiles[x][y].type == 1) {
                    tiles[x][y].type = 0;
                    totalSnowflakes--;
                }
            }
        }
    }
    if (IsKeyPressed(KEY_R)) {
        for (int x = 0; x < 256; x++) {
            for (int y = 0; y < 144; y++) {
                tiles[x][y].type = 0;
                totalSnowflakes = 0;
            }
        }
    }
}

void moveSnow() {
    for (int x = 0; x < 256; x++) {
        for (int y = 143; y >= 0; y--) {
            if (tiles[x][y].type == 1 && y < 143) {
                if (tiles[x][y + 1].type == 0) {
                    tiles[x][y].type = 0;
                    tiles[x][y + 1].type = 1;
                    tiles[x][y + 1].snowColor = tiles[x][y].snowColor;
                } else if (tiles[x][y + 1].type == 1 && tiles[x - 1][y + 1].type == 0 && x > 0) {
                    tiles[x][y].type = 0;
                    tiles[x - 1][y + 1].type = 1;
                    tiles[x - 1][y + 1].snowColor = tiles[x][y].snowColor;
                } else if (tiles[x][y + 1].type == 1 && tiles[x + 1][y + 1].type == 0&& x < 255) {
                    tiles[x][y].type = 0;
                    tiles[x + 1][y + 1].type = 1;
                    tiles[x + 1][y + 1].snowColor = tiles[x][y].snowColor;
                }
            }
        }
    }
}

void spawnSnow() {
    int randomIndex = GetRandomValue(0, 255);
    totalSnowflakes++;

    tiles[randomIndex][0].type = 1;
    tiles[randomIndex][0].snowColor = snowColors[GetRandomValue(0, 2)];
}

int main() {
    InitWindow(1280, 720, "Falling Snow");

    SetTargetFPS(240);

    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 144; y++) {
            tiles[x][y].hitBox.x = x * tileSize;
            tiles[x][y].hitBox.y = y * tileSize;
            tiles[x][y].hitBox.width = tileSize;
            tiles[x][y].hitBox.height = tileSize;
        }
    }

    while (!WindowShouldClose())
    {
        input();
        moveSnow();
        spawnSnow();

        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        for (int x = 0; x < 256; x++) {
            for (int y = 0; y < 144; y++) {
                if (tiles[x][y].type == 1) {
                    DrawRectangleRec(tiles[x][y].hitBox, tiles[x][y].snowColor);
                }
            }
        }
        DrawText(TextFormat("Number of Snowflakes: %d", totalSnowflakes), 0, 0, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
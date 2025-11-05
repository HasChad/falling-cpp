#include <raylib.h>
#include <raymath.h>
#include <sys/types.h>

enum Cell { None, Sand, Stone };

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 60;

int main() {
    InitWindow(cellSize * gridWidth, cellSize * gridHeight, "Falling-Cpp");
    SetTargetFPS(60);

    Cell grid[gridWidth][gridHeight] = { None };

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition() / cellSize;

        for (int y = gridHeight - 1; y >= 0; y--) {
            for (int x = 0; x < gridWidth; x++) {
                if (y < gridHeight - 1) {
                    if (grid[x][y] == Cell::Sand) {
                        if (grid[x][y + 1] == Cell::None) {
                            grid[x][y] = Cell::None;
                            grid[x][y + 1] = Cell::Sand;
                        } else if (x != 0 && grid[x - 1][y + 1] == Cell::None) {
                            grid[x][y] = Cell::None;
                            grid[x - 1][y + 1] = Cell::Sand;
                        } else if (x != gridWidth - 1 && grid[x + 1][y + 1] == Cell::None) {
                            grid[x][y] = Cell::None;
                            grid[x + 1][y + 1] = Cell::Sand;
                        }
                    }
                }
            }
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            grid[(int)mousePos.x][(int)mousePos.y] = Cell::Sand;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            grid[(int)mousePos.x][(int)mousePos.y] = Cell::Stone;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            grid[(int)mousePos.x][(int)mousePos.y] = Cell::None;
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < gridHeight; y++) {
            for (int x = 0; x < gridWidth; x++) {
                // DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, WHITE);

                if (grid[x][y] == Cell::Sand)
                    DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, YELLOW);
                if (grid[x][y] == Cell::Stone)
                    DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, GRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
}

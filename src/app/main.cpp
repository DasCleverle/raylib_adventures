#include <raylib.h>

int main() {
    InitWindow(800, 600, "Hello from raylib");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);
        DrawText("Hello from raylib", 10, 10, 20, BEIGE);

        EndDrawing();
    }

    CloseWindow();

}

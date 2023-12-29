#include "raylib.h"
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 20

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Array Visualization");

    int array[MAX_ARRAY_SIZE] = {0}; // Initialize array with zeros
    int arraySize = 10; // Initial size of the array
    int currentArrayIndex = 0; // Index to keep track of the current array element to be filled

    // Input box properties
    Rectangle inputBox = { 10, 10, 50, 30 };
    char inputValue[3] = ""; // Initialize input value buffer

    // Button properties
    Rectangle generateButton = { 70, 10, 120, 30 };
    bool generateButtonPressed = false;

    Rectangle randomButton = { 200, 10, 120, 30 };
    bool randomButtonPressed = false;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        generateButtonPressed = false;
        randomButtonPressed = false;

        // Check for numeric key input
        for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
            if (IsKeyPressed(key)) {
                // If the first digit is '0', allow overwriting it with the new key
                if (strlen(inputValue) == 2 && inputValue[0] == '0') {
                    inputValue[0] = inputValue[1];
                    inputValue[1] = '0' + (key - KEY_ZERO);
                } else {
                    // Append the pressed key to the inputValue
                    char keyChar = '0' + (key - KEY_ZERO);
                    if (strlen(inputValue) < 2) {
                        // Allow appending the digit if length is less than 2
                        inputValue[strlen(inputValue)] = keyChar;
                    }
                }
            }
        }

        // Check for Enter key pressed
        if (IsKeyPressed(KEY_ENTER)) {
            // Generate button pressed
            if (strlen(inputValue) > 0 && currentArrayIndex < arraySize) {
                int value = atoi(inputValue);
                array[currentArrayIndex] = value;
                currentArrayIndex++;
            }
            // Clear inputValue for the next input
            inputValue[0] = '\0';
        }

        // Check for Random button pressed
        if (CheckCollisionPointRec(GetMousePosition(), randomButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Generate random values for the array
            for (int i = 0; i < arraySize; i++) {
                array[i] = GetRandomValue(1, 99);
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw input box
        DrawRectangleRec(inputBox, LIGHTGRAY);
        DrawRectangleLines(inputBox.x, inputBox.y, inputBox.width, inputBox.height, BLACK);
        DrawText(inputValue, inputBox.x + 10, inputBox.y + 10, 20, MAROON);

        // Draw generate button
        DrawRectangleRec(generateButton, generateButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Remplire", generateButton.x + 10, generateButton.y + 5, 20, DARKGRAY);

        // Draw random button
        DrawRectangleRec(randomButton, randomButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Random", randomButton.x + 10, randomButton.y + 5, 20, DARKGRAY);

        // Draw array table
        DrawText("Array Elements:", 10, 70, 20, DARKGRAY);
        for (int i = 0; i < arraySize; i++) {
            DrawRectangleLines(10 + i * 40, 100, 40, 30, BLACK);
            DrawText(TextFormat("%02d", array[i]), 20 + i * 40, 110, 20, MAROON);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();

    return 0;
}





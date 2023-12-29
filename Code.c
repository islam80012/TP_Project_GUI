#include "raylib.h"
#include <stdio.h>
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
    Rectangle inputBox1 = { 10, 10, 50, 30 };
    Rectangle inputBox2 = { 70, 10, 50, 30 };
    char inputValue1[2] = ""; // Initialize input value buffer for the first digit
    char inputValue2[2] = ""; // Initialize input value buffer for the second digit

    // Button properties
    Rectangle generateButton = { 130, 10, 120, 30 };
    bool generateButtonPressed = false;

    Rectangle randomButton = { 260, 10, 120, 30 };
    bool randomButtonPressed = false;

    //Rectangle searchButton = { 390, 10, 120, 30 };
    //bool searchButtonPressed = false;

    Rectangle changeColorButton = { 520, 10, 180, 30 };
    bool changeColorButtonPressed = false;

    Color backgroundColor = RAYWHITE;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        generateButtonPressed = false;
        randomButtonPressed = false;
       // searchButtonPressed = false;
        changeColorButtonPressed = false;

        // Check for numeric key input
        for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
            if (IsKeyPressed(key)) {
                // Check if the first digit is empty, if yes, add the key to it
                if (strlen(inputValue1) == 0) {
                    inputValue1[0] = '0' + (key - KEY_ZERO);
                }
                // If the first digit is already entered, add the key to the second digit
                else if (strlen(inputValue2) == 0) {
                    inputValue2[0] = '0' + (key - KEY_ZERO);
                }
            }
        }

        // Check for Enter key pressed
        if (IsKeyPressed(KEY_ENTER)) {
            // Remplir button pressed
            if (strlen(inputValue1) > 0 && strlen(inputValue2) > 0 && currentArrayIndex < arraySize) {
                int value = atoi(inputValue1) * 10 + atoi(inputValue2);
                array[currentArrayIndex] = value;
                currentArrayIndex++;
            }
            // Clear inputValues for the next input
            inputValue1[0] = '\0';
            inputValue2[0] = '\0';
        }

        // Check for Random button pressed
        if (CheckCollisionPointRec(GetMousePosition(), randomButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Generate random values for the array
            for (int i = 0; i < arraySize; i++) {
                array[i] = GetRandomValue(1, 99);
            }
        }

        // Check for Search button pressed
     /*  if (CheckCollisionPointRec(GetMousePosition(), searchButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Search button pressed
            int searchValue = atoi(inputValue1) * 10 + atoi(inputValue2);
            bool found = false;
            for (int i = 0; i < arraySize; i++) {
                if (array[i] == searchValue) {
                    // Value found
                    found = true;
                    break;
                }
            }
            // Handle the result (for now, print to console)
            if (found) {
                printf("Value %d found in the array.\n", searchValue);
            } else {
                printf("Value %d not found in the array.\n", searchValue);
            } 
        } */

        // Check for Change Color button pressed
        if (CheckCollisionPointRec(GetMousePosition(), changeColorButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Change the background color to a random color
            backgroundColor = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(backgroundColor);

        // Draw input boxes
        DrawRectangleRec(inputBox1, LIGHTGRAY);
        DrawRectangleLines(inputBox1.x, inputBox1.y, inputBox1.width, inputBox1.height, BLACK);
        DrawText(inputValue1, inputBox1.x + 10, inputBox1.y + 10, 20, MAROON);

        DrawRectangleRec(inputBox2, LIGHTGRAY);
        DrawRectangleLines(inputBox2.x, inputBox2.y, inputBox2.width, inputBox2.height, BLACK);
        DrawText(inputValue2, inputBox2.x + 10, inputBox2.y + 10, 20, MAROON);

        // Draw Remplir button
        DrawRectangleRec(generateButton, generateButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Remplir", generateButton.x + 10, generateButton.y + 5, 20, DARKGRAY);

        // Draw Random button
        DrawRectangleRec(randomButton, randomButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Random", randomButton.x + 10, randomButton.y + 5, 20, DARKGRAY);

        // Draw Search button
      //  DrawRectangleRec(searchButton, searchButtonPressed ? GRAY : LIGHTGRAY);
       // DrawText("Search", searchButton.x + 10, searchButton.y + 5, 20, DARKGRAY);

        // Draw Change Color button
        DrawRectangleRec(changeColorButton, changeColorButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Change Color", changeColorButton.x + 10, changeColorButton.y + 5, 16, DARKGRAY);

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

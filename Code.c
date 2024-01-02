#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 20

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Array Visualization");

    int array[MAX_ARRAY_SIZE] = {0}; // Initialize array with zeros
    int arraySize = 10; // Initial size of the array
    int currentArrayIndex = 0; // Index to keep track of the current array element to be filled

    // Input box properties
    Rectangle inputBox1 = {10, 10, 50, 30};
    Rectangle inputBox2 = {70, 10, 50, 30};
    char inputValue1[2] = ""; // Initialize input value buffer for the first digit
    char inputValue2[2] = ""; // Initialize input value buffer for the second digit

    // Button properties
<<<<<<< HEAD
    Rectangle searchButton = {390, 10, 120, 30};
    bool searchButtonPressed = false;
=======

    Rectangle searchButton = { 390, 10, 120, 30 };
    bool searchButtonPressed = false;

    Rectangle deleteButton = { 130, 10, 120, 30 };
    bool deleteButtonPressed = false;
>>>>>>> 1d16c3305b8e35a635cb9b6a51a0ab988d23b5a2

    Rectangle deleteButton = {130, 10, 120, 30};
    bool deleteButtonPressed = false;

    Rectangle randomButton = {260, 10, 120, 30};
    bool randomButtonPressed = false;

<<<<<<< HEAD
    Rectangle changeColorButton = {520, 10, 180, 30};
=======
    Rectangle changeColorButton = { 520, 10, 180, 30 };
>>>>>>> 1d16c3305b8e35a635cb9b6a51a0ab988d23b5a2
    bool changeColorButtonPressed = false;
    // Text box
    Rectangle searchResultBox = {260, 340, 300, 60};
    bool showSearchResultBox = false;
    Rectangle notFoundBox = {260, 340, 300, 60};
    bool showNotFoundBox = false;

    Color backgroundColor = RAYWHITE;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // À placer avant la boucle principale
    bool deleteVisualized = false;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        deleteButtonPressed = false;
        randomButtonPressed = false;
        searchButtonPressed = false;
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
        // Check for delete button pressed
        if (CheckCollisionPointRec(GetMousePosition(), deleteButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
<<<<<<< HEAD
            deleteButtonPressed = true;
            // Check if there's a number selected for deletion
            if (strlen(inputValue1) > 0 && strlen(inputValue2) > 0) {
                int deleteIndex = atoi(inputValue1) * 10 + atoi(inputValue2);
                // Check if the delete index is within the array bounds
                if (deleteIndex >= 0 && deleteIndex < arraySize) {
                    // Move all elements after the selected index one position to the left
                    for (int i = deleteIndex; i < arraySize - 1; i++) {
                        array[i] = array[i + 1];
                    }

                    // Clear the last element
                    array[arraySize - 1] = 0;

                    // Update the currentArrayIndex to reflect the new state
                    currentArrayIndex = (deleteIndex > 0) ? deleteIndex - 1 : 0;

                    // Indicate that deletion has been visualized
                    deleteVisualized = true;
                } else {
                    // Display a message indicating deletion is impossible
                    showNotFoundBox = true;
                }
            }

=======
        deleteButtonPressed = true;
        // Check if there's a number selected for deletion
        if (currentArrayIndex > 0) {
        // Move all elements after the selected index one position to the left
            for (int i = currentArrayIndex; i < arraySize - 1; i++) {
                array[i] = array[i + 1];
            }
        // Clear the last element
            array[arraySize - 1] = 0;

        // Update the currentArrayIndex to reflect the new state
            currentArrayIndex = (currentArrayIndex > 0) ? currentArrayIndex - 1 : 0;
        }
>>>>>>> 1d16c3305b8e35a635cb9b6a51a0ab988d23b5a2
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
<<<<<<< HEAD

            // Clear inputValues for the next input
            inputValue1[0] = '\0';
            inputValue2[0] = '\0';
        }
        // Check for Search button pressed
        if (CheckCollisionPointRec(GetMousePosition(), searchButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            searchButtonPressed = true;
            showSearchResultBox = false;
            showNotFoundBox = true;
            // Search for the value in the array
            if (strlen(inputValue1) > 0 && strlen(inputValue2) > 0) {
                int searchValue = atoi(inputValue1) * 10 + atoi(inputValue2);
                for (int i = 0; i < arraySize; i++) {
                    if (array[i] == searchValue) {
                        // Value found
                        showNotFoundBox = false;  // Reset to false if found
                        showSearchResultBox = true;
                        break;
                    }
                }
            }
            // Clear inputValues for the next input
            inputValue1[0] = '\0';
            inputValue2[0] = '\0';
        }
=======
        }
        // Check for Search button pressed
        if (CheckCollisionPointRec(GetMousePosition(), searchButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        searchButtonPressed = true;
        showSearchResultBox = false;  
        showNotFoundBox = true;  
        // Search for the value in the array
        if (strlen(inputValue1) > 0 && strlen(inputValue2) > 0) {
        int searchValue = atoi(inputValue1) * 10 + atoi(inputValue2);
        for (int i = 0; i < arraySize; i++) {
                if (array[i] == searchValue) {
                // Value found
                    showNotFoundBox = false;  // Reset to false if found
                    showSearchResultBox = true;
                    break;
                }
            }
        }
    // Clear inputValues for the next input
        inputValue1[0] = '\0';
        inputValue2[0] = '\0';
        }

>>>>>>> 1d16c3305b8e35a635cb9b6a51a0ab988d23b5a2

        // Check for Change Color button pressed
        if (CheckCollisionPointRec(GetMousePosition(), changeColorButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Change the background color to a random color
            backgroundColor = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};

            // Clear inputValues for the next input
            inputValue1[0] = '\0';
            inputValue2[0] = '\0';
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

        // Draw delete button
        DrawRectangleRec(deleteButton, deleteButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Delete", deleteButton.x + 10, deleteButton.y + 5, 20, DARKGRAY);

        // Draw Random button
        DrawRectangleRec(randomButton, randomButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Random", randomButton.x + 10, randomButton.y + 5, 20, DARKGRAY);

        // Draw Search button
        DrawRectangleRec(searchButton, searchButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Search", searchButton.x + 10, searchButton.y + 5, 20, DARKGRAY);

        // Draw search result box
        if (showSearchResultBox) {
            DrawRectangleRec(searchResultBox, LIGHTGRAY);
            DrawText("Search Result: found", searchResultBox.x + 10, searchResultBox.y + 5, 20, DARKGRAY);
<<<<<<< HEAD
        }
=======
        } 
>>>>>>> 1d16c3305b8e35a635cb9b6a51a0ab988d23b5a2
        // Draw "Not Found" box
        if (showNotFoundBox) {
            DrawRectangleRec(notFoundBox, LIGHTGRAY);
            DrawText("Search Result: Not Found", notFoundBox.x + 10, notFoundBox.y + 5, 20, DARKGRAY);
<<<<<<< HEAD
        }
=======
        }      
>>>>>>> 1d16c3305b8e35a635cb9b6a51a0ab988d23b5a2
        // Draw Change Color button
        DrawRectangleRec(changeColorButton, changeColorButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Change Color", changeColorButton.x + 10, changeColorButton.y + 5, 16, DARKGRAY);

        // Draw array table
        DrawText("Array Elements:", 10, 70, 20, DARKGRAY);
        for (int i = 0; i < arraySize; i++) {
            // Highlight the element being deleted
            if (deleteVisualized && i == currentArrayIndex) {
                DrawRectangle(10 + i * 40, 100, 40, 30, GRAY);
            } else {
                DrawRectangleLines(10 + i * 40, 100, 40, 30, BLACK);
            }
            DrawText(TextFormat("%02d", array[i]), 20 + i * 40, 110, 20, MAROON);
        }
<<<<<<< HEAD
        deleteVisualized = false; // Reset deleteVisualized after visualization

=======
>>>>>>> 1d16c3305b8e35a635cb9b6a51a0ab988d23b5a2
        EndDrawing();
    }
    // De-Initialization
    CloseWindow();
    return 0;
}

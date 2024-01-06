#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_ARRAY_SIZE 20
#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 30

void ManualFillArray(int array[], int *arraySize, int *currentArrayIndex, char inputValue1[], char inputValue2[], bool enterKeyPressed);
void SelectionSort(int array[], int arraySize, int *i, int *j, int *currentMinIndex, bool *sortingInProgress);

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Input box properties
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
    Rectangle searchButton = {390, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
    bool searchButtonPressed = false;

    Rectangle deleteButton = {130, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
    bool deleteButtonPressed = false;

    Rectangle randomButton = {260, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
    bool randomButtonPressed = false;

    Rectangle changeColorButton = {520, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
    bool changeColorButtonPressed = false;

    Rectangle addButton = {650, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
    bool addButtonPressed = false;

    Rectangle selectionSortButton = {650, 50, BUTTON_WIDTH, BUTTON_HEIGHT};
    bool sortingInProgress = false;
    int currentMinIndex = 0;
    int i = 0;
    int j = 0;
    bool selectionSortButtonPressed = false;
    double sortingStartTime = 0.0;


    // Text box
    bool showSearchResultBox = false;
    double searchResultBoxDisplayTime = 0.0;
    Rectangle searchResultBox = {260, 340, 300, 60};

    Rectangle notFoundBox = {260, 340, 300, 60};
     Rectangle FoundBox = {260, 340, 300, 60};
    bool showNotFoundBox = false;
    bool showFoundBox = false;

    Color backgroundColor = RAYWHITE;

    double deleteAnimationStartTime = 0.0;
    bool deleteVisualized = false;
    int deleteIndex = 0 ;

    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        deleteButtonPressed = false;
        randomButtonPressed = false;
        changeColorButtonPressed = false;

        // Check for numeric key input and space key
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

        // Check for Enter key
        if (IsKeyPressed(KEY_ENTER)) {
            // Perform the manual fill array function when Enter key is pressed
            ManualFillArray(array, &arraySize, &currentArrayIndex, inputValue1, inputValue2, true);
        }

    // Check for delete button pressed
        if (CheckCollisionPointRec(GetMousePosition(), deleteButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Check if there's a number selected for deletion
            if (strlen(inputValue1) > 0 && strlen(inputValue2) > 0) {
                int deleteIndex = atoi(inputValue1) * 10 + atoi(inputValue2);
                
                // Check if the delete index is within the array bounds
                if (deleteIndex >= 0 && deleteIndex < arraySize) {
                    // Shift elements in the array to delete the selected index
                    for (int i = deleteIndex; i < arraySize - 1; i++) {
                        array[i] = array[i + 1];
                    }
                    array[arraySize - 1] = 0;
                    arraySize--;

                    // Clear inputValues for the next input
                    inputValue1[0] = '\0';
                    inputValue2[0] = '\0';
                } else {
                    // Display a message indicating deletion is impossible
                    showNotFoundBox = true;
                }
            }
        }

    // Animation de suppression avec permutation visuelle
    if (deleteVisualized) {
        // Calculate elapsed time since the start of deletion animation
        float elapsedTime = (float)(GetTime() - deleteAnimationStartTime);
        // Animation duration
        float animationDuration = 0.5f;

        if (elapsedTime < animationDuration) {
            // Draw the elements with deletion animation
            BeginDrawing();
            ClearBackground(backgroundColor); // Clear the background before redrawing the frame

            for (int i = 0; i < arraySize; i++) {
                // Skip the element being deleted
                if (i == deleteIndex) continue;

                // Calculate current and target positions for each element
                float currentX = 10 + i * 40;
                float currentY = 100;
                float targetX = currentX - 40;
                float targetY = currentY;

                // Interpolate the position based on elapsed time
                float t = elapsedTime / animationDuration;
                float newX = Lerp(currentX, targetX, t);
                float newY = Lerp(currentY, targetY, t);

                // Draw the element at the new position
                DrawRectangleLines(newX, newY, 40, 30, BLACK);
                DrawText(TextFormat("%02d", array[i]), newX + 10, newY + 10, 20, MAROON);
            }

            EndDrawing();
        } else {
            // End of deletion animation
            // Shift elements in the array and update the array size
            for (int i = deleteIndex; i < arraySize - 1; i++) {
                array[i] = array[i + 1];
            }
            array[arraySize - 1] = 0;
            arraySize--;

            // Reset variables related to deletion visualization
            deleteVisualized = false;
            deleteIndex = 0;
        }
    }
     
        // Check for Random button pressed
        if (CheckCollisionPointRec(GetMousePosition(), randomButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Generate random values for the array
            for (int i = 0; i < arraySize; i++) {
                array[i] = GetRandomValue(1, 99);
            }

            // Clear inputValues for the next input
            inputValue1[0] = '\0';
            inputValue2[0] = '\0';
        }

      // Check for Search button pressed
        if (CheckCollisionPointRec(GetMousePosition(), searchButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            searchButtonPressed = true;
            showSearchResultBox = false;
            showNotFoundBox = false; // Ajout pour réinitialiser showNotFoundBox
            showFoundBox = false; // Ajout pour réinitialiser showFoundBox

            // Search for the value in the array
            if (strlen(inputValue1) > 0 && strlen(inputValue2) > 0) {
                int searchValue = atoi(inputValue1) * 10 + atoi(inputValue2);
                bool elementFound = false;

                for (int i = 0; i < arraySize; i++) {
                    if (array[i] == searchValue) {
                        // Value found
                        elementFound = true;
                        break;
                    }
                }

        // Set the flag to display the search result box
        showSearchResultBox = true;

        // Record the display time
        searchResultBoxDisplayTime = GetTime();

        // Update the box content based on the search result
        if (elementFound) {
            showFoundBox = true; // Mettez showFoundBox à true si l'élément est trouvé
            DrawText("Search Result: Found", FoundBox.x + 10, FoundBox.y + 5, 20, DARKGRAY);
        } else {
            showNotFoundBox = true; // Mettez showNotFoundBox à true si l'élément n'est pas trouvé
            DrawText("Search Result: Not Found", notFoundBox.x + 10, notFoundBox.y + 5, 20, DARKGRAY);
        }
    }

        // Clear inputValues for the next input
            inputValue1[0] = '\0';
            inputValue2[0] = '\0';
        }


        // Check for Change Color button pressed
        if (CheckCollisionPointRec(GetMousePosition(), changeColorButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Change the background color to a random color
            backgroundColor = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};

            // Clear inputValues for the next input
            inputValue1[0] = '\0';
            inputValue2[0] = '\0';
        }

        // Check for Add button pressed
        if (CheckCollisionPointRec(GetMousePosition(), addButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            addButtonPressed = true;

            // Convert the text from the text field to an integer
            int newValue = atoi(inputValue1) * 10 + atoi(inputValue2);

            // Ensure the index is valid
            if (arraySize < MAX_ARRAY_SIZE) {
                array[arraySize] = newValue;
                arraySize++;
            }

            // Reset the text field after adding
            inputValue1[0] = '\0';
            inputValue2[0] = '\0';
        }

        // Check for sorting start
        if (!sortingInProgress && IsKeyPressed(KEY_S)) {
            sortingInProgress = true;
            currentMinIndex = 0;
            i = 0;
            j = i + 1;
        }
       // Check for Selection Sort button pressed
        if (CheckCollisionPointRec(GetMousePosition(), selectionSortButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectionSortButtonPressed = true;
            sortingInProgress = true;
            currentMinIndex = 0;
            i = 0;
            j = i + 1;
            sortingStartTime = GetTime();
        }
        // Sorting visualization
        SelectionSort(array, arraySize, &i, &j, &currentMinIndex, &sortingInProgress);

    // Sorting visualization
   // Sorting visualization
if (sortingInProgress) {
    if (i < arraySize) {
        // Find the minimum element in the unsorted part of the array
        if (j < arraySize) {
            if (array[j] < array[currentMinIndex]) {
                currentMinIndex = j;
            }
            j++;
        } else {
            // Swap the found minimum element with the first element
            int temp = array[i];
            array[i] = array[currentMinIndex];
            array[currentMinIndex] = temp;

            // Increment i to move to the next unsorted element
            i++;
            currentMinIndex = i;
            j = i + 1;
        }
    } else {
        // Sorting is complete
        sortingInProgress = false;
    }
}

// Check if the Selection Sort button was pressed
if (selectionSortButtonPressed) {
    // Perform sorting
    SelectionSort(array, arraySize, &i, &j, &currentMinIndex, &sortingInProgress);
    selectionSortButtonPressed = false;
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

        // Check if the element is found in the array
        int searchValue = atoi(inputValue1) * 10 + atoi(inputValue2);
        bool elementFound = false;

        for (int i = 0; i < arraySize; i++) {
            if (array[i] == searchValue) {
                elementFound = true;
                break;
            }
        }

        if (elementFound) {
            DrawText("Search Result: found", searchResultBox.x + 10, searchResultBox.y + 5, 20, DARKGRAY);
        } else {
            DrawText("Search Result: Not Found", searchResultBox.x + 10, searchResultBox.y + 5, 20, DARKGRAY);
        }

        // Check if 3 seconds have passed since the last time the box was displayed
        if (GetTime() - searchResultBoxDisplayTime > 3.0) {
            showSearchResultBox = false; // Hide the box
        }
    }
        // Draw "Not Found" box
        if (showNotFoundBox) {
            DrawRectangleRec(notFoundBox, LIGHTGRAY);
            DrawText("Search Result: Not Found", notFoundBox.x + 10, notFoundBox.y + 5, 20, DARKGRAY);
        }
        // Draw "Found" box
        if (showFoundBox) {
            DrawRectangleRec(FoundBox, LIGHTGRAY);
            DrawText("Search Result: Found", FoundBox.x + 10, FoundBox.y + 5, 20, DARKGRAY);
        }
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

    // Draw a rectangle around the element being deleted
    if (CheckCollisionPointRec(GetMousePosition(), deleteButton) && i == atoi(inputValue1) * 10 + atoi(inputValue2)) {
        DrawRectangle(10 + i * 40, 100, 40, 30, RED);
    } else {
        DrawRectangleLines(10 + i * 40, 100, 40, 30, BLACK);
    }

    DrawText(TextFormat("%02d", array[i]), 20 + i * 40, 110, 20, MAROON);
}

// Highlight the element being deleted
if (deleteVisualized && i == deleteIndex) {
    DrawRectangle(10 + i * 40, 100, 40, 30, GRAY);
} else {
    DrawRectangleLines(10 + i * 40, 100, 40, 30, BLACK);
}

// Draw array table for sorting visualization
for (int k = 0; k < arraySize; k++) {
    // Highlight the elements being compared or swapped
    if (k == i || k == currentMinIndex) {
        DrawRectangle(10 + k * 40, 100, 40, 30, sortingInProgress ? SKYBLUE : GRAY);
    } else {
        DrawRectangleLines(10 + k * 40, 100, 40, 30, BLACK);
    }

    DrawText(TextFormat("%02d", array[k]), 20 + k * 40, 110, 20, MAROON);
}



        // Draw Add button
        DrawRectangleRec(addButton, addButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Add", addButton.x + 10, addButton.y + 5, 20, DARKGRAY);

        deleteVisualized = false; // Reset deleteVisualized after visualization
        EndDrawing();

         // Draw Selection Sort button
        DrawRectangleRec(selectionSortButton, selectionSortButtonPressed ? GRAY : LIGHTGRAY);
        DrawText("Selection Sort", selectionSortButton.x + 10, selectionSortButton.y + 5, 16, DARKGRAY);

    }

    

    // De-Initialization
    CloseWindow();
    return 0;
}

void ManualFillArray(int array[], int *arraySize, int *currentArrayIndex, char inputValue1[], char inputValue2[], bool enterKeyPressed) {
    // Convert the text from the text field to an integer
    int newValue = atoi(inputValue1) * 10 + atoi(inputValue2);

    // Ensure the index is valid
    if (*currentArrayIndex >= 0 && *currentArrayIndex < *arraySize) {
        array[*currentArrayIndex] = newValue;
    }

    // Reset the text field after updating
    inputValue1[0] = '\0';
    inputValue2[0] = '\0';

    // Increment the index only if the Enter key was pressed
    if (enterKeyPressed) {
        *currentArrayIndex = (*currentArrayIndex + 1) % MAX_ARRAY_SIZE;
    }
}
void SelectionSort(int array[], int arraySize, int *i, int *j, int *currentMinIndex, bool *sortingInProgress) {
    if (*sortingInProgress) {
        if (*i < arraySize) {
            if (*j < arraySize) {
                if (array[*j] < array[*currentMinIndex]) {
                    *currentMinIndex = *j;
                }
                (*j)++;
            } else {
                int temp = array[*i];
                array[*i] = array[*currentMinIndex];
                array[*currentMinIndex] = temp;

                (*i)++;
                *currentMinIndex = *i;
                *j = *i + 1;
            }
        } else {
            *sortingInProgress = false;
        }
    }
}
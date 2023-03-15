#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printResult(int** arr);
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
<<<<<<< Updated upstream
void initilizeMatrix(int** arr);
=======
void upCase(char *word);
int concatenateDigits(int num1, int num2);
bool depthFirstSearch(char** matrix, char* word, int row, int col, int index, bool** visited, int** path);
void printPath(int **path);
>>>>>>> Stashed changes
int bSize;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for (int i=0; i<bSize; i++) {
        for (int j=0; j<bSize; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

<<<<<<< Updated upstream
}

void printResult(int** arr) {
    for (int i=0; i<bSize; i++) {
        printf("\n");
        for (int j=0; j<bSize; j++) {
            printf("%d ", arr[i][j]);
=======
    upCase(word);
    //initialize a bool matrix to check if we visited a cell or not
    bool **visited = (bool**)malloc(bSize * sizeof(bool*));
    for(int i = 0; i < bSize; i++){
        visited[i] = (bool*)malloc(bSize * sizeof(bool));
        for (int j=0; j<bSize; j++) {
            visited[i][j] = false;
        }
    }
    
    //initialize a matrix to print out the path of the word
    int **path = (int**)malloc(bSize * sizeof(int*));
    for(int i = 0; i < bSize; i++){
        path[i] = (int*)malloc(bSize * sizeof(int));
        for (int j=0; j<bSize; j++) {
            path[i][j] = false;
        }
    }

    //start searching from every cell in the matrix
    for (int row = 0; row < bSize; row++) {
        for (int col = 0; col < bSize; col++) {
            if (depthFirstSearch(arr, word, row, col, 0, visited, path)) {
                printPath(path);
                return;
            }
        }
    }
    
    printf("\nWord not found!");
    return;

}

bool depthFirstSearch(char** matrix, char* word, int row, int col, int index, bool** visited, int** path)
{
    //check if we found the entire word. if found, exit function with success
    if (index == strlen(word)) {
        return true;
    }
    
    //check if we are out of bounds (attempting to access elements outside the array can result in crashes and weird behavior)
    if (row < 0 || row >= bSize || col < 0 || col >= bSize) {
        return false;
    }
    
    //check if the current cell in the matrix matches the letter(word[index]) we are searching for
    if (matrix[row][col] != word[index]) {
        return false;
    }
    
    //if we get to this point, then cell element matches our letter. we then mark the current cell as visited and update the
    //path value to the corresponding
    visited[row][col] = true;
    path[row][col] = concatenateDigits(index + 1, path[row][col]);
    
    //we now will recursively search in all directions, this is why we picked depth first search
    bool found = depthFirstSearch(matrix, word, row-1, col, index+1, visited, path) ||   // Up
                 depthFirstSearch(matrix, word, row+1, col, index+1, visited, path) ||   // Down
                 depthFirstSearch(matrix, word, row, col-1, index+1, visited, path) ||   // Left
                 depthFirstSearch(matrix, word, row, col+1, index+1, visited, path) ||   // Right
                 depthFirstSearch(matrix, word, row-1, col-1, index+1, visited, path) || // Up-Left
                 depthFirstSearch(matrix, word, row-1, col+1, index+1, visited, path) || // Up-Right
                 depthFirstSearch(matrix, word, row+1, col-1, index+1, visited, path) || // Down-Left
                 depthFirstSearch(matrix, word, row+1, col+1, index+1, visited, path);   // Down-Right
    
    // Unmark the current cell before returning
    visited[row][col] = false; //this is for subsequent calls to the function. I can remove it safely if I don't plan on making subsequent calls
                               //However, it is generally good practice to reset the visited flag for each cell after the recursive call is complete
    // If the entire word is not found, reset the path array
    if (found == false) {
        path[row][col] = 0;
    }
    
    return found;
}

void printPath(int** path) {
    printf("\nWord found!");
    printf("\nPrinting the search path:\n");
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%-8d", path[i][j]);
>>>>>>> Stashed changes
        }
        printf("\n");
    }
}

<<<<<<< Updated upstream
void initilizeMatrix(int** arr) {
    for (int i=0; i<bSize; i++) {
        for (int j=0; j<bSize; j++) {
            arr[i][j] = 0;
        }
    }
=======
void upCase(char *word) {
    for (int i=0; i<strlen(word); i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] -= 32;
        }
    }
}

int concatenateDigits(int num1, int num2) {
    int digits = 0, temp = num2;

    //find the number of digits in num2
    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    //multiple num1 by 10^(digits), this will shift num1 to the left by that number of digits. then simply add num2
    int path = num1 * pow(10, digits) + num2;

    return path;
>>>>>>> Stashed changes
}
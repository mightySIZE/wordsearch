#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
bool depthFirstSearch(char** matrix, char* word, int row, int col, int index, int** path);
void printPath(int **path);
void upCase(char *word);
int concatenateDigits(int num1, int num2);
int bSize;
bool check;

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
    for (int i=0; i<bSize; i++) {
        for (int j=0; j<bSize; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}

void searchPuzzle(char** arr, char* word) {
    //capitilize all letters in the word
    upCase(word);

    check = false;

    //initialize a matrix to print out the path of the word
    int **path = (int**)malloc(bSize * sizeof(int*));
    for(int row = 0; row < bSize; row++) {
        path[row] = (int*)malloc(bSize * sizeof(int));
        for (int col = 0; col < bSize; col++) {
            path[row][col] = 0;
        }
    }

    //start searching from every cell in the matrix
    for (int row = 0; row < bSize; row++) {
        for (int col = 0; col < bSize; col++) {
            //check if the letter in the cell matches the first letter of the word with depthFirstSearch() function
            //if the letter matches. then we will recursively search in all directions for the rest of the word with depthFirstSearch() function
            if (depthFirstSearch(arr, word, row, col, 0, path)) {
                //if the word is found, print the path and exit the function
                printPath(path);
                return;
            }
        }
    }
    
    printf("\nWord not found!");
    return;
}

bool depthFirstSearch(char** matrix, char* word, int row, int col, int index, int** path) {
    //check if we found the entire word, initialize check to true
    if (index == strlen(word)) {
        check = true;
        return true;
    }
    
    //check if we are out of bounds (attempting to access elements outside the array can result in crashes and weird behavior)
    if (row < 0 || row > bSize || col < 0 || col > bSize) {
        return false;
    }
    
    //check if the current cell in the matrix matches the letter(word[index]) we are searching for
    if (matrix[row][col] != word[index]) {
        return false;
    }
    
    //we now will recursively search in all directions, this is why we picked depth first search
    bool found = depthFirstSearch(matrix, word, row-1, col, index+1, path) ||   // search Up
                 depthFirstSearch(matrix, word, row+1, col, index+1, path) ||   // search Down
                 depthFirstSearch(matrix, word, row, col-1, index+1, path) ||   // search Left
                 depthFirstSearch(matrix, word, row, col+1, index+1, path) ||   // search Right
                 depthFirstSearch(matrix, word, row-1, col-1, index+1, path) || // search Up-Left
                 depthFirstSearch(matrix, word, row-1, col+1, index+1, path) || // search Up-Right
                 depthFirstSearch(matrix, word, row+1, col-1, index+1, path) || // search Down-Left
                 depthFirstSearch(matrix, word, row+1, col+1, index+1, path);   // search Down-Right
    
    //if the entire word is found, update the path matrix with the index of the current letter in the word
    if (check == true) {
        path[row][col] = concatenateDigits(path[row][col], index + 1);
    }

    return found;
}

void printPath(int** path) {
    printf("\nWord found!");
    printf("\nPrinting the search path:\n");
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%-8d", path[i][j]);
        }
        printf("\n");
    }
}

void upCase(char *word) {
    //iterate through the word and convert all lowercase letters to uppercase
    for (int i=0; i<strlen(word); i++) {
        //check if the current character is a lowercase letter
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
}
/* 
given this depthFirstSearch function:
bool depthFirstSearch(char** matrix, char* word, int row, int col, int index, int** path) {
    //check if we found the entire word. if found, exit function with success
    if (index == strlen(word)) {
        check = true;
    }
    
    //check if we are out of bounds (attempting to access elements outside the array can result in crashes and weird behavior)
    if (row < 0 || row > bSize || col < 0 || col > bSize) {
        return false;
    }
    
    //check if the current cell in the matrix matches the letter(word[index]) we are searching for
    if (matrix[row][col] != word[index]) {
        return false;
    }
    
    //if we get to this point, then cell element matches our letter. we then update the path value to the corresponding index
    //path[row][col] = concatenateDigits(index + 1, path[row][col]);
    
    //we now will recursively search in all directions, this is why we picked depth first search
    bool found = depthFirstSearch(matrix, word, row-1, col, index+1, path) ||   // search Up
                 depthFirstSearch(matrix, word, row+1, col, index+1, path) ||   // search Down
                 depthFirstSearch(matrix, word, row, col-1, index+1, path) ||   // search Left
                 depthFirstSearch(matrix, word, row, col+1, index+1, path) ||   // search Right
                 depthFirstSearch(matrix, word, row-1, col-1, index+1, path) || // search Up-Left
                 depthFirstSearch(matrix, word, row-1, col+1, index+1, path) || // search Up-Right
                 depthFirstSearch(matrix, word, row+1, col-1, index+1, path) || // search Down-Left
                 depthFirstSearch(matrix, word, row+1, col+1, index+1, path);   // search Down-Right
    
    //if the entire word is not found, reset the path array
    if (check == true) {
        path[row][col] = index;
    }

    return found;
}
---
modify it so that it  */
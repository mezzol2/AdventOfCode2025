#include <stdio.h>
#include "matrix.h"
#include <time.h>

int part1Func(struct CharMatrix matrix);
int shootBeam(struct CharMatrix matrix, int row, int col);

int main(){
    //start timer
    clock_t start = clock();

    //open file
    FILE *fptr;
    fptr = fopen("test.txt","r");

    struct CharMatrix matrix = buildCharMatrix(fptr);
    int part1 = part1Func(matrix);

    //end timer
    clock_t end = clock();

    printf("Part 1: %d\n", part1);
    // printf("Part 2: %lld\n", part2);
    printf("Time: %f seconds", ((float)(end-start))/CLOCKS_PER_SEC);

    return 0;
}

int part1Func(struct CharMatrix matrix){
    //determine where the beam starts
    int start = 0;
    while (matrix.charMatrix[0][start] != 'S'){
        start++;
    }

    return shootBeam(matrix, 1, start);
}

int shootBeam(struct CharMatrix matrix, int row, int col){
    //check if in bounds
    if (row < 0 || col < 0 || row >= matrix.numRow || col >= matrix.numCol){
        return 0;
    }

    //get the char at this point in the matrix
    char c = matrix.charMatrix[row][col];

    // | here means the beam is already here and we can stop
    if (c == '|') return 0;

    // ^ here means we hit a splitter and need to conintue to the left and right
    if (c == '^'){
        return 1 + shootBeam(matrix, row, col - 1) + shootBeam(matrix, row, col+1);
    }

    // . here means there is empty space and the beam continues
    return shootBeam(matrix, row + 1, col);
}
#include <stdio.h>
#include <time.h>
#include "matrix.h"

int part1Func(struct CharMatrix matrix);
long long part2Func(struct CharMatrix matrix);
int shootBeam(struct CharMatrix matrix, int row, int col);

int main(){
    //start timer
    clock_t start = clock();

    //open file
    FILE *fptr;
    fptr = fopen("input.txt","r");

    //build the matrix
    struct CharMatrix matrix = buildCharMatrix(fptr);

    //since part1 overwrites data in the martix and part 2 does not, part 2 is calculated first
    long long part2 = part2Func(matrix);  
    int part1 = part1Func(matrix);

    freeCharMatrix(matrix);

    //end timer
    clock_t end = clock();

    printf("Part 1: %d\n", part1);
    printf("Part 2: %lld\n", part2);
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
        //update the left spot if it not on the left edge
        if (0 < col){
            matrix.charMatrix[row][col-1] = '|';
        }
        //update the right spot if it not on the right edge
        if (col < matrix.numCol){
            matrix.charMatrix[row][col+1] = '|';
        }


        return shootBeam(matrix, row+1, col - 1) + shootBeam(matrix, row+1, col+1) + 1;
    }

    // . here means there is empty space and the beam continues
    matrix.charMatrix[row][col] = '|';
    return shootBeam(matrix, row + 1, col);
}

long long part2Func(struct CharMatrix matrix){
    //determine where the beam starts
    int start = 0;
    while (matrix.charMatrix[0][start] != 'S'){
        start++;
    }

    //initialize the current and previous lines as long long arrays
    long long *prev = (long long*)malloc(sizeof(long long)*matrix.numCol);
    long long *current = (long long*)malloc(sizeof(long long)*matrix.numCol);

    for (int i = 0; i < matrix.numCol; i++){
        prev[i] = 0;
        current[i] = 0;
    }

    prev[start] = 1;
    
    //iteratively propogate the paths through the current and previous arrays
    //odd rows can be skipped since they only contian '.' 
    for (int i = 1; i < matrix.numRow; i++){
        //go through each element in this row
        for (int j = 0; j < matrix.numCol; j++){
            
            //if the character above this spot is '^', then there are 0 beams at this spot
            if (matrix.charMatrix[i-1][j] == '^'){
                current[j] = 0;
            } else{
                long long fromLeft = 0; long long fromRight = 0;

                //check if paths will contine from the left
                if (j > 0 && matrix.charMatrix[i-1][j-1] == '^'){
                    fromLeft = prev[j-1];
                }

                //check if paths will contine from the right
                if (j < matrix.numCol - 1 && matrix.charMatrix[i-1][j+1] == '^'){
                    fromRight = prev[j+1];
                }

                current[j] = fromLeft + prev[j] + fromRight;
            }
        }
        //set the current array as the prev array
        //we keep the data in the new row and will overwrite data in the old row
        long long *temp = current;
        current = prev;
        prev = temp;
    }

    //total up the beams in the final version of the array
    long long total = 0;

    for (int i = 0; i < matrix.numCol; i++){
        total += prev[i];
    }

    //free memory
    free(prev);
    prev = NULL;
    free(current);
    current = NULL;

    return total;
}
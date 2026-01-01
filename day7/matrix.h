#include <stdio.h>
#include <stdlib.h>

struct CharMatrix
{
    int numCol;
    int numRow;
    char** charMatrix;
};


int getNumCol(FILE *fptr){
    //get the size of the line and number of columns
    int numCol = 0;
    char firstLine[200];
    fgets(firstLine,200,fptr);
    while(firstLine[numCol] != 10){  //check for a line break
        numCol++;
    }

    //set the pointer back at the beginning of the file
    fseek(fptr,0,0);

    return numCol;
}

int getNumRow(FILE *fptr, int numCol){
    //get size of the file
    fseek(fptr,0,SEEK_END);
    const int fileSize = ftell(fptr);
    
    //set the pointer back at the beginning of the file
    fseek(fptr,0,0);

    //determine the number of columns
    //We add 1 to numCol to account for the line break characters
    return fileSize / (numCol+1);
}

struct CharMatrix buildCharMatrix(FILE *fptr){
    int i, j;

    struct CharMatrix matrix;

    matrix.numCol = getNumCol(fptr);
    matrix.numRow = getNumRow(fptr, matrix.numCol);

    //allocate memory
    matrix.charMatrix = (char**)malloc(matrix.numRow*sizeof(char*));
    for (i = 0; i < matrix.numRow; i++){
        matrix.charMatrix[i] = (char*) malloc(matrix.numCol*sizeof(char));
    };
 
    //build the matrix
    fseek(fptr,0,0);
    for (i = 0; i < matrix.numRow; i++){
        for (j = 0; j < matrix.numCol; j++){
            matrix.charMatrix[i][j] = fgetc(fptr);
        }
        //move pointer to beginning of the lext line
        fgetc(fptr);
    }

    return matrix;
}

//for testing
void printCharMatrix(struct CharMatrix matrix){
    for (int i = 0; i < matrix.numRow; i++){
        for (int j = 0; j < matrix.numCol; j++){
            printf("%c",matrix.charMatrix[i][j]);
        }
        //new line
        printf("\n");
    }
}

//free memory
void freeCharMatrix(struct CharMatrix matrix){
    for (int i=0; i<matrix.numRow;i++){
        free(matrix.charMatrix[i]);
        matrix.charMatrix[i] = NULL;  
    }
    free(matrix.charMatrix);
    matrix.charMatrix = NULL;
    matrix.numRow = 0;
    matrix.numCol = 0;
}
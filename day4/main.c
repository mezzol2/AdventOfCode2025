#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
    FILE *fptr;
    fptr = fopen("test.txt","r");

    //get the size of the line and number of columns
    int colNum = 0;
    char firstLine[200];
    fgets(firstLine,200,fptr);
    while(firstLine[colNum] != 10){  //check for a line break
        colNum++;
    }

    //get size of the file
    fseek(fptr,0,SEEK_END);
    const int fileSize = ftell(fptr);

    //determine the number of columns
    //We add 1 to colNum to account for the line break characters
    const int rowNum = fileSize / (colNum+1);
    
    //set the pointer back at the beginning of the file
    fseek(fptr,0,0);

    int accessible = part1(fptr, colNum, rowNum);
    
    printf("Part 1: %d",accessible);

    return 0;
}

int part1(FILE *fptr,int colNum,int rowNum){
    int i, j;

    //allocate memory for the rolls of paper grid
    bool** grid = (bool**) malloc(rowNum*sizeof(bool*));
    for (i = 0; i < rowNum; i++){
        grid[i] = (bool*) malloc(colNum*sizeof(bool));
    };
 
    //build the grid
    for (i = 0; i < rowNum; i++){
        //move pointer to beginning of a line
        fseek(fptr,0,(colNum+1)*i);
        for (j = 0; j < colNum; j++){
            //check if there is an @, ASCII = 64
            if (fgetc(fptr) == 64){
                grid[i][j] = true;
            }
        }
    }
}
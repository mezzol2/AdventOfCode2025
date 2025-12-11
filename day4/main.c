#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Function prototype
bool** buildGrid(FILE *fptr, int colNum, int rowNum);
int part1Func(bool** grid, int colNum,int rowNum);
void freeGrid(bool** grid, int colNum,int rowNum);
bool checkNeighbors(bool** grid, int colNum,int rowNum, int i, int j);

int main(){
    FILE *fptr;
    fptr = fopen("input.txt","r");

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


    //build grid
    bool** grid = buildGrid(fptr, colNum, rowNum);

    //Print the grid; used for testing and debugging
    // for (int i =0;i<rowNum;i++){
    //     for (int j=0;j<colNum;j++){
    //         printf("%d",grid[i][j]);
    //     }
    //     printf("\n");
    // }
    
    //close file
    fclose(fptr);

    //Run part 1
    int part1 = part1Func(grid, colNum, rowNum);

    //Free memory
    freeGrid(grid,colNum,rowNum);
    
    printf("Part 1: %d", part1);

    return 0;
}

bool** buildGrid(FILE *fptr,int colNum,int rowNum){
    int i, j;

    //allocate memory for the rolls of paper grid
    bool** grid = (bool**)malloc(rowNum*sizeof(bool*));
    for (i = 0; i < rowNum; i++){
        grid[i] = (bool*) malloc(colNum*sizeof(bool));
    };
 
    //build the grid
    fseek(fptr,0,0);
    for (i = 0; i < rowNum; i++){
        for (j = 0; j < colNum; j++){
            //check if there is an @, ASCII = 64
            if (fgetc(fptr) == 64){
                grid[i][j] = true;
            } else{
                grid[i][j] = false;
            }
        }
        //move pointer to beginning of the lext line
        fgetc(fptr);
    }

    return grid;
}

int part1Func(bool** grid, int colNum,int rowNum){
    int i,j,count = 0;

    //iterate through the grid
    for (i=0; i<rowNum;i++){
        for (j=0; j<colNum;j++){
            //check if there is paper here
            if (grid[i][j]){
                //check the neighbors
                if (checkNeighbors(grid, colNum, rowNum, i, j)){
                    count++;
                }
            }
        }
    }

    return count;
}

void freeGrid(bool** grid, int colNum,int rowNum){
    for (int i=0; i<rowNum;i++){
        free(grid[i]);
        grid[i] = NULL;  
    }
    free(grid);
    grid = NULL;
}

bool checkNeighbors(bool** grid, int colNum,int rowNum, int i, int j){
    int neighbors = 0;
    bool ref = grid[i][j];
    bool ref2 = grid[1][3];

    //check left
    if (j != 0){
        //check above left
        if (i != 0){
            if (grid[i-1][j-1]) neighbors++;
        }
        //check direct left
        if (grid[i][j-1]) neighbors++;
        //check below left
        if (i != rowNum-1){
            if (grid[i+1][j-1]) 
                neighbors++;
        }
    }

    //check directly above
    if (i != 0){
        if (grid[i-1][j]) neighbors++;
    }

    //check directly below
    if (i != rowNum-1){
        if (grid[i+1][j]) neighbors++;
    }
        
    //check right
    if (j != colNum-1){
        //check above left
        if (i != 0){
            if (grid[i-1][j+1]) neighbors++;
        }
        //check direct left
        if (grid[i][j+1]) neighbors++;
        //check below left
        if (i != rowNum-1){
            if (grid[i+1][j+1]) 
                neighbors++;
        }
    }    

    return neighbors < 4;
}
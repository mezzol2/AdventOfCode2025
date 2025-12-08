#include <stdio.h>
#include <string.h>

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
    const int rowNUm = fileSize / (colNum+1);
    
    //set the pointer back at the beginning of the file
    fseek(fptr,0,0);
    
    
    printf("%d\n",colNum);
    printf("%d\n",rowNUm);
    printf("%d",fileSize);


    return 0;
}
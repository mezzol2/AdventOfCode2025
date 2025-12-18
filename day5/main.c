#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

struct Node* buildTree(struct Node *node, FILE *fptr);
int part1Func(struct Node *node, FILE *fptr);

int main(){
    //open file
    FILE *fptr;
    fptr = fopen("input.txt","r");

    //initialise the root of the tree
    struct Node* root = NULL;

    //build tree
    root = buildTree(root, fptr);

    //check values
    int part1 = part1Func(root, fptr);

    //close file
    fclose(fptr);

    printf("Part 1: %d\n", part1);

    return 0;
}

struct Node* buildTree(struct Node *root, FILE *fptr){
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 2; //arbitrary start value

    while ((read = getline(&line, &len, fptr)) > 1) {
        //if (read > 0 && line[read-1] == '\n') line[read-1] = '\0';
        char *lowStr = strtok(line, "-");
        char *highStr = strtok(NULL, "-");
        //if (!lowStr || !highStr) continue;
        long long low = atoll(lowStr);
        long long high = atoll(highStr);
        root = insertNode(root, low, high);
    }
    free(line);
    return root;
}

int part1Func(struct Node *root, FILE *fptr){
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 1; //arbitrary start value
    int count = 0;

    while ((read = getline(&line, &len, fptr))>0)
    {
        //as long as this is not the last line, delete the last character
        if (line[read-1] == '\n')
            line[read-1] = '\0';

        long long value = atoll(line);
        if (lookup(root, value)){
            count++;
        }
    }
    return count;
}
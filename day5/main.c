#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

struct Node* buildTree(struct Node *node, FILE *fptr);
int part1Func(struct Node *node, FILE *fptr);
int part2Func(struct Node *root);

int main(){
    //start timer
    clock_t start = clock();

    //open file
    FILE *fptr;
    fptr = fopen("test.txt","r");

    //initialise the root of the tree
    struct Node* root = NULL;

    //build tree
    root = buildTree(root, fptr);

    //check values
    int part1 = part1Func(root, fptr);

    //close file
    fclose(fptr);

    //get the number of ingredient ID's
    int part2 = part2Func(root);

    //end timer
    clock_t end = clock();

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);
    printf("Time: %f seconds", ((float)(end-start))/CLOCKS_PER_SEC);

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

//To solve part 2, we perform a traverasl of the tree.  I have arbitratily choosen to do a post-order reversal.
int part2Func(struct Node *root){
    return postOrder(root);
}
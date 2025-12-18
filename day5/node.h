#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    long long int low, high;
    struct Node *left, *right;
};

struct Node *createNode(long long int low, long long int high)
{
    //allocate memory for the Range struct
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    //initialize its values
    ptr->low = low;
    ptr->high = high;
    ptr->left = ptr->right = NULL;
    return ptr;
}

struct Node *insertNode(struct Node *node, long long int low, long long int high){
    //if node is null, create a node
    if (node == NULL){
        return createNode(low, high);
    }
    //if the new high is strictly less than this node's low, continue to the left
    if (high < node->low){
        node->left = insertNode(node->left,low, high);
    }
    //if the new low is strictly greater than this node's low, continue to the right
    else if (node->high < low){
        node->right = insertNode(node->right,low, high);
    }
    else { //check for overlaps
        //new low is lower than current low
        if (low < node->low){
            node->left = insertNode(node->left,low, node->low-1);
        }
        
        //new high is higher then current high
        if (node->high < high){
            node->right = insertNode(node->right,node->high+1,high);
        }
    }    

    return node;
}

bool lookup(struct Node* node, long long int x){
    if (node == NULL){
        return false;
    }
    if (node->low <= x && x <= node->high){
        return true;
    }
    if (x < node->low){
        return lookup(node->left,x);
    }
    return lookup(node->right,x);
}
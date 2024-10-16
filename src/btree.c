#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define M 4
//To know on wich line is the error for debugging
#define STRINGIFY(x) #x
#define DEBUG_ERROR(func, str, ...) printf("Error in function %s at line " STRINGIFY(__LINE__) ": " str, func, #__VA_ARGS__)


struct node{
    int keys;
    bool leaf;
    struct node *children[M];
    int tab_of_key[M-1];
}node;

struct node *createNode(bool leaf){
    struct node * createNode = (struct node*) malloc(sizeof(struct node));
    if(createNode == NULL){
        DEBUG_ERROR("createNode", "MEMORY ALLOCATION ERROR\n");
        exit(EXIT_FAILURE);
    }
    createNode->keys = 0;
    createNode->leaf = leaf; 
    for(int i = 0; i < M; i++){
        createNode->children[i] = NULL;
    }
    return createNode;
}
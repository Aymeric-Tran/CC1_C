#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include <stdbool.h>
#include <string.h>

void loadDataFromFile(const char *filename, bTree *tree) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    int key;
    while (fscanf(file, "%d", &key) != EOF) {
        insert(tree, key);
    }

    fclose(file);
}

int main(int argc, char* argv[], char* envp[]) {
    bTree *tree = create_bTree();

    const char *filename = "data.txt";
    loadDataFromFile(filename, tree);

    printf("Traversal of the B-Tree:\n");
    traverse(tree->root);
    printf("\n");

    return 0;
}
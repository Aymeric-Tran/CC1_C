#ifndef BTREE_H
#define BTREE_H

#define MAX 4

typedef struct bTreeNode {
    int keys[MAX-1];
    int actual_keys_in_node;
    bool leaf;
    struct bTreeNode *children[MAX];
} bTreeNode;

typedef struct bTree{
    bTreeNode *root;
} bTree;

bTree* create_bTree();
bTreeNode* new_Node(bool leaf);
void splitChild(bTreeNode *x, int i, bTreeNode *y);
void insert(bTree *tree, int k);

#endif // BTREE_H


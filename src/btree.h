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
void insertNonFull(bTreeNode *x, int k);
void traverse(bTreeNode *node);
void deleteKey(bTreeNode* node, int k);
int findKey(bTreeNode* node, int k);
void removeFromLeaf(bTreeNode* node, int idx);
void removeFromNonLeaf(bTreeNode* node, int idx);
int getPredecessor(bTreeNode* node, int idx);
int getSuccessor(bTreeNode* node, int idx);
void fill(bTreeNode* node, int idx);
void borrowFromPrev(bTreeNode* node, int idx);
void borrowFromNext(bTreeNode* node, int idx);
void merge(bTreeNode* node, int idx);

#endif // BTREE_H
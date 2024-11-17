#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

// Creates a new B-Tree and initializes the root node.
bTree* create_bTree() {
    bTree *tree = (bTree*)malloc(sizeof(bTree));
    if (tree == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    tree->root = new_Node(true);
    return tree;
}

// Allocates a new node for the B-Tree and sets its leaf property.
bTreeNode* new_Node(bool leaf) {
    bTreeNode *node = (bTreeNode*)malloc(sizeof(bTreeNode));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->leaf = leaf;
    node->actual_keys_in_node = 0;
    for (int i = 0; i < MAX; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Splits a child node that is full.
void splitChild(bTreeNode *x, int i, bTreeNode *y) {
    bTreeNode *z = new_Node(y->leaf);
    z->actual_keys_in_node = (MAX / 2) - 1;

    for (int j = 0; j < (MAX / 2) - 1; j++)
        z->keys[j] = y->keys[j + MAX / 2];

    if (!y->leaf)
        for (int j = 0; j < MAX / 2; j++)
            z->children[j] = y->children[j + MAX / 2];

    y->actual_keys_in_node = (MAX / 2) - 1;

    for (int j = x->actual_keys_in_node; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];

    x->children[i + 1] = z;

    for (int j = x->actual_keys_in_node - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[(MAX / 2) - 1];
    x->actual_keys_in_node++;
}

// Inserts a key into the B-Tree.
void insert(bTree *tree, int k) {
    bTreeNode *r = tree->root;
    if (r->actual_keys_in_node == MAX - 1) {
        bTreeNode *s = new_Node(false);
        tree->root = s;
        s->children[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, k);
    } else {
        insertNonFull(r, k);
    }
}

// Inserts a key into a non-full node.
void insertNonFull(bTreeNode *x, int k) {
    int i = x->actual_keys_in_node - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->actual_keys_in_node++;
    } else {
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++;
        if (x->children[i]->actual_keys_in_node == MAX - 1) {
            splitChild(x, i, x->children[i]);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->children[i], k);
    }
}

// Traverses the B-Tree and prints all keys.
void traverse(bTreeNode *node) {
    int i;
    for (i = 0; i < node->actual_keys_in_node; i++) {
        if (!node->leaf)
            traverse(node->children[i]);
        printf(" %d", node->keys[i]);
    }

    if (!node->leaf)
        traverse(node->children[i]);
}

// Finds the index of the first key that is greater than or equal to k.
int findKey(bTreeNode* node, int k) {
    int idx = 0;
    while (idx < node->actual_keys_in_node && node->keys[idx] < k)
        ++idx;
    return idx;
}

// Removes a key from a leaf node.
void removeFromLeaf(bTreeNode* node, int idx) {
    for (int i = idx + 1; i < node->actual_keys_in_node; ++i)
        node->keys[i - 1] = node->keys[i];
    node->actual_keys_in_node--;
}

// Removes a key from a non-leaf node.
void removeFromNonLeaf(bTreeNode* node, int idx) {
    int k = node->keys[idx];

    if (node->children[idx]->actual_keys_in_node >= (MAX + 1)/2) {
        int pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        deleteKey(node->children[idx], pred);
    } else if (node->children[idx + 1]->actual_keys_in_node >= (MAX + 1)/2) {
        int succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        deleteKey(node->children[idx + 1], succ);
    } else {
        merge(node, idx);
        deleteKey(node->children[idx], k);
    }
}

// Gets the predecessor of a key in the node subtree.
int getPredecessor(bTreeNode* node, int idx) {
    bTreeNode* cur = node->children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->actual_keys_in_node];
    return cur->keys[cur->actual_keys_in_node - 1];
}

// Gets the successor of a key in the node subtree.
int getSuccessor(bTreeNode* node, int idx) {
    bTreeNode* cur = node->children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

// Ensures that a node has enough keys to allow deletion operations.
void fill(bTreeNode* node, int idx) {
    if (idx != 0 && node->children[idx-1]->actual_keys_in_node >= (MAX+1)/2)
        borrowFromPrev(node, idx);
    else if (idx != node->actual_keys_in_node && node->children[idx+1]->actual_keys_in_node >= (MAX+1)/2)
        borrowFromNext(node, idx);
    else {
        if (idx != node->actual_keys_in_node)
            merge(node, idx);
        else
            merge(node, idx-1);
    }
}

// Borrows a key from the previous sibling.
void borrowFromPrev(bTreeNode* node, int idx) {
    bTreeNode* child = node->children[idx];
    bTreeNode* sibling = node->children[idx-1];

    for (int i=child->actual_keys_in_node-1; i >= 0; --i)
        child->keys[i+1] = child->keys[i];

    if (!child->leaf) {
        for (int i=child->actual_keys_in_node; i >= 0; --i)
            child->children[i+1] = child->children[i];
    }

    child->keys[0] = node->keys[idx-1];

    if (!node->leaf)
        child->children[0] = sibling->children[sibling->actual_keys_in_node];

    node->keys[idx-1] = sibling->keys[sibling->actual_keys_in_node-1];

    child->actual_keys_in_node += 1;
    sibling->actual_keys_in_node -= 1;
}

// Borrows a key from the next sibling.
void borrowFromNext(bTreeNode* node, int idx) {
    bTreeNode* child = node->children[idx];
    bTreeNode* sibling = node->children[idx+1];

    child->keys[(child->actual_keys_in_node)] = node->keys[idx];

    if (!(child->leaf)) 
        child->children[(child->actual_keys_in_node)+1] = sibling->children[0];

    node->keys[idx] = sibling->keys[0];
    
    for (int i=1; i < sibling->actual_keys_in_node; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i=1; i <= sibling->actual_keys_in_node; ++i)
            sibling->children[i-1] = sibling->children[i];
    }

    child->actual_keys_in_node += 1;
    sibling->actual_keys_in_node -= 1;
}

// Merges a node with its sibling.
void merge(bTreeNode* node, int idx) {
    bTreeNode* child = node->children[idx];
    bTreeNode* sibling = node->children[idx+1];

    child->keys[(MAX-1)/2 - 1] = node->keys[idx];

    for (int i=0; i<sibling->actual_keys_in_node; ++i)
        child->keys[i + (MAX-1)/2] = sibling->keys[i];

    if (!child->leaf) {
        for (int i=0; i<=sibling->actual_keys_in_node; ++i)
            child->children[i + (MAX-1)/2] = sibling->children[i];
    }

    for (int i=idx+1; i < node->actual_keys_in_node; ++i)
        node->keys[i-1] = node->keys[i];

    for (int i=idx+2; i <= node->actual_keys_in_node; ++i)
        node->children[i-1] = node->children[i];

    child->actual_keys_in_node += sibling->actual_keys_in_node+1;
    node->actual_keys_in_node--;

    free(sibling);
}

// Deletes a key from the B-Tree.
void deleteKey(bTreeNode* node, int k) {
    int idx = findKey(node, k);

    if (idx < node->actual_keys_in_node && node->keys[idx] == k) {
        if (node->leaf)
            removeFromLeaf(node, idx);
        else
            removeFromNonLeaf(node, idx);
    } else {
        if (node->leaf) {
            printf("The key %d is not present in the tree\n", k);
            return;
        }

        bool flag = (idx == node->actual_keys_in_node);
        
        if (node->children[idx]->actual_keys_in_node < (MAX + 1) / 2)
            fill(node, idx);

        if (flag && idx > node->actual_keys_in_node)
            deleteKey(node->children[idx-1], k);
        else
            deleteKey(node->children[idx], k);
    }
}
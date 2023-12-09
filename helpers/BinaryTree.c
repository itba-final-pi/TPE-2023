#include <stdio.h>

#include "BinaryTree.h"

typedef struct NodeAVL {
    size_t key;
    void * elem;
    struct NodeAVL * left, * right;
    int bf;
} NodeAVL;

typedef struct BinaryTreeCDT {
    AVLTree root;
    AVLTree iter;
} BinaryTreeCDT;

BinaryTree newBinaryTree(void) {
    return calloc(1, sizeof(BinaryTreeCDT));
}

static void rotateLeft(AVLTree * tp) {
    AVLTree parent = *tp, child = (*tp)->right;
    parent->right = child->left;
    child->left = parent;
    (*tp) = child;
}

static void rotateRight(AVLTree * tp) {
    AVLTree parent = *tp, child = (*tp)->left;
    parent->left = child->right;
    child->right = parent;
    (*tp) = child;
}

static void fixLeftImbalance(AVLTree * tp) {
    AVLTree t, parent, child, * cptr;
    parent = *tp;
    cptr = &(parent->left);
    child = *cptr;
    if (child->bf != parent->bf) {
        
        int oldBF = child->right->bf;
        rotateLeft(cptr);
        rotateRight(tp);
        t = *tp;
        t->bf = 0;
        switch (oldBF) {
            case -1:
                t->left->bf = 0; t->right->bf = 1;
                break;

            case 0:
                t->left->bf = t->right->bf = 0;
                break;

            case 1:
                t->left->bf = -1; t->right->bf = 0;
                break;
            
            default:
                break;
        }
    } else {
        rotateRight(tp);
        t = * tp;
        t->right->bf = t->bf = 0;
    }
}

static void fixRightImbalance(AVLTree * tp) {
    AVLTree t, parent, child, * cptr;
    parent = *tp;
    cptr = &(parent->right);
    child = *cptr;
    if (child->bf != parent->bf) {
        int oldBF = child->left->bf;
        rotateRight(cptr);
        rotateLeft(tp);
        t = *tp;
        t->bf = 0;
        switch (oldBF) {
            case -1:
                t->right->bf = 0; t->left->bf = 1;
                break;

            case 0:
                t->right->bf = t->left->bf = 0;
                break;

            case 1:
                t->right->bf = -1; t->left->bf = 0;
                break;
            
            default:
                break;
        }
    } else {
        rotateLeft(tp);
        t = * tp;
        t->left->bf = t->bf = 0;
    }
}

static int insertAVL(AVLTree * tp, size_t key, void * elem) {
    AVLTree t;
    int sign, delta;
    t = *tp;

    if (t == NULL) {
        t = malloc(sizeof(NodeAVL));
        t->key = key;
        t->elem = elem;
        t->bf = 0;
        t->left = t->right = NULL;
        *tp = t;
        return 1;
    }

    sign = key - t->key;

    if (sign == 0) return 0;

    if (sign < 0) {
        delta = insertAVL(&t->left, key, elem);
        if (delta == 0) return 0;
        switch (t->bf) {
            case 1:
                return (t->bf = 0);
            case 0:
                return -(t->bf = -1);
            case -1:
                fixLeftImbalance(tp);
                return 0;
            default:
                break ;
        }
    } else {
        delta = insertAVL(&t->right, key, elem);
        if (delta == 0) return 0;
        switch (t->bf) {
            case -1:
                return (t->bf = 0);
            case 0:
                return (t->bf = 1);
            case 1:
                fixRightImbalance(tp);
                return 0;
            default:
                break ;
        }
    }

    return 0;
}

void insert(BinaryTree * t, size_t key, void * elem) {
    insertAVL(&(*t)->root, key, elem);
}

static AVLTree searchRec(AVLTree t, size_t key) {
    if (t == NULL) return NULL;

    int sign = key - t->key;

    if (sign == 0) return t;

    if (sign < 0) {
        return searchRec(t->left, key);
    }

    return searchRec(t->right, key);
}

void * search(BinaryTree t, size_t key) {
    AVLTree node;
    if ( t == NULL || (node = searchRec(t->root, key)) == NULL ) return NULL;
    return node->elem;
}

#ifdef DEBUG_RUN_TESTS

AVLTree getBinaryTreeRoot(BinaryTree t) {
    return t->root;
}

AVLTree getLeftNode(AVLTree t) {
    return t->left;
}

AVLTree getRightNode(AVLTree t) {
    return t->right;
}

size_t getNodeKey(AVLTree t) {
    return t->key;
}

void * getNodeElement(AVLTree t) {
    return t->elem;
}

#endif

static void freeAVLTree(AVLTree t) {
    if (t && t->left) freeAVLTree(t->left);
    if (t && t->right) freeAVLTree(t->right);
    free(t);
}

void freeBinaryTree(BinaryTree t) {
    if (t && t->root) freeAVLTree(t->root);
    free(t);
}

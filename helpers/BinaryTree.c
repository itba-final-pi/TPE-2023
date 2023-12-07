#include <stdio.h>

#include "BinaryTree.h"

typedef struct Node {
    int key;
    struct Node * left, * right;
    int bf;
} Node;

BinaryTree newBinaryTree(void) {
    return calloc(1, sizeof(Node));
}

static void rotateLeft(BinaryTree * tp) {
    BinaryTree parent = *tp, child = (*tp)->right;
    parent->right = child->left;
    child->left = parent;
    (*tp) = child;
}

static void rotateRight(BinaryTree * tp) {
    BinaryTree parent = *tp, child = (*tp)->left;
    parent->left = child->right;
    child->right = parent;
    (*tp) = child;
}

static void fixLeftImbalance(BinaryTree * tp) {
    BinaryTree t, parent, child, * cptr;
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

static void fixRightImbalance(BinaryTree * tp) {
    BinaryTree t, parent, child, * cptr;
    parent = *tp;
    cptr = &(parent->right);
    child = *cptr;
    if (child->bf != parent->bf) {
        int oldBF = child->left->bf;
        rotateLeft(cptr);
        rotateRight(tp);
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
        t->right->bf = t->bf = 0;
    }
}

int insertAVL(BinaryTree * tp, int key) {
    BinaryTree t;
    int sign, delta;
    t = *tp;

    if (t == NULL) {
        t = newBinaryTree();
        t->key = key;
        t->bf = 0;
        t->left = t->right = NULL;
        *tp = t;
        return 1;
    }

    sign = key - t->key;

    if (sign == 0) return 0;

    if (sign < 0) {
        delta = insertAVL(&t->left, key);
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
        delta = insertAVL(&t->right, key);
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

BinaryTree getLeftNode(BinaryTree t) {
    return t->left;
}

BinaryTree getRightNode(BinaryTree t) {
    return t->right;
}

int getNodeKey(BinaryTree t) {
    return t->key;
}

void freeBinaryTree(BinaryTree tp) {
    if (tp && tp->left) freeBinaryTree(tp->left);
    if (tp && tp->right) freeBinaryTree(tp->right);
    free(tp);
}
#include <stdio.h>

#include "BinaryTree.h"
#include "Stack.h"

#define MAX(a,b) ((a) > (b) ? a : b)

static int getHeight(AVLTree n);
static AVLTree rotateLeft(AVLTree tp);
static AVLTree rotateRight(AVLTree tp);
static AVLTree insertAVL(AVLTree tp, size_t key, void * elem, int * added);
static AVLTree searchRec(AVLTree t, size_t key);
static void moveIteratorFarthestLeft(AVLTree current, Stack s);
static void freeAVLTree(AVLTree t);

typedef struct NodeAVL {
    size_t key;
    void * elem;
    struct NodeAVL * left, * right;
    int height;
} NodeAVL;

typedef struct BinaryTreeCDT {
    AVLTree root;
    Stack iter;
} BinaryTreeCDT;

BinaryTree newBinaryTree(void) {
    return calloc(1, sizeof(BinaryTreeCDT));
}

static int getHeight(AVLTree n) {
    if(n == NULL) {
        return 0;
    }

    return n->height;
}

int getBalanceFactor(AVLTree t){
    if( t == NULL ){
        return 0;
    }
    return getHeight(t->left) - getHeight(t->right);
}

static AVLTree rotateRight(AVLTree parent){
    AVLTree child = parent->left; 
    AVLTree aux = child->right; 
  
    child->right = parent; 
    parent->left = aux; 
  
    parent->height = MAX(getHeight(parent->left), getHeight(parent->right)) + 1; 
    child->height = MAX(getHeight(child->left), getHeight(child->right)) + 1; 
  
    return child; 
}

static AVLTree rotateLeft(AVLTree parent){
    AVLTree child = parent->right; 
    AVLTree aux = child->left; 
  
    child->left = parent; 
    parent->right = aux; 
  
    parent->height = MAX(getHeight(parent->left), getHeight(parent->right)) + 1; 
    child->height = MAX(getHeight(child->left), getHeight(child->right)) + 1; 
  
    return child; 
}

static AVLTree insertAVL(AVLTree tp, size_t key, void * elem, int * added){
    // Create/insert new node
    if (tp == NULL) {
        AVLTree node = malloc(sizeof(NodeAVL));
        node->key = key;
        node->elem = elem;
        node->left = node->right = NULL;
        node->height = 1;
        *added = 1;
        return node;
    }

    // Ignore duplicates
    if (key == tp->key) return tp;

    // Perform recursive insertion
    if (key < tp->key) {
        tp->left  = insertAVL(tp->left, key, elem, added);
    } else { // key > tp->key
        tp->right = insertAVL(tp->right, key, elem, added);
    }

    tp->height = MAX(getHeight(tp->left), getHeight(tp->right)) + 1;

    // Get the node's new balance factor
    int bf = getBalanceFactor(tp);

    if ( bf > 1 ) {
        if (key > tp->left->key) tp->left =  rotateLeft(tp->left); 
        return rotateRight(tp); 
    } 

    if ( bf < -1 ) {
        if (key < tp->right->key) tp->right = rotateRight(tp->right); 
        return rotateLeft(tp); 
    }

    // bf == 0 return the same node
    return tp;
}

int insert(BinaryTree t, size_t key, void * elem) {
    int added = 0;
    t->root = insertAVL(t->root, key, elem, &added);
    return added;
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

void toBeginTreeIter(BinaryTree t) {
    freeStack(t->iter);
    t->iter = newStack();
    moveIteratorFarthestLeft(t->root, t->iter);
}

int hasNextTreeElem(BinaryTree t) {
    return t != NULL ? isEmptyStack(t->iter) : 0;
}

static void moveIteratorFarthestLeft(AVLTree current, Stack s) {
    while (current && current->left) {
        push(s, current);
        current = current->left;
    }
    if (current) push(s, current);
}

void * getNextTreeElem(BinaryTree t) {
    AVLTree node = NULL;

    if ( isEmptyStack(t->iter) ||  (node = pop(t->iter)) == NULL  ) {
        return NULL;
    }

    if (node->right)
        moveIteratorFarthestLeft(node->right, t->iter);

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

static void treeprint(AVLTree root, int level)
{
        if (root == NULL)
                return;
        for (int i = 0; i < level; i++)
                printf(i == level - 1 ? "|-" : "  ");

        treeprint(root->left, level + 1);
        treeprint(root->right, level + 1);
}

void PRINT(BinaryTree t)
{
    treeprint(t->root, 0);
}

void freeBinaryTree(BinaryTree t) {
    if (t && t->root) freeAVLTree(t->root);
    if (t && t->iter) freeStack(t->iter);
    free(t);
}

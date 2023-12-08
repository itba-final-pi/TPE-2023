#include <stdlib.h>

#ifndef _binary_tree_h
#define _binary_tree_h

typedef struct NodeAVL * BinaryTree;

/**
 * @brief Creates a new BinaryTree ADT
 * 
 * @return BinaryTree 
 */
BinaryTree newBinaryTree(void);

void insert(BinaryTree * t, size_t key, void * elem);

BinaryTree getLeftNode(BinaryTree t);

BinaryTree getRightNode(BinaryTree t);

size_t getNodeKey(BinaryTree t);

void * getNodeElem(BinaryTree t);

void freeBinaryTree(BinaryTree tp);

#endif

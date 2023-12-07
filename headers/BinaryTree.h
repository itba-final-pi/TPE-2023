#include <stdlib.h>

#ifndef _binary_tree_h
#define _binary_tree_h

typedef struct Node * BinaryTree;

/**
 * @brief Creates a new BinaryTree ADT
 * 
 * @param file path to the file to be opened
 * @return BinaryTree 
 */
BinaryTree newBinaryTree(void);

int insertAVL(BinaryTree * tp, int key);

BinaryTree getLeftNode(BinaryTree t);

BinaryTree getRightNode(BinaryTree t);

int getNodeKey(BinaryTree t);

void freeBinaryTree(BinaryTree tp);

#endif

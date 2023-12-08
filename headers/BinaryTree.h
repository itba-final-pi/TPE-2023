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

/**
 * @brief Inserts a new key-value pair into the BinaryTree
 * 
 * @param t tree
 * @param key size_t key 
 * @param elem element (pointer)
 */
void insert(BinaryTree * t, size_t key, void * elem);

/**
 * @brief Returns the elem pointer corresponding to the key within the tree
 * 
 * NULL if not found
 * 
 * @param key 
 * @return void* 
 */
void * search(BinaryTree t, size_t key);

BinaryTree getLeftNode(BinaryTree t);

BinaryTree getRightNode(BinaryTree t);

size_t getNodeKey(BinaryTree t);

void * getNodeElem(BinaryTree t);

void freeBinaryTree(BinaryTree tp);

#endif

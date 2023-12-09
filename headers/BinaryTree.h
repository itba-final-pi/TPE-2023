#include <stdlib.h>

#ifndef _binary_tree_h
#define _binary_tree_h

typedef struct NodeAVL * AVLTree;
typedef struct BinaryTreeCDT * BinaryTree;

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

#ifdef DEBUG_RUN_TESTS

AVLTree getBinaryTreeRoot(BinaryTree t);

AVLTree getLeftNode(AVLTree t);

AVLTree getRightNode(AVLTree t);

size_t getNodeKey(AVLTree t);

void * getNodeElem(AVLTree t);

#endif

void freeBinaryTree(BinaryTree tp);

#endif

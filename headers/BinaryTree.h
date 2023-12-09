#include <stdlib.h>

#ifndef _binary_tree_h
#define _binary_tree_h

typedef struct NodeAVL * AVLTree;

/**
 * Balanced Binary Search Tree implementation.
 * 
 * Balancing is achieved by using an AVL Tree, based on the book "Programming Abstractions in C" by Eric S. Roberts
 * 
 * Special thanks to the University of San Francisco, California, for [their AVLTree Visualization tool](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html)
 */
typedef struct BinaryTreeCDT * BinaryTree;

/**
 * @brief Creates a new BinaryTree ADT
 * 
 * Allows storing key-value pairs, where the key is `size_t` and the value is a void pointer
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

/**
 * @brief Prepare the binary tree to start in-order interation
 * 
 * @param t BinaryTree
 */
void toBeginTreeIter(BinaryTree t);

/**
 * @brief Returns whether or not another element exists in the in-order tree traversal
 * 
 * @param t BinaryTree
 * @return int (1 if an element exists, 0 if the traversal was finished)
 */
int hasNextTreeElem(BinaryTree t);

/**
 * @brief Get the next element on the in-order tree traversal
 * 
 * Returns the **POINTER** that was stored
 * 
 * NULL if no element exists (or NULL was stored in the first place)
 * 
 * @param t BinaryTree
 * @return void * 
 */
void * getNextTreeElem(BinaryTree t);

#ifdef DEBUG_RUN_TESTS

AVLTree getBinaryTreeRoot(BinaryTree t);

AVLTree getLeftNode(AVLTree t);

AVLTree getRightNode(AVLTree t);

size_t getNodeKey(AVLTree t);

void * getNodeElement(AVLTree t);

#endif

void freeBinaryTree(BinaryTree tp);

#endif

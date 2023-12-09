#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tests.h"

#include "BinaryTree.h"

/**
 * Stacks store **pointers** 
 * 
 * To test this simply, we cast integers (10, 20, 30) to void pointers
 * 
 * So that we can validate the pointers to those memory addresses (that we don't technically own) are stored properly
 * 
 * i.e:
 * push(s, (void*) 10)
 * pop(s) // returns (void *) 10
 */

int
main(void) {
    BinaryTree tree = newBinaryTree();
    int value = 42;

    assert( search(tree, 10) == NULL );

    insert(tree, 10, (void *) 10 );
    insert(tree, 20, (void *) 20);
    insert(tree, 30, (void *) 30);
    insert(tree, 40, (void *) 40);

    assert( getNodeKey(getBinaryTreeRoot(tree)) == 20 );
    assert( getNodeKey(getLeftNode(getBinaryTreeRoot(tree))) == 10 );
    assert( getNodeKey(getRightNode(getBinaryTreeRoot(tree))) == 30 );
    assert( getNodeKey(getRightNode(getRightNode(getBinaryTreeRoot(tree)))) == 40 );

    insert(tree, 50, (void *) 50);
    assert( getNodeKey(getRightNode(getBinaryTreeRoot(tree))) == 40 );

    insert(tree, 25, &value);

    assert( getNodeKey(getBinaryTreeRoot(tree)) == 30 );
    assert( getNodeKey(getLeftNode(getBinaryTreeRoot(tree))) == 20 );
    assert( getNodeKey(getRightNode(getBinaryTreeRoot(tree))) == 40 );
    assert( getNodeKey(getRightNode(getLeftNode(getBinaryTreeRoot(tree)))) == 25 );

    assert( search(tree, 10) == (void *) 10 );
    assert( search(tree, 25) == (void *) &value );

    toBeginTreeIter(tree);

    void * tree_inorder[] = { (void *) 10, (void *) 20, (void *) &value, (void *) 30, (void *) 40, (void *) 50 };

    for (int i = 0; hasNextTreeElem(tree); i++) {
        void * p = (void *) getNextTreeElem(tree);
        assert( (void *)p == tree_inorder[i] );
    }
    

    freeBinaryTree(tree);

    return 0;
}

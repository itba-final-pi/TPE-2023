#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tests.h"

#include "BinaryTree.h"

int
main(void) {
    BinaryTree tree = newBinaryTree();
    int value = 42;

    insert(&tree, 10, (void *) 10 );
    insert(&tree, 20, NULL);
    insert(&tree, 30, NULL);
    insert(&tree, 40, NULL);

    assert( getNodeKey(getBinaryTreeRoot(tree)) == 20 );
    assert( getNodeKey(getLeftNode(getBinaryTreeRoot(tree))) == 10 );
    assert( getNodeKey(getRightNode(getBinaryTreeRoot(tree))) == 30 );
    assert( getNodeKey(getRightNode(getRightNode(getBinaryTreeRoot(tree)))) == 40 );

    insert(&tree, 50, NULL);
    assert( getNodeKey(getRightNode(getBinaryTreeRoot(tree))) == 40 );

    insert(&tree, 25, &value);

    assert( getNodeKey(getBinaryTreeRoot(tree)) == 30 );
    assert( getNodeKey(getLeftNode(getBinaryTreeRoot(tree))) == 20 );
    assert( getNodeKey(getRightNode(getBinaryTreeRoot(tree))) == 40 );
    assert( getNodeKey(getRightNode(getLeftNode(getBinaryTreeRoot(tree)))) == 25 );

    assert( search(tree, 10) == (void *) 10 );
    assert( search(tree, 25) == (void *) &value );

    freeBinaryTree(tree);

    return 0;
}

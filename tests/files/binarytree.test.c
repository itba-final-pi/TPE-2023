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

    insert(&tree, 10, NULL);
    insert(&tree, 20, NULL);
    insert(&tree, 30, NULL);
    insert(&tree, 40, NULL);

    assert( getNodeKey(tree) == 20 );
    assert( getNodeKey(getLeftNode(tree)) == 10 );
    assert( getNodeKey(getRightNode(tree)) == 30 );
    assert( getNodeKey(getRightNode(getRightNode(tree))) == 40 );

    insert(&tree, 50, NULL);
    assert( getNodeKey(getRightNode(tree)) == 40 );

    insert(&tree, 25, &value);

    assert( getNodeKey(tree) == 30 );
    assert( getNodeKey(getLeftNode(tree)) == 20 );
    assert( getNodeKey(getRightNode(tree)) == 40 );
    assert( getNodeKey(getRightNode(getLeftNode(tree))) == 25 );

    freeBinaryTree(tree);

    return 0;
}

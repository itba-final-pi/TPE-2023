#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tests.h"

#include "BinaryTree.h"

int
main(void) {
    BinaryTree tree = NULL;
    insertAVL(&tree, 10);
    insertAVL(&tree, 20);
    insertAVL(&tree, 30);
    insertAVL(&tree, 40);

    assert( getNodeKey(tree) == 20 );
    assert( getNodeKey(getLeftNode(tree)) == 10 );
    assert( getNodeKey(getRightNode(tree)) == 30 );
    assert( getNodeKey(getRightNode(getRightNode(tree))) == 40 );

    insertAVL(&tree, 50);
    assert( getNodeKey(getRightNode(tree)) == 40 );

    insertAVL(&tree, 25);

    assert( getNodeKey(tree) == 30 );
    assert( getNodeKey(getLeftNode(tree)) == 20 );
    assert( getNodeKey(getRightNode(tree)) == 40 );

    freeBinaryTree(tree);

    return 0;
}

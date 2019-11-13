#include <stdio.h>
#include <stdlib.h>

#include "tree_tests.h"

int main()
{
    int a = 6;
    int b = 21;
    int c = -4;
    int d = 0;
    int f = 120;

    Tree* tree = create_tree(sizeof(int), compare_ints, int_formatter);
    tree_insert(tree, &a);
    tree_insert(tree, &b);
    tree_insert(tree, &c);
    tree_insert(tree, &d);
    tree_insert(tree, &f);

    printf("%s\n", tree_as_string(tree));

    add_tests();
    search_tests();
    delete_tests();
}

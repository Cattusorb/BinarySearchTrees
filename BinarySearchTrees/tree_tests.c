#include "tree_tests.h"

/*
 * Function: test_with_strings
 * ----------------------------
 * runs a test where the expected output is a char*
 *
 */
void test_with_strings(const char* test_name, const char* result, const char* expected) {
	printf("Test: %s... ", test_name);

	if (strcmp(result, expected) == 0) {
		printf("passed\n");
	} else {
		printf("FAILED. Expected %s (result %s)\n", expected, result);
	}
}

/*
 * Function: test_false
 * ----------------------------
 * runs a test where the expected output is false
 *
 */
void test_false(const char* test_name, bool result) {
	printf("Test: %s... ", test_name);

	if (!result) {
		printf("passed\n");
	} else {
		printf("FAILED.");
	}
}

/*
 * Function: test_false
 * ----------------------------
 * runs a test where the expected output is true
 *
 */
void test_true(const char* test_name, bool result) {
	printf("Test: %s... ", test_name);

	if (result) {
		printf("passed\n");
	} else {
		printf("FAILED.");
	}
}

/*
 * Function: compare_ints
 * ----------------------------
 * Compares the data stored at pointers a and b, assuming both addresses store
 * integers
 *
 *   a, b: void pointers to integers
 *
 * returns: ans < 0 if a < b, ans > 0 if a > b, ans = 0 if a == b
 *
 */
int compare_ints(const void* a, const void* b) {
	return *((int*) a) - *((int*) b);
}


/*
 * Function: int_formatter
 * ----------------------------
 * returns a char* representation of the integer stored at a given address
 *
 *	data: points to an integer
 *
 */
char* int_formatter(const void* data) {
	char* buffer = (char*) malloc(12 * sizeof(char));
	sprintf(buffer, "%d", *((int*) data));
	return buffer;
}

Tree* build_small_tree() {
	int a[] = {8, 5, 12, 3, 7, 18};
	Tree* tree = create_tree(sizeof(int), compare_ints, int_formatter); 

	for (int i = 0; i < 6; i++) {
		tree_insert(tree, &a[i]);
	}

	return tree;
}

Tree* build_bigger_tree() {
	int a[] = {9, 2, 12, -8, 10, 18, -5, 14, 25, -6, 1};
	Tree* tree = create_tree(sizeof(int), compare_ints, int_formatter); 

	for (int i = 0; i < 11; i++) {
		tree_insert(tree, &a[i]);
	}

	return tree;
}

void add_to_null_fails() {
	int k = 42;
	test_false("Can't add to null tree", tree_insert(NULL, &k));
}

void add_null_key_fails() {
	Tree* tree = create_tree(sizeof(int), compare_ints, int_formatter);
	test_false("Can't add null key", tree_insert(tree, NULL));
}

void add_to_empty_tree_works(){
	Tree* tree = create_tree(sizeof(int), compare_ints, int_formatter);
	int x = 42;
	tree_insert(tree, &x);
	test_with_strings("Add to empty tree", tree_as_string(tree), "Tree: 42");
}

void add_left_works(){
	Tree* tree = build_small_tree();
	int x = 10;
	tree_insert(tree, &x);
	test_with_strings("Add as left child", tree_as_string(tree), "Tree: 3 5 7 8 10 12 18");
}

void add_right_works(){
	Tree* tree = build_small_tree();
	int x = 4;
	tree_insert(tree, &x);
	test_with_strings("Add as right child", tree_as_string(tree), "Tree: 3 4 5 7 8 12 18");
}

void search_null_fails(){
	int k = 42;
	test_false("Can't search null tree", search(NULL, &k));
}

void search_for_null_key_fails(){
	Tree* tree = build_small_tree();
	test_false("Can't find null key", search(tree, NULL));
}

void failed_search_fails(){
	Tree* tree = build_small_tree();
	int k = 42;
	test_false("Testing failed search", search(tree, &k));
}

void normal_search_works(){
	Tree* tree = build_small_tree();
	int k = 7;
	test_true("Testing successful search", search(tree, &k));
}

void remove_from_null_fails(){
	int k = 42;
	test_false("Remove from null fails", tree_delete(NULL, &k));
}

void remove_null_key_fails(){
	Tree* tree = build_small_tree();
	test_false("Remove null key fails", tree_delete(tree, NULL));
}

void remove_from_empty_fails(){
	Tree* tree = create_tree(sizeof(int), compare_ints, int_formatter);
	int k = 42;
	test_false("Remove from empty tree fails", tree_delete(tree, &k));
}

void remove_missing_key_fails(){
	Tree* tree = build_small_tree();
	int k = 42;
	test_false("Remove missing key fails", tree_delete(tree, &k));
}

void remove_node_with_no_kids() {
	Tree* tree = build_bigger_tree();
	int k = 10;
	tree_delete(tree, &k);
	test_with_strings("Remove childless node",
					  tree_as_string(tree),
                      "Tree: -8 -6 -5 1 2 9 12 14 18 25");
}

void remove_node_with_right_child() {
	Tree* tree = build_bigger_tree();
	int k = -8;
	tree_delete(tree, &k);
	test_with_strings("Remove node with right child only",
					  tree_as_string(tree),
                      "Tree: -6 -5 1 2 9 10 12 14 18 25");
}

void remove_node_with_left_child() {
	Tree* tree = build_bigger_tree();
	int k = 2;
	tree_delete(tree, &k);
	test_with_strings("Remove node with left child only",
					  tree_as_string(tree),
                      "Tree: -8 -6 -5 1 9 10 12 14 18 25");
}

void remove_node_with_two_kids() {
	Tree* tree = build_bigger_tree();
	int k = 12;
	tree_delete(tree, &k);
	test_with_strings("Remove node with two kids",
					  tree_as_string(tree),
                      "Tree: -8 -6 -5 1 2 9 10 14 18 25");
}

void remove_root_works() {
	Tree* tree = build_bigger_tree();
	int k = 9;
    tree_delete(tree, &k);
	test_with_strings("Remove root", tree_as_string(tree), "Tree: -8 -6 -5 1 2 10 12 14 18 25");
}


void add_tests() {
	add_to_null_fails();
	add_null_key_fails();
	add_to_empty_tree_works();
	add_left_works();
	add_right_works();
}

void search_tests() {
	search_null_fails();
	search_for_null_key_fails();
	failed_search_fails();
	normal_search_works();
}

void delete_tests() {
	remove_from_null_fails();
	remove_null_key_fails();
	remove_from_empty_fails();
	remove_missing_key_fails();
	remove_node_with_no_kids();
	remove_node_with_left_child();
	remove_node_with_right_child();
	remove_node_with_two_kids();
	remove_root_works();
}

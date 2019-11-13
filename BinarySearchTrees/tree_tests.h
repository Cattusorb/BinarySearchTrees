#ifndef TREE_TESTS_H_INCLUDED
#define TREE_TESTS_H_INCLUDED

#include "bst.h"

void test_with_strings(const char*, const char*, const char*);
void test_false(const char*, bool);
void test_true(const char*, bool);

int compare_ints(const void*, const void*);
char* int_formatter(const void*);

void add_to_null_fails();
void add_null_key_fails();
void add_to_empty_tree_works();
void add_left_works();
void add_right_works();

void search_null_fails();
void search_for_null_key_fails();
void failed_search_fails();
void normal_search_works();

void remove_from_null_fails();
void remove_from_empty_fails();
void remove_null_key_fails();
void remove_missing_key_fails();
void remove_node_with_no_kids();
void remove_node_with_right_child();
void remove_node_with_left_child();
void remove_node_with_two_kids();
void remove_root_works();

void add_tests();
void search_tests();
void delete_tests();

#endif

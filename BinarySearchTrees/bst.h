#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct TreeNode TreeNode;
typedef struct Tree Tree;

/*
 * struct: TreeNode
 * ----------------------------
 * A node in a tree
 *
 * 	void* key: value of the node
 *	TreeNode* parent: pointer to the node's parent. NULL if this is the root.
 *	TreeNode* left: pointer to the node's left child. NULL if none exists.
 *	TreeNode* right: pointer to the node's right child. NULL if none exists.
 *
 */
struct TreeNode {
	void* key;
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;
};

/*
 * struct: Tree
 * ----------------------------
 * A Tree (could be a binary search tree or some other type)
 *
 * 	TreeNode* root: pointer to root node of the tree. NULL if tree is empty
 *	data_size: size of keys in bytes
 *	comparator: function for comparing keys. Must obey the following rules:
 *				comparator(a, b) < 0 if a < b
 *				comparator(a, b) > 0 if a > b
 *				comparator(a, b) = 0 if a == b
 *  formatter: function that returns a string representation of keys
 *
 */
struct Tree {
	TreeNode* root;
	size_t data_size;
	int (*compare)(const void*, const void*);
	char* (*formatter)(const void*);
};

// CREATION //
Tree* create_tree(const size_t, int (const void*, const void*), char* (const void*));
TreeNode* create_tree_node(const void*, const size_t);

// DISPLAY //
char* tree_as_string(const Tree*);
void subtree_as_string(const TreeNode*, char*, char* (const void*));

// DEPTH //
int max_depth(const TreeNode*);
int tree_depth(const Tree*);

// INSERT //
bool tree_insert(Tree*, const void*);

// SEARCH //
TreeNode* recursive_search(TreeNode*, const void*, int (const void*, const void*));
bool search(const Tree*, const void*);
TreeNode* tree_maximum(TreeNode*);

// DELETE //
void transplant(Tree* tree, TreeNode*, TreeNode*);
bool tree_delete(Tree*, const void*);

// DESTROY //
void destroy_subtree(TreeNode*);
void destroy_tree(Tree*);

#endif

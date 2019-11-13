#include "bst.h"

const int STRING_LENGTH = 1024;

/*
 * function: create_tree
 * ----------------------------
 * Creates an empty tree
 *
 *	data_size: size of keys in bytes
 *	comparator: function for comparing keys. Must obey the following rules:
 *				comparator(a, b) < 0 if a < b
 *				comparator(a, b) > 0 if a > b
 *				comparator(a, b) = 0 if a == b
 *	formatter: function that returns a string representation of keys
 *
 * returns: a tree with root = NULL
 */
Tree* create_tree(const size_t data_size,
				  int (*comparator)(const void*, const void*),
				  char* (*formatter)(const void*)) {

	// Allocate space for the tree
	Tree* tree = (Tree*) malloc(sizeof(Tree));

	// Initialize the attributes
	tree->root = NULL;
	tree->data_size = data_size;
	tree->compare = comparator;
	tree->formatter = formatter;

	// All done!
	return tree;
}

/*
 * function: create_tree_node
 * ----------------------------
 * Creates a tree node and sets its key equal to data
 *
 *
 * returns: A node with:
 *		key = data
 *		parent = NULL
 *		left = NULL
 *		right = NULL
 */
TreeNode* create_tree_node(const void* data, const size_t data_size) {
	// Allocate space for the node
	TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));

	// Set the key
	node->key = malloc(data_size);
	memcpy(node->key, data, data_size);

	// Init pointers to the parents and kids
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	// All done!
	return node;
}

/*
 * function: tree_as_string
 * ----------------------------
 * Returns a char* representation of the BST
 *
 * 	tree: the tree
 *
 */
char* tree_as_string(const Tree* tree) {
	char* output = (char*) malloc(STRING_LENGTH * sizeof(char));
	strcpy(output, "Tree:");
	subtree_as_string(tree->root, output, tree->formatter);
	return output;
}

/*
 * function: subtree_as_string
 * ----------------------------
 * Apppends the string representation of the subtree rooted at node to output
 * 	node: root of subtree
 *  output: storing the string representation of the whole tree
 *  formatter: converts node's key type to a string
 *
 * NB: this doesn't work if the string representation of the tree exceeds
 *     STRING_LENGTH. But fixing it would be annoying and getting tree_delete to
 *     work right took me three hours, so I'm not in the mood to fix this
 *     problem at the moment.
 */
void subtree_as_string(const TreeNode* node, char* output, char* (*formatter)(const void*)) {
	if (node != NULL) {
		subtree_as_string(node->left, output, formatter);
		char* key_as_string = formatter(node->key);
		sprintf(output,"%s %s", output, key_as_string);
		free(key_as_string);
		subtree_as_string(node->right, output, formatter);
	}
}

/*
 * Function: max_depth
 * ----------------------------
 * Recursively determines the depth of the subtree rooted at a node
 *
 *   x: node in a tree
 *
 * returns: maximum depth of subtree rooted at x
 *
 */
int max_depth(const TreeNode* x) {
	if (x == NULL) {
		return 0;
	} else {
		int lDepth = max_depth(x->left);
		int rDepth = max_depth(x->right);

		if (lDepth > rDepth) {
			return (lDepth + 1);
		} else {
			return (rDepth + 1);
		}
	}
}

/*
 * Function: tree_depth
 * ----------------------------
 * Determines the maximum depth of a tree
 *
 *   tree: a tree
 *
 * returns: maximum depth of tree
 *
 */
int tree_depth(const Tree* tree) {
	return max_depth(tree->root);
}

/*
 * function: tree_insert
 * ----------------------------
 * Inserts a node in to a tree obeying the binary search tree property
 *
 * 	tree: tree to add to
 *	data: data to put in new node
 *
 */
bool tree_insert(Tree* tree, const void* data) {
    if (tree == NULL || data == NULL)
    {
        return false;
    }

    // Create a new node to add to the tree
	TreeNode* z = create_tree_node(data, tree->data_size);

	TreeNode* x = tree->root;
	TreeNode* y = NULL;

	while (x != NULL)
    {
        y = x;
        if (tree->compare(data, x->key) < 0)
        {
            x = x->left;
        } else
        {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == NULL)
    {
        // Tree was empty, add new node as root
        tree->root = z;
    } else if (tree->compare(data, y->key) < 0)
    {
        // New node's key is smaller so it becomes
        // y's left child
        y->left = z;
    } else
    {
        // New node's key is larger so it becomes
        // y's right child
        y->right = z;
    }


	return true;
}

/*
 * function: recursive_search
 * ----------------------------
 * Recursively searches a subtree for a node containing query value
 *
 * 	node: root of the subtree
 *	q: value to find in tree
 *	compare: function for comparing keys. Must obey the following rules:
 *				compare(a, b) < 0 if a < b
 *				compare(a, b) > 0 if a > b
 *				compare(a, b) = 0 if a == b
 *
 * returns: a pointer to the node containing the key, NULL if not found
 */
TreeNode* recursive_search(TreeNode* node, const void* q, int (*compare)(const void*, const void*)) {
	if (node == NULL || q == NULL)
    {
        return false;
    }

    if (compare(q, node->key) < 0)
    {
        return recursive_search(node->left, q, compare);
    } else if (compare(q, node->key) > 0)
    {
        return recursive_search(node->right, q, compare);
    } else
    {
        return true;
    }

	return NULL;
}

/*
 * function: search
 * ----------------------------
 * Searches the tree for a query value
 *
 * 	tree: the tree
 *	q: value to find in tree
 *
 * returns: true if the key q is present in the tree, false if not
 */
bool search(const Tree* tree, const void* q) {
	if (tree == NULL || q == NULL) {
		return false;
	}

	return (recursive_search(tree->root, q, tree->compare) != NULL);
}

/*
 * Function: tree_maximum
 * ----------------------------
 * Finds the node with the maximum key value in the subtree rooted at node
 *
 *   node: root of a subtree
 *
 */
TreeNode* tree_maximum(TreeNode* node) {
	if (node == NULL) {
		return NULL;
	}

	while (node->right != NULL) {
		node = node->right;
	}

	return node;
}

/*
 * Function: transplant
 * ----------------------------
 * Replaces one node with another in a tree
 *
 *   tree: a tree
 *   u: node to be replaced
 *   v: node to replace with
 *
 */
void transplant(Tree* tree, TreeNode* u, TreeNode* v) {
    if (tree == NULL)
    {
        return false;
    }

	if (u->parent == NULL)
    {
        tree->root = v;
    } else if (u = u->parent->left)
    {
       u->parent->left = v;
    } else
    {
        u->parent->right = v;
    }

    if (v != NULL)
    {
        v->parent = u->parent;
    }

    destroy_subtree(u);
}

/*
 * Function: tree_delete
 * ----------------------------
 * Finds the shallowest node with a given key value and removes it
 *
 *   tree: a tree
 *   key: key to remove
 *
 * returns: true if removal is successful, false otherwise
 *
 */
bool tree_delete(Tree* tree, const void* key) {
    TreeNode* node = tree->root;

    if (tree == NULL || key == NULL)
    {
        return false;
    }

    if (node->left == NULL)
    {
        transplant(tree, node, node->right);
    } else if (node->right == NULL)
    {
        transplant(tree, node, node->left);
    } else
    {
        TreeNode* prev = tree_maximum(node->left);
        node->key = prev->key;
        transplant(tree, prev, prev->left);
    }

	return true;
}


/*
 * function: destroy_subtree
 * ----------------------------
 * Destroys all nodes in the subtree rooted at a given node
 *
 * 	node: node in a tree
 *
 */
void destroy_subtree(TreeNode* node) {
	if (node == NULL) {
		return;
 	}

	destroy_subtree(node->left);
	TreeNode* right = node->right;
	free(node->key);
	free(node);
	destroy_subtree(right);
}

/*
 * function: destroy_tree
 * ----------------------------
 * Destroys all nodes in a tree and the tree itself
 *
 * 	tree: tree to destroy
 *
 */
void destroy_tree(Tree* tree) {
	destroy_subtree(tree->root);
	free(tree);
}

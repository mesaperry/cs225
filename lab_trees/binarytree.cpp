/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(this->root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    if (subRoot == nullptr) { return; }
    Node* temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = temp;
    mirror(subRoot->left);
    mirror(subRoot->right);
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    InorderTraversal<T> tree_traverse = InorderTraversal<T>(this->root);
	T prev = -1;
	for (Node * curr : tree_traverse) {
		if (curr->elem < prev) {
			return false;
		}
		prev = curr->elem;
	}
	return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrderedRecursive(this->root);
}
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const Node* subRoot) const
{
    if (subRoot == NULL) { return true; }
	if (subRoot->left!=NULL && maxValue(subRoot->left) > subRoot->elem) { return false; }
	if (subRoot->right!=NULL && minValue(subRoot->right) < subRoot->elem) { return false; }
	if (!isOrderedRecursive(subRoot->left) || !isOrderedRecursive(subRoot->right)) { return false; }
	return true;
}
template <typename T>
int BinaryTree<T>::maxValue(const Node* subRoot) const
{
	if (subRoot == nullptr) { return -1; }
	int high = -1;
	high = std::max(high, subRoot->elem);
	if (subRoot->left != NULL) { high = std::max(high, subRoot->left->elem); }
	if (subRoot->right != NULL) { high = std::max(high, subRoot->right->elem); }
	return high;
}
template <typename T>
int BinaryTree<T>::minValue(const Node* subRoot) const
{
	if (subRoot == nullptr) { return -1; }
	int low = 2147483647;
	low = std::min(low, subRoot->elem);
	if (subRoot->left != NULL) { low = std::min(low, subRoot->left->elem); }
	if (subRoot->right != NULL) { low = std::min(low, subRoot->right->elem); }
	return low;
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    // your code here
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return -1;
}

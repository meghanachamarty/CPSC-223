/* Meghana Chamarty 
 * mc3547
 *4/18/23
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for CPSC 223
 * Part of: Homework assignment "AVL Trees" for CPSC 223
 */

#include <iostream>

#include "AVLTree.h"
#include "pretty_print.h"

using namespace std;

/*
 * Input: data (the value to store), multiplicity of the node, height of the
 *      node, left and right child pointers
 * Returns: avl tree node.
 * Does: creates a new node with values given as input parameter
 */
static Node *new_node(int data, int multiplicity, int height, Node *left, Node *right)
{
    Node* node = new Node();

    node->data = data;
    node->count = multiplicity;
    node->height = height;
    node->left = left;
    node->right = right;

    return node;
}

/*
 * Input: data (the value to store)
 * Returns: avl tree node.
 * Does: calls a helper function to create a new node with default
 *        values parameter
 */
static Node *new_node(int data)
{
    return new_node(data, 1, 0, NULL, NULL);
}

/********************************
 * BEGIN PUBLIC AVLTREE SECTION *
 ********************************/

// Default Constructor // 
AVLTree::AVLTree()
{
    this->root = NULL; 
}

// copy constructor // 
AVLTree::AVLTree(const AVLTree &source)
{
    this->root = pre_order_copy(source.root);
}

// destructor // 
AVLTree::~AVLTree()
{
    post_order_delete(root); 
}

/*
 * Input: const AVLTree &source
 * Returns: AVLTree
 * Does: assignment overload
 */ 
AVLTree &AVLTree::operator=(const AVLTree &source)
{
    if (this == &source) {
        return *this;
    }
    Node* new_root = pre_order_copy(source.root); 
    post_order_delete(root);
    root = new_root;  
    return *this;
}

/*
 * Input: N/A
 * Returns: int
 * Does: public find minimum
 */  
int AVLTree::find_min() const
{
    return find_min(root)->data;
}

/*
 * Input: N/A
 * Returns: int
 * Does: public find maximum
 */ 
int AVLTree::find_max() const
{
    return find_max(root)->data;
}

/*
 * Input: int
 * Returns: boolean
 * Does: searches AVLTree (public)
 */ 
bool AVLTree::contains(int value) const
{
    return contains(root, value);
}

/*
 * Input: int
 * Returns: N/A
 * Does: inserts a int into the AVLTree (public)
 */ 
void AVLTree::insert(int value)
{
    root = insert(root, value);
}

/*
 * Input: int
 * Returns: N/A
 * Does: removes a int from the AVLTree (public)
 */
void AVLTree::remove(int value)
{
    root = remove(root, value);
}

/*
 * Input: N/A
 * Returns: int
 * Does: determines height of tree (public)
 */
int AVLTree::tree_height() const
{
    return tree_height(root);
}

/*
 * Input: N/A
 * Returns: int
 * Does: determines the number of nodes in the AVLTree
 */
int AVLTree::node_count() const
{
    return node_count(root);
}

/*
 * Input: N/A
 * Returns: int
 * Does: determines the sum of all the nodes in the AVLTree (public)
 */
int AVLTree::count_total() const
{
    return count_total(root);
}

/*
 * Input: N/A
 * Returns: N/A
 * Does: prints tree (public)
 */
void AVLTree::print_tree() const
{
    print_pretty(root, 1, 0, std::cout);
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

/*
 * Input: a node of the avl tree
 * Returns: min node of the avl tree
 * Does: private find minimum.
 */ 
Node *AVLTree::find_min(Node *node) const
{
    if (node->left != NULL){
        return find_min(node->left); 
    }
    else{
        return node;
    }
}

/*
 * Input: a node of the avl tree
 * Returns: the max node of the avl tree
 * Does: private find maximum
 */ 
Node *AVLTree::find_max(Node *node) const
{
    if (node->right != NULL){
        return find_max(node->right); 
    }
    else{
        return node; 
    }
}

/*
 * Input: int and a node of the avl tree
 * Returns: boolean
 * Does: searches AVLTree (private) for value
 */ 
bool AVLTree::contains(Node *node, int value) const {
    if (node == NULL){
        return false; 
    }
    if (node->data == value){
        return true; 
    }
    else if (contains(node->left, value) || contains(node->right, value)){
        return true;
    }
    return false;
}

/*
 * Input: int and a node of the avl tree
 * Returns: a node of the avl tree with the inserted value
 * Does: inserts int at given node
 */ 
Node *AVLTree::insert(Node *node, int value)
{
    /* BST insertion start */
    if (node == NULL)
    {
        return new_node(value);
    }
    else if (value < node->data)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insert(node->right, value);
    }
    else if (value == node->data)
    {
        node->count++;
        return node;
    }
    /* BST insertion ends */

    /* AVL maintenance start */
    node->height = 1 + max(tree_height(node->left), tree_height(node->right));
    node = balance(node);
    /* AVL maintenace end */

    return node;
}

/*
 * Input: int and a node of the avl tree
 * Returns: a node of the avl tree with the removed int value
 * Does: removes int at given node
 */
Node *AVLTree::remove(Node *node, int value)
{
    /* BST removal begins */
    if (node == NULL)
    {
        return NULL;
    }

    Node *root = node;
    if (value < node->data)
    {
        node->left = remove(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = remove(node->right, value);
    }
    else
    {
        // We found the value. Remove it.
        if (node->count > 1)
        {
            node->count--;
        }
        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                root = NULL;
                delete node;
                return root;
            }
            else if (node->left != NULL && node->right == NULL)
            {
                root = node->left;
                node->left = NULL;
                delete node;
            }
            else if (node->left == NULL && node->right != NULL)
            {
                root = node->right;
                node->right = NULL;
                delete node;
            }
            else
            {
                Node *replacement = find_min(node->right);
                root->data = replacement->data;
                root->count = replacement->count;
                replacement->count = 1;
                root->right = remove(root->right, replacement->data);
            }
        }
    }
    /* BST removal ends */

    /* AVL maintenance begins */
    if (root != NULL)
    {
        root->height = 1 + max(tree_height(root->left), tree_height(root->right));
        root = balance(root);
    }
    /* AVL maintenance ends */

    return root;
}

/*
 * Input: a node of the avl tree
 * Returns: int
 * Does: returns height of a node (private)
 */
int AVLTree::tree_height(Node *node) const
{
    if (node == NULL)
    {
        return -1; 
    }
    else 
    {
        return node->height; 
    }
}

/*
 * Input: a node of the avl tree
 * Returns: int
 * Does: determines the number of nodes in the AVLTree
 */
int AVLTree::node_count(Node *node) const
{
    if (node == NULL)
    {
        return 0; 
    }
    else
    {
        return 1 + node_count(node->left) + node_count(node->right); 
    }
}

/*
 * Input: a node of the avl tree
 * Returns: int
 * Does: determines the sum of all the nodes in the AVLTree (private)
 */
int AVLTree::count_total(Node *node) const
{
    if (node == NULL){
        return 0; 
    }
    else 
    { 
        return node->count * node->data + count_total(node->left) + count_total(node->right); 
    }
}

/*
 * Input: a node of the avl tree
 * Returns:a node of the copied node
 * Does: deep copies a node, its information, and its children (private)
 */
Node *AVLTree::pre_order_copy(Node *node) const
{
    if (node == NULL)
    {
        return NULL;
    }
    Node *new_node = new Node();
    new_node->count = node->count; 
    new_node->data  = node->data; 
    new_node->height = node->height; 

    new_node->left = pre_order_copy(node->left); 
    new_node->right = pre_order_copy(node->right); 
    return new_node;
}

/*
 * Input: a node of the avl tree
 * Returns: N/A
 * Does: deep deletes a node, its information, and its children (private)
 */
void AVLTree::post_order_delete(Node *node)
{
    if (node == NULL)
    {
        return; 
    }
    post_order_delete(node->left); 
    post_order_delete(node->right);
    delete node; 
}

/*
 * Input: a node of the avl tree
 * Returns: a node of the balenced avl tree
 * Does: balences a binary tree to be an AVLTree
 */
Node *AVLTree::balance(Node *node)
{
    if (abs(height_diff(node)) > 1)
    {
        Node* x = node;
        if (height_diff(x) < 0)
        {
            Node* y = node->right; 
            if (height_diff(node->right) <= 0)
            {
                return left_rotate(x); 
            }
            else
            {
                x->right= right_rotate(y); 
                return left_rotate(x); 
            }
        }
        else
        {
            Node* y = node->left; 
            if (height_diff(node->left) <= 0)
            { 
                // zigzag case, rotate y left, rotate x right //
                x->left = left_rotate(y); 
                return right_rotate(x); 
            }
            else
            { 
                // straight line case, rotate x right //
                return right_rotate(x); 
            }
        }
    }
    return node; 
}

/*
 * Input: a node of the avl tree
 * Returns: a node of the rotated avl tree
 * Does: rotates a given node right
 */
Node *AVLTree::right_rotate(Node *node)
{
    if (node != NULL && node->left != NULL)
    {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = 1 + max(tree_height(node->left), tree_height(node->right));
    temp->height = 1 + max(tree_height(temp->left), tree_height(temp->right));
    return temp; 
    }
    return node; 
}

/*
 * Input: a node of the avl tree
 * Returns: a node of the rotated avl tree
 * Does: rotates a given node left
 */
Node *AVLTree::left_rotate(Node *node)
{
    if (node != NULL && node->right != NULL){
        Node* temp = node->right;
        node->right = temp->left; 
        temp->left = node; 
        node->height = 1 + max(tree_height(node->left), tree_height(node->right));
        temp->height = 1 + max(tree_height(temp->left), tree_height(temp->right));
        return temp;
    } 
    return node; 
}

// Input: a node of the avl tree
// Returns: integer value signifying the height difference.
// Does: calculates the difference in the height of the left and child subtree of node
int AVLTree::height_diff(Node *node) const
{
    if (node->left == NULL && node->right == NULL){
        return 0; 
    }
    if (node->right == NULL){
        return node->left->height + 1;
    }
    if (node->left == NULL){
        return -1 * (node->right->height + 1); 
    }
    else{
        return node->left->height - node->right->height; 
    }
}

// Input: a node of the avl tree and a child node of the avl tree
// Returns: a node of the avl tree
// Does: finds the parent of the given child node. 
Node *AVLTree::find_parent(Node *node, Node *child) const
{
    if (node == NULL)
        return NULL;

    if (node->left == child or node->right == child)
    {
        return node;
    }

    if (child->data > node->data)
    {
        return find_parent(node->right, child);
    }
    else
    {
        return find_parent(node->left, child);
    }
}

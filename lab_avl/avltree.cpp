/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = 0;
    //std::cout << "rebalance " << subtree->key << " height " << subtree->height << std::endl;
    if (subtree->left == NULL && subtree->right == NULL) { balance = 0; }
    else if (subtree->left != NULL && subtree->right != NULL) { balance = subtree->right->height - subtree->left->height; }
    else if (subtree->left != NULL) { balance = (subtree->left->height+1) * -1; }
    else if (subtree->right != NULL) { balance = (subtree->right->height+1); }
    //std::cout << "balance " << balance << std::endl;
    if (balance == 2) {
        int balance_r = 0;
        if (subtree->right->right != NULL && subtree->right->left != NULL) { balance_r = subtree->right->right->height - subtree->right->left->height; }
        else if (subtree->right->right != NULL) { balance_r = (subtree->right->right->height+1); }
        else if (subtree->right->left != NULL) { balance_r = (subtree->right->left->height+1) * -1; }

        if (balance_r == 1) {
            rotateLeft(subtree);
            subtree->left->height = subtree->right->height;
        }
        else {
            rotateRightLeft(subtree);
            subtree->left->height = subtree->height;
            subtree->height = subtree->right->height;
            subtree->right->height = subtree->left->height;
        }
    }
    else if (balance == -2) {
        int balance_l = 0;
        if (subtree->left->right != NULL && subtree->left->left != NULL) { balance_l = subtree->left->right->height - subtree->left->left->height; }
        else if (subtree->left->right != NULL) { balance_l = (subtree->left->right->height+1); }
        else if (subtree->left->left != NULL) { balance_l = (subtree->left->left->height+1) * -1; }

        if (balance_l == -1) {
            rotateRight(subtree);
            subtree->right->height = subtree->left->height;
        }
        else {
            rotateLeftRight(subtree);
            subtree->right->height = subtree->height;
            subtree->height = subtree->left->height;
            subtree->left->height = subtree->right->height;
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        //std::cout << "key " << key << std::endl;
        Node* node = new Node(key, value);
        node->height = 0;
        subtree = node;
        return;
    }
    
    if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }// else {
    //    subtree->value = value;
    //    return;
    //}

    if (subtree->left == NULL && subtree->right == NULL) { subtree->height = 0; }
    else if (subtree->left != NULL && subtree->right != NULL) { subtree->height = std::max(subtree->left->height, subtree->right->height) + 1; }
    else if (subtree->left != NULL) { subtree->height = subtree->left->height+1; }
    else if (subtree->right != NULL) { subtree->height = subtree->right->height+1; }

    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* predecessor = subtree->left;
            Node* p_pre = subtree;
            while (predecessor->right != NULL) {
                p_pre = predecessor;
                predecessor = predecessor->right;
            }
            if (p_pre == subtree) {
                delete subtree;
                subtree = predecessor;
            }
            else {
                predecessor->left = subtree->left;
                predecessor->right = subtree->right;
                delete subtree;
                subtree = predecessor;
                p_pre->right = NULL;
            }
        } else {
            /* one-child remove */
            // your code here
            Node* child;
            if (subtree->left == NULL) { child = subtree->right; }
            else { child = subtree->left; }
            delete subtree;
            subtree = child;
        }
        // your code here
    }
}

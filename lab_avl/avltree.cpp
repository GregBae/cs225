/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include <algorithm>
 #include <cmath>
 #include <iostream>

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
    if (t == NULL){
        return;
    }
    if (t->right == NULL){
        return;
    }

    Node *temp = t->right;
    t->right = temp->left;
    temp->left = t;


    t->height = max(heightOrNeg1(t->right),heightOrNeg1(t->left))+1;
    temp->height = max(heightOrNeg1(temp->right),heightOrNeg1(temp->left))+1;
    t = temp;
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
    if (t == NULL)
        return;
    if (t->left == NULL)
        return;

    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;

    t->height = max(heightOrNeg1(t->right),heightOrNeg1(t->left))+1;
    temp->height = max(heightOrNeg1(temp->right),heightOrNeg1(temp->left))+1;

    t = temp;
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
    int diff = heightOrNeg1(subtree->right)-heightOrNeg1(subtree->left);
    int b = abs(diff);
    if (b <= 1){
        return;
    }
    else{
        if (diff > 0){
            if (heightOrNeg1(subtree->right->right)-heightOrNeg1(subtree->right->left)>=1){
                rotateLeft(subtree);
            }
            else{
                rotateRightLeft(subtree);
            }
        }else{
            if (heightOrNeg1(subtree->left->right)-heightOrNeg1(subtree->left->left)>=1){
                rotateLeftRight(subtree);
            }
            else{
                rotateRight(subtree);
            }
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
    if (subtree == NULL){
        subtree = new Node(key,value);
        return;
    }

    if (subtree->key == key){
        subtree->value = value;
    }
    else if (key > subtree->key){
        insert(subtree->right,key,value);
    }
    else{
        insert(subtree->left,key,value);
    }

    subtree->height = max(heightOrNeg1(subtree->right),heightOrNeg1(subtree->left))+1;
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
        remove(subtree->left,key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * temp = subtree->left;
            if (temp->right == NULL){
                temp->right = subtree->right;
                Node * delete_temp = subtree;
                subtree = temp;
                delete_temp->right = NULL;
                delete_temp->left = NULL;
                delete delete_temp;
            }
            else{
                Node * temp_p = temp;
                temp = temp->right;
                while(temp->right != NULL){
                    temp_p = temp;
                    temp = temp->right;
                }
                temp->right = subtree->right;
                temp->left = subtree->left;
                Node * temp_subtree = subtree;
                subtree = temp;
                temp_p->right = NULL;
                temp_subtree->right = NULL;
                temp_subtree->left = NULL;
                delete temp_subtree;
            }
        } else {
            /* one-child remove */
            // your code here
            Node * temp = subtree;
            if(subtree->left != NULL){
                subtree = subtree->left;
                delete temp;
            }
            else{
                subtree = subtree->right;
                delete temp;
            }
        }
        // your code here
        if(subtree != NULL){
            subtree->height = max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
            rebalance(subtree);
        }
    }
}

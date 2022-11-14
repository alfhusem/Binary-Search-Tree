#include "BST.h"

#include <iostream>

/**
 * Implement the BST constructor
 */
BST::BST() {
    root = nullptr;
    numElements = 0;
    // cout << "BST created" << endl;
}

/**
 * Implement the BST destructor
 */
BST::~BST() {
    // cout << "BST deleted" << endl;
    clear();
}

/**
 * Implement size() correctly
 */
unsigned int BST::size() const {
    return numElements;
}

/**
 * Implement clear() correctly without memory leaks
 */
void BST::clear() { //ASK this doesn't work
    Node *node;
    Node *tmp;
    node = root;
    while (node != nullptr) {
        // cout << "checking node: " << node->data << endl;
        if (node->leftChild){
            
            node = node->leftChild;
            node->parent->leftChild = nullptr;
            
        }
        else if (node->rightChild) {
            node = node->rightChild;
            node->parent->rightChild = nullptr;
        }
        else{
            // Node has no children
            // cout << "node: " << node->data;
            // if(node->parent){
                // cout << ", parent: " << node->parent->data << endl;
            // }
            // else{
            //     cout << ", no parent" << endl;
            // }
            tmp = node;
            node = node->parent;
            delete tmp; // ASK not sure if this deletes the node
        }
    }
    numElements = 0;
    root = nullptr;
}

/**
 * Implement insert() correctly
 */
bool BST::insert(int element) {
    Node *node;
    Node *new_node = new Node(element);
    node = root;
    // cout << "test " << element << endl;
    while (node != nullptr) {
        if (node->data == element){
            delete new_node;
            // cout << "failed insert " << element << endl;
            return false;
        }
        else if (node->data > element) {
            if (node->leftChild){
                node = node->leftChild;
                //cout << "deeper left " << node->data << endl;
            }
            else {
                node->leftChild = new_node;
                new_node->parent = node;
                numElements ++;
                // cout << "insert successful " << element << ", parent: " << node->data << endl;
                return true;
            }
        }
        else if (node->data < element) {
            if (node->rightChild){
                node = node->rightChild;
                //cout << "deeper right " << node->data << endl;
            }
            else {
                node->rightChild = new_node;
                new_node->parent = node;
                numElements ++;
                // cout << "insert successful " << element << ", parent: " << node->data << endl;
                return true;
            }
        }
        
    }
    root = new_node;
    numElements ++;
    // cout << "insert successful " << element << ", is root" << endl;
    return true;
}


/**
 * Implement find() correctly
 */
bool BST::find(const int & query) const {
    Node *node;
    node = root;
    while (node != nullptr) {
        if (node->data == query){ // ASK pointer?
            return true;
        }
        else if (node->data > query) {
            if (node->leftChild){
                node = node->leftChild;
            }
            else {
                return false;
            }
        }
        else if (node->data < query) {
            if (node->rightChild){
                node = node->rightChild;
            }
            else {
                return false;
            }
        }
        
    }
}

/**
 * Implement the getLeftMostNode() function correctly
 */
BST::Node* BST::getLeftMostNode() {
    /* YOUR CODE HERE 
    Not used yet*/
    Node *node;
    node = root;
    while (node != nullptr) {
        if (node->leftChild){
            node = node->leftChild;
        }
        else{
            // Node has no children
            return node;
        }
    }
    return node;
}

/**
 * Implement the BST::Node successor function correctly
 */
BST::Node* BST::Node::successor() {
    Node *node;
    node = this;
    if (node->rightChild){
        node = node->rightChild;
        while (node->leftChild) {
            node = node->leftChild;
        }
        return node;
    }
    else{
        // Node has no right child
        while (node != nullptr) {
            if (node->parent) {
                // if current node is its parent's left child, return parent
                if (node->parent->leftChild) {
                    if (node == node->parent->leftChild) {
                        return node->parent;
                    }
                }
                node = node->parent;
                
            }
            else {
                
                // node is the root node with no right child
                return nullptr;
            }
            
        }
    }
    
    
}

//---

#include "BinaryTree.h"

bool contains(vector<int> vec, int elem){
    if (vec.size() == 0) {
        return false;
    }
    for(int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == elem)
        {
            return true;
        }
    }
    return false;
}

/**
 * Implement balanceFactors() correctly
 */
unordered_map<int,int> BinaryTree::balanceFactors() {
    unordered_map<int, int> umap;
    Node* node = root;
    Node* child = root;
    int leftBf;
    int rightBf;
    int maxH;
    int h;
    vector<int> checkedEdge;
   
    while (node != nullptr) {
        leftBf = 0;
        rightBf = 0;
    
        /*traverse left*/
        maxH = 0;
        h = 0;
        checkedEdge.clear();

        if (node->leftChild) {
            child = node->leftChild;
            h++;
        }
        while (child != node){
        
            if (child->leftChild && !contains(checkedEdge, child->leftChild->label)){
                
                checkedEdge.insert(0, child->leftChild->label);
                child = child->leftChild;
                h++;
            }
            else if (child->rightChild) {
                child = child->rightChild;
                checkedEdge.insert(0, child->parent->rightChild.label);
                h++;
            }
            else{
                if (h > maxH){
                    maxH = h;
                }
                h--;
                child = child->parent;
                 
            }
        }
        leftBf = maxH;

        /*traverse right*/
        maxH = 0;
        h = 0;
        checkedEdge.clear();

        if (node->rightChild) {
            child = node->rightChild;
            h++;
        }
        while (child != node){
        
            if (child->leftChild && !contains(checkedEdge, child->leftChild->label)){
                
                checkedEdge.insert(0, child->leftChild->label);
                child = child->leftChild;
                h++;
            }
            else if (child->rightChild) {
                child = child->rightChild;
                checkedEdge.insert(0, child->parent->rightChild.label);
                h++;
            }
            else{
                if (h > maxH){
                    maxH = h;
                }
                h--;
                child = child->parent;
                 
            }
        }
        rightBf = maxH;

        /*add to unordered_map*/
        umap[node->label] = rightBf - leftBf;
    }

    /*Set next node*/
    if (node->leftChild && !contains(checkedEdge, child->leftChild->label)){
        
        checkedEdge.insert(0, child->leftChild->label);
        child = child->leftChild;
        h++;
    }
    else if (child->rightChild) {
        child = child->rightChild;
        checkedEdge.insert(0, child->parent->rightChild.label);
        h++;
    }
    else{
        if (h > maxH){
            maxH = h;
        }
        h--;
        child = child->parent;       
    }
    
}

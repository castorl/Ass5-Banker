//
// Created by <Name> on <Date>.
//

#include "accounttree.h"



//constructor
AccountTree::AccountTree(){}

// Delete all nodes in BST
AccountTree::~AccountTree(){
    clear();
}

// Insert new account, returns true if successful
//ordered by ID number.
bool AccountTree::insert(Account* account) {
    //check if root is null
    if(root == nullptr){
        root = new Node(account);
        return true;
    }
        return insertRecursive(root,account);
}

// Retrieve account
// returns true if successful AND *account points to account
bool AccountTree::retrieve(const int& accountNumber, Account*& account) const {
    //starts at root and calls recursive that does binary search
    if(root != nullptr){
        return retrieveRecursive(root,accountNumber,account);

    }
    return false;
}

// Display information on all accounts
void AccountTree::display() const {
    if(root == nullptr){
        cout << "Error in display"; //debug purpose
    }
    //call recursive
    displayR(root);
}

// delete all information in AccountTree
void AccountTree::clear() {
    clearR(root);
    //sets root to nullptr
    root = nullptr;
}

// check if tree is empty
bool AccountTree::isEmpty() const {
    //if there is no root, then there is nothing
    return root == nullptr;
}

//recursive insert recursive helper
//if lower than root go left, higher go right
bool AccountTree::insertRecursive(Node* curr, Account* account){
    //less go left
    if(account->getID() < curr-> getAccount()-> getID()){
        //base case for recursion
        if(curr->getLeft() == nullptr){//if left ptr is null(so leaf)
            Node* newNodeAccount = new Node(account);
            curr->setLeft(newNodeAccount);
            return true;
        }
        return insertRecursive(curr->getLeft(),account);

    }
    if(account->getID() > curr-> getAccount()-> getID()){
        //base case for recursion
        if(curr->getRight() == nullptr){//if right ptr is null(so leaf)
            Node* newNodeAccount = new Node(account);
            curr->setRight(newNodeAccount);
            return true;
        }
        return insertRecursive(curr->getRight(),account);

    }
    //greater go right
    return false;
}

//recursive clear function helper
void AccountTree::clearR(Node* curr){
    //recursion stops when all accounts are deleted
    if(curr != nullptr){
        //go all the way to left leaf
        //delete and come back up
        clearR(curr->getLeft());
        //go all the way to right leaf
        //delete and come back up
        clearR(curr->getRight());
        delete curr->getAccount();
        delete curr;
    }
}

//recursive retrieve helper
bool AccountTree::retrieveRecursive(Node* curr,const int& acctID, Account*& account) const{
    //start at root and search binary
    //base case
    if(curr->getAccount()->getID() == acctID){
        account = curr->getAccount();
        return true; 
    }
    //if account is less go right
    if(curr->getAccount()->getID() < account->getID()){
        return retrieveRecursive(curr->getLeft(),acctID,account);
    }
    //greater go left
    if(curr->getAccount()->getID() > account->getID()){
        return retrieveRecursive(curr->getRight(),acctID,account);
    }
    return false;
}

//recursive display function helper
void AccountTree::displayR(Node* curr) const{
    //display from top and go on
    //base case
    if(curr != nullptr){
        //once all left are display stops recursion
        displayR(curr->getLeft());
        cout << *curr->getAccount() << endl; //derefence account
        //once it gets to right leaf stops recursion
        displayR(curr->getRight());
    }
}

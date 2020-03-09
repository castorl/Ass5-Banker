//
// Created by Melanie Alexandra Palomino & Alana Yao on March 6, 2020.
//

#include "accounttree.h"

using namespace std;

// constructor
AccountTree::AccountTree() : root(nullptr) {}

// Delete all nodes in BST
AccountTree::~AccountTree() { clear(); }

// Insert new account, returns true if successful
// ordered by ID number.
bool AccountTree::insert(Account* account) {
    // check if tree is empty
    if (isEmpty()) {
        root = new Node(account);
        return true;
    }
    return insertRecursive(root, account);
}

// Retrieve account
// returns true if successful AND *account points to account
bool AccountTree::retrieve(const int& accountNumber, Account*& account) const {
    // starts at root and calls recursive that does binary search
    if (!isEmpty()) {
        return retrieveRecursive(root, accountNumber, account);
    }
    return false;
}

// recursive retrieve helper
bool AccountTree::retrieveRecursive(Node* curr, const int& acctID,
                                    Account*& account) const {
    // start at root and search binary
    // base case
    if (curr->getAccount()->getID() == acctID &&
        curr->getAccount()->getFirst() == account->getFirst() &&
        curr->getAccount()->getLast() == account->getLast()) {
        account = curr->getAccount();
        return true;
    }
    // if account is less go right
    if (curr->getAccount()->getID() < account->getID()) {
        return retrieveRecursive(curr->getLeft(), acctID, account);
    }
    // greater go left
    if (curr->getAccount()->getID() > account->getID()) {
        return retrieveRecursive(curr->getRight(), acctID, account);
    }
    return false;
}

// recursive insert recursive helper
// if lower than root go left, higher go right
bool AccountTree::insertRecursive(Node* curr, Account* account) {
    // less go left
    if (account->getID() < curr->getAccount()->getID()) {
        // base case for recursion
        if (curr->getLeft() == nullptr) { // if left ptr is null(so leaf)
            Node* newNodeAccount = new Node(account);
            curr->setLeft(newNodeAccount);
            return true;
        }
        return insertRecursive(curr->getLeft(), account);
    }
    if (account->getID() > curr->getAccount()->getID()) {
        // base case for recursion
        if (curr->getRight() == nullptr) { // if right ptr is null(so leaf)
            Node* newNodeAccount = new Node(account);
            curr->setRight(newNodeAccount);
            return true;
        }
        return insertRecursive(curr->getRight(), account);
    }
    // greater go right
    return false;
}

// Display information on all accounts
void AccountTree::display() const {
    if (root == nullptr) {
        cout << "Error in display"; // debug purpose
    }
    // call recursive
    displayR(root);
}

// recursive display function helper
void AccountTree::displayR(Node* curr) const {
    // display from top and go on
    // base case
    if (curr != nullptr) {
        // once all left are display stops recursion
        displayR(curr->getLeft());
        cout << *curr->getAccount() << endl; // derefence account
        // once it gets to right leaf stops recursion
        displayR(curr->getRight());
    }
}

// delete all information in AccountTree
void AccountTree::clear() {
    clearR(root);
    // sets root to nullptr
    root = nullptr;
}

// recursive clear function helper
void AccountTree::clearR(Node* curr) {
    // recursion stops when all accounts are deleted
    if (curr != nullptr) {
        // go all the way to left leaf
        // delete and come back up
        clearR(curr->getLeft());
        // go all the way to right leaf
        // delete and come back up
        clearR(curr->getRight());
        delete curr->getAccount();
        delete curr;
    }
}

// check if tree is empty
bool AccountTree::isEmpty() const {
    // if there is no root, then there is nothing
    return root == nullptr;
}

// return true if the account ID number is already in use
bool AccountTree::idExists(int& id) const {
    if (!isEmpty()) // search for ID if tree is not empty
        return findId(id, root);
    return false;
}

bool AccountTree::findId(int& id, Node* curr) const {
    if (curr->getAccount() == nullptr) // reached child, id not found
        return false;

    // if ID found
    if (curr->getAccount()->getID() == id) {
        return true;
    }

    // if id is less go left
    if (curr->getAccount()->getID() < id) {
        return findId(id, curr->getLeft());
    } else { // id is more, go right
        return findId(id, curr->getRight());
    }
}

// retrieves address of an account that exists
Account* AccountTree::fetch(int& id) const {
    return fetchR(id, root)->getAccount();
}

// fetch account recursive helper method
Node* AccountTree::fetchR(int id, Node* curr) const {
    // account found
    if (curr->getAccount()->getID() == id) {
        return curr;
    } 
    // not found yet, keep recursing
    if (curr->getAccount()->getID() < id) {
        return fetchR(id, curr->getLeft());
    } else { // id is more, go right
        return fetchR(id, curr->getRight());
    }
}

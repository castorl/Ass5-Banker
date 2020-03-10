//
// Created by Melanie Alexandra Palomino & Alana Yao on March 6, 2020.
//

#pragma once

#include "account.h"
#include <iostream>

class AccountTree {
  public:
    // Create BST
    AccountTree();

    // Delete all nodes in BST
    ~AccountTree();

    // Insert new account
    bool insert(Account* account);

    // Retrieve account
    // returns true if successful AND *Account points to account
    // NOLINTNEXTLINE
    bool retrieve(const int& accountNumber, Account*& account);

    // Display information on all accounts
    void display() const;

    // delete all information in AccountTree
    void clear();

    // check if tree is empty
    bool isEmpty() const;

  private:
    class Node {
      public:
        explicit Node(Account* account)
            : account{account}, right{nullptr}, left{nullptr} {}

        // returns account
        auto* getAccount() const { return this->account; }

        // sets account

        // NOLINTNEXTLINE
        void setAccount(Account*& account) { this->account = account; }

        // returns left pointer
        auto* getLeft() const { return this->left; }
        // returns right pointer
        auto* getRight() const { return this->right; }

        // sets node value to right pointer
        void setRight(Node* node) { this->right = node; }

        // sets node value to left pointer
        void setLeft(Node* node) { this->left = node; }

      private:
        Account* account;
        Node* right;
        Node* left;
    };

    Node* root = nullptr;

    // recursive insert helper function
    bool insertRecursive(Node* curr, Account* account);

    // recursive display function helper
    void displayR(Node* curr) const;

    // recursive clear function helper
    void clearR(Node* curr);

    // recursive retrieve helper
    // NOLINTNEXTLINE
    bool retrieveRecursive(Node* curr, const int& acctID, Account*& account);
};
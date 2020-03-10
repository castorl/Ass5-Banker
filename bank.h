
//
// Created by Melanie Alexandra Palomino & Alana Yao on March 6, 2020.
//
/* Banker has three phases
// Phase 1: Read txt and input to queue
// Phase 2: Runs every transaction
// Phase 3: Displays all open accounts and balances in these accounts
*/

#pragma once

#include "accounttree.h"
#include <fstream>
#include <queue>

using namespace std;

class Bank {
  public:
    // constructor for bank
    Bank();
    // destructor for bank
    ~Bank();

    // calls helper functions to process transactions
    void processTransactions(const string& fileName);

    // helper function to add transactions to queue
    void addToQueue(const string& fileName);

    // displays accounts' fund balances
    void displayAllBankBalances() const;

  private:
    AccountTree accounts;

    struct Action {

        char TransType{};
        // maybe change to acctOf to avoid confusion
        int AcctTo{};
        int AcctFrom{};
        int Amount{};
        string First;
        string Last;
        int FundTo{};
        int FundFrom{};
    };

    // queue that holds the transactions read from the file
    queue<Action> transactionsQ;
};
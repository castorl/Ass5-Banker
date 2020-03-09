
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
#include <string>

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
        char transType;
        // maybe change to acctOf to avoid confusion
        int acctTo;
        int acctFrom;
        int amount;
        string first;
        string last;
        int fundTo;
        int fundFrom;
    };

    queue<Action> transactionsQ;

    // helper function to run transactions
    // use the switch case for transactions of either opening, depositing,
    // withdrawing, transferring or displaying to the correct account
    void processQueue();
};

//
// Created by <Name> on <Date>. 
//
/* Banker has three phases
// Phase 1: Read txt and input to queue 
// Phase 2: Runs every transaction 
// Phase 3: Displays all open accounts and balances in these accounts 
*/

#pragma once

#include "accounttree.h"
#include <fstream>
#include <string>
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

    struct Action{
      char transType; 
      int acctTo; 
      int acctFrom;
      int amount; 
      string first; 
      string last; 
      int fundTo; 
      int fundFrom;
    };

    queue <Action> transactionsQ;

    // helper function to set transaction type
    void transClassification();

    // helper function to run transactions
    // use the switch case for transactions of either opening, depositing, 
    // withdrawing, transferring or displaying to the correct account 
    void processQueue();

    // function helper to determine the type of transaction 
    // void transactionType(const string& transaction, char type);

    //helper function to check input data
    // bool checkData(stringstream& s,int& amt, int& fund, int& ID, int& ID2, int& fund2); 
};
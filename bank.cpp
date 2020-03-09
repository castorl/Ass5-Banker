//
// Created by Melanie Alexandra Palomino & Alana Yao on March 6, 2020.
//
/* Banker has three phases
// Phase 1: Read txt and input to queue
// Phase 2: Runs every transaction
//Banker also must print out errors to file
// Phase 3: Displays all open accounts and balances in these accounts
*/

/*TO DO:
 * - Verify ID input, cannot be greater than 99999 or less than 10000 (except H)
 * -
 *
 *
 * */
#include "bank.h"
#include "accounttree.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

using namespace std;

// constuctor for bank
Bank::Bank() {}

// destructor for bank
Bank::~Bank() {
    // nothing to delete
}

// Function calls function to add transactions to queue
// Calls helper functions to processes transactions
void Bank::processTransactions(const string& fileName) {
    // call helper funciton to add and create structs
    addToQueue(fileName);
    // call function to process queue
    processQueue();
}

// process file's lines as transactions and add to queue
// throws invalid_argument exception if fileName not found
void Bank::addToQueue(const string& fileName) {
    // create file reader
    ifstream inFile;
    inFile.open(fileName);

    if (!inFile) {
        throw invalid_argument("Invalid file name!");
    }

    string line;
    char type;
    string lastName, firstName;
    int acctNum, acctNum2, amt, fund, fund2;

    // while not end of file
    // add transactions to queue
    while (!inFile.eof()) {
        getline(inFile, line); // check first letter
        stringstream s(line);
        s >> type;

        switch (type) {
            case 'O': // open account transaction
            {
                s >> lastName >> firstName >> acctNum;

                Action newAcct;
                newAcct.transType = type;
                newAcct.last = lastName;
                newAcct.first = firstName;
                newAcct.acctTo = acctNum;

                transactionsQ.push(newAcct);
                break;
            }
            case 'D': // deposit transaction
            {
                s >> acctNum >> amt;
                fund = acctNum % 10;
                acctNum = acctNum / 10;

                Action deposit;
                deposit.transType = type;
                deposit.acctTo = acctNum;
                deposit.amount = amt;
                deposit.fundTo = fund;

                transactionsQ.push(deposit);
                break;
            }
            case 'W': // withdraw transaction
            {
                s >> acctNum >> amt;
                fund = acctNum % 10;
                acctNum = acctNum / 10;

                Action withdraw;
                withdraw.transType = type;
                withdraw.acctFrom = acctNum;
                withdraw.amount = amt;
                withdraw.fundFrom = fund;

                transactionsQ.push(withdraw);
                break;
            }
            case 'T': // transfer transaction
            {
                s >> acctNum >> amt >> acctNum2;
                fund = acctNum % 10;
                acctNum = acctNum / 10;
                fund2 = acctNum2 % 10;
                acctNum2 = acctNum2 / 10;

                Action transfer;
                transfer.transType = type;
                transfer.acctTo = acctNum2;
                transfer.acctFrom = acctNum;
                transfer.amount = amt;
                transfer.fundFrom = fund;
                transfer.fundTo = fund2;

                transactionsQ.push(transfer);
                break;
            }
            case 'H': // display history
            {
                s >> acctNum;
                if (acctNum > 9999) { // display history of specific fund
                    fund = acctNum % 10;
                    acctNum = acctNum / 10;
                } else {       // display history of whole account
                    fund = -1; // no fund specified
                }
                Action history;
                history.acctFrom = acctNum;
                history.fundFrom = fund;

                transactionsQ.push(history);
                break;
            }
        }
    }
    inFile.close();
}

// helper function that executes transactions, uses switch case to decide
void Bank::processQueue() {
    while (!transactionsQ.empty()) {
        Action *tracker = &transactionsQ.front();
        switch (tracker->transType) {
            case 'O': { // open account
                Account* openNew = new Account(tracker->first, tracker->last,
                                               tracker->acctTo);
                if (accounts.retrieve(tracker->acctTo, openNew) ||
                    !accounts.insert(openNew)) { 
                    // if account exists or couldn't insert
                    cout << "Error, account or account ID already in use.";
                }
                break;
            }
            case 'D': { // deposit
                if (accounts.idExists(tracker->acctTo)) {
                    Account* temp = &accounts.fetch(tracker->acctTo);
                    // make the deposit and record the transaction
                    temp->deposit(tracker->amount, tracker->fundTo);
                    string recordD =
                        to_string(tracker->transType) + " " + 
                        to_string(tracker->acctTo) +
                        to_string(tracker->fundTo) + " " + 
                        to_string(tracker->amount);
                    temp->recordTrans(recordD, tracker->fundTo);
                } else { // if account not found
                    cout << "Could not locate account with client ID "
                         << tracker->acctTo << "." << endl;
                }
                break;
            }
            // withdraw
            case 'W': {
                if (accounts.idExists(tracker->acctTo)) {
                    Account* temp = &accounts.fetch(tracker->acctFrom);
                    if (temp->withdraw(tracker->amount, 
                                       tracker->fundFrom)) {
                        // make the withdrawal and record the transaction
                        string recordW =
                            to_string(tracker->transType) + " " + 
                            to_string(tracker->acctFrom) +
                            to_string(tracker->fundFrom) + " " + 
                            to_string(tracker->amount);
                        temp->recordTrans(recordW, tracker->fundFrom);
                        ;
                    } else
                        cout << "Error, attempting to take out more than "
                                "available balance." << endl;
                } else {
                    // print error in transaction history of no account
                    cout << "Could not locate account with client ID " 
                         << tracker->acctTo << "." << endl;
                }
                break;
            }
            // transfer
            case 'T': {
                // if both accounts exist
                if (accounts.idExists(tracker->acctFrom) &&
                    accounts.idExists(tracker->acctTo)) {
                    Account* temp = &accounts.fetch(tracker->acctFrom);
                    Account* temp2 = &accounts.fetch(tracker->acctTo);
                    if (temp->withdraw(tracker->amount, tracker->fundFrom)) {
                        // make the withdrawal and record the transaction
                        string recordW =
                            to_string(tracker->transType) + " " + 
                            to_string(tracker->acctFrom) +
                            to_string(tracker->fundFrom) + " " + 
                            to_string(tracker->amount) + " " + 
                            to_string(tracker->acctTo) + 
                            to_string(tracker->fundTo);
                        temp->recordTrans(recordW,
                                          tracker->fundFrom);
                        ;
                        // make the desposit and record the transaction
                        temp2->deposit(tracker->amount, tracker->fundTo);
                        string recordD =
                            to_string(tracker->transType) + " " + 
                            to_string(tracker->acctTo) +
                            to_string(tracker->fundTo) + " " + 
                            to_string(tracker->amount);
                        temp2->recordTrans(recordD, tracker->fundTo);
                    } else
                        cout << "Error, attempting to take out more than "
                                "available balance."
                             << endl;
                } else {
                    cout << "Could not locate account of one or more of the "
                        "client IDs." << endl;
                }
                break;
            }
            // print history
            case 'H': {
                if (accounts.idExists(tracker->acctFrom)) {
                    Account* temp = &accounts.fetch(tracker->acctFrom);
                    temp->displayTrans(tracker->fundFrom);
                } else {
                cout << "Could not locate account with client ID "
                         << tracker->acctFrom << "." << endl;
                }
                break;
            }
        } // end of switch
        // pop action from queue
        transactionsQ.pop();
    } // end of while
}

// displays tree accounts' fund balances
void Bank::displayAllBankBalances() const { accounts.display(); }

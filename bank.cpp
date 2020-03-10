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
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

// constuctor for bank
Bank::Bank() = default;

// destructor for bank
Bank::~Bank() = default;
// nothing to delete

// process file's lines as transactions and add to queue
void Bank::addToQueue(const string& fileName) {
    // create file reader
    ifstream inFile;
    inFile.open(fileName);

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
            newAcct.TransType = type;
            newAcct.Last = lastName;
            newAcct.First = firstName;
            newAcct.AcctTo = acctNum;

            transactionsQ.push(newAcct);
            break;
        }
        case 'D': // deposit transaction
        {
            s >> acctNum >> amt;
            fund = acctNum % 10;
            acctNum = acctNum / 10;

            Action deposit;
            deposit.TransType = type;
            deposit.AcctTo = acctNum;
            deposit.Amount = amt;
            deposit.FundTo = fund;

            transactionsQ.push(deposit);
            break;
        }
        case 'W': // withdraw transaction
        {
            s >> acctNum >> amt;
            fund = acctNum % 10;
            acctNum = acctNum / 10;

            Action withdraw;
            withdraw.TransType = type;
            withdraw.AcctFrom = acctNum;
            withdraw.Amount = amt;
            withdraw.FundFrom = fund;

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
            transfer.TransType = type;
            transfer.AcctTo = acctNum2;
            transfer.AcctFrom = acctNum;
            transfer.Amount = amt;
            transfer.FundFrom = fund;
            transfer.FundTo = fund2;

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
            history.TransType = type;
            history.AcctFrom = acctNum;
            history.FundFrom = fund;

            transactionsQ.push(history);
            break;
        }
        default: {
            cout << "Invalid transaction type.";
            break;
        }
        }
    }
    inFile.close();
}

// Function calls function to add transactions to queue
// Calls helper functions to processes transactions
void Bank::processTransactions(const string& fileName) {
    // call helper funciton to add and create structs
    addToQueue(fileName);
    // process the queue
    Account* hold; // holds the account searched for, if found
    while (!transactionsQ.empty()) {
        Action* tracker = &transactionsQ.front(); // holds first item in queue
        switch (tracker->TransType) {
        case 'O': { // open account
            Account* openNew =
                new Account(tracker->First, tracker->Last, tracker->AcctTo);
            if (accounts.retrieve(tracker->AcctTo, hold)) {
                // if the account number is already in use
                cout << "Error, account ID already in use.";
                break;
            }
            accounts.insert(openNew);
            break;
        }
        case 'D': { // deposit
            if (accounts.retrieve(tracker->AcctTo, hold)) {
                // make the deposit and record the transaction
                hold->deposit(tracker->Amount, tracker->FundTo);
                string recordD;
                recordD += tracker->TransType;
                recordD += " " + to_string(tracker->AcctTo) +
                           to_string(tracker->FundTo) + " " +
                           to_string(tracker->Amount);
                hold->recordTrans(recordD, tracker->FundTo);
            } else { // if account not found
                cout << "Could not locate account with client ID "
                     << tracker->AcctTo << "." << endl;
            }
            break;
        }
        // withdraw
        case 'W': {
            if (accounts.retrieve(tracker->AcctFrom, hold)) {
                if (hold->withdraw(tracker->Amount, tracker->FundFrom)) {
                    // make the withdrawal and record the transaction
                    string recordW;
                    recordW += tracker->TransType;
                    recordW += " " + to_string(tracker->AcctFrom) +
                               to_string(tracker->FundFrom) + " " +
                               to_string(tracker->Amount);
                    hold->recordTrans(recordW, tracker->FundFrom);
                    ;
                } else
                    cout << "Error, attempting to take out more than "
                            "available balance."
                         << endl;
            } else {
                // print error in transaction history of no account
                cout << "Could not locate account with client ID "
                     << tracker->AcctTo << "." << endl;
            }
            break;
        }
        // transfer
        case 'T': {
            Account* hold2; // pointer to hold the account to transfer to
            // if both accounts exist
            if (accounts.retrieve(tracker->AcctFrom, hold) &&
                accounts.retrieve(tracker->AcctTo, hold2)) {
                if (hold->withdraw(tracker->Amount, tracker->FundFrom)) {
                    // make the withdrawal and record the transaction
                    string recordW;
                    recordW += tracker->TransType;
                    recordW += " " + to_string(tracker->AcctFrom) +
                               to_string(tracker->FundFrom) + " " +
                               to_string(tracker->Amount) + " " +
                               to_string(tracker->AcctTo) +
                               to_string(tracker->FundTo);
                    hold->recordTrans(recordW, tracker->FundFrom);
                    ;
                    // make the desposit and record the transaction
                    hold2->deposit(tracker->Amount, tracker->FundTo);
                    string recordD = to_string(tracker->TransType) + " " +
                                     to_string(tracker->AcctTo) +
                                     to_string(tracker->FundTo) + " " +
                                     to_string(tracker->Amount);
                    hold2->recordTrans(recordD, tracker->FundTo);
                } else
                    cout << "Error, attempting to take out more than "
                            "available balance."
                         << endl;
            } else {
                cout << "Could not locate account of one or more of the "
                        "client IDs."
                     << endl;
            }
            break;
        }
        // print history
        case 'H': {
            if (accounts.retrieve(tracker->AcctFrom, hold)) {
                hold->displayTrans(tracker->FundFrom);
            } else {
                cout << "Could not locate account with client ID "
                     << tracker->AcctFrom << "." << endl;
            }
            break;
        }
        default: {
            cout << "Invalid transaction type.";
            break;
        }
        } // end of switch
        // pop action from queue
        transactionsQ.pop();
    } // end of while
}

// displays tree accounts' fund balances
void Bank::displayAllBankBalances() const { accounts.display(); }

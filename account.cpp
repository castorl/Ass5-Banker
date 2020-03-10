//
// Created by Melanie Alexandra Palomino & Alana Yao on March 6, 2020.
//

#include "account.h"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;
// displays account info and final fund balances
ostream& operator<<(ostream& out, const Account& other) {
    cout << other.firstName << " " << other.lastName
         << " Account ID:" << other.accID << "\n";

    for (const auto& acctFund : other.acctFunds) {
        cout << "\t" << acctFund.FundName << ": " << acctFund.Balance << "\n";
    }
    return out;
}

// creates account with name, lastname and accID
Account::Account(string lastName, string firstName, int accID)
    : firstName(move(firstName)), lastName(move(lastName)), accID((accID)) {

    string name[] = {"Money Market",       "Prime Money Market",
                     "Long-Term Bond",     "Short-Term Bond",
                     "500 Index Fund",     "Capital Value Fund",
                     "Growth Equity Fund", "Growth Index Fund",
                     "Value Fund",         "Value Stock Index"};
    for (int i = 0; i < 10; i++) {
        acctFunds[i].FundName = name[i];
    }
}

// destructor
Account::~Account() = default;

// deposits amount into fund type of account
bool Account::deposit(int amt, int type) {
    // deposit amount
    acctFunds[type].Balance += amt;

    return true;
}

// withdraws amount from fund type
bool Account::withdraw(int amt, int type) {
    // checks if amount is too high
    if (amt > acctFunds[type].Balance) {
        // calculate amount needed to cover the shortage
        int extra = -1 * (acctFunds[type].Balance - amt); // make it positive
        int type2;
        // deciding what the other fund type is
        if (type % 2 == 1) { // if it's odd
            type2 = type - 1;
        } else {
            type2 = type + 1;
        }

        if (extra < acctFunds[type2].Balance) { // if the other type can cover
            acctFunds[type].Balance = 0;
            acctFunds[type2].Balance -= extra;
            string recordT = "T " + to_string(accID) +
                             to_string(type2) + " " +
                             to_string(extra) + " " + to_string(accID) + 
                             to_string(type);
            recordTrans(recordT, type2); // record the transfer from type 2 to type 1
            return true;
        }
        return false;
    }

    // else, continue to withdraw from fund
    acctFunds[type].Balance -= amt;

    return true;
}

// transfers amount into one fund type to another of the same account or other
bool Account::transfer(Account* other, int amt, int type, int oType) {
    // check if account has enough to withdraw
    if (!withdraw(amt, type)) {
        return false;
    }

    withdraw(amt, type);        // yes, withdraw from account
    other->deposit(amt, oType); // deposit to other account

    return true;
}

// displays history for account or single fund
void Account::displayTrans(int fund) const {
    cout << "Displaying Transaction History for " << firstName << " "
         << lastName;
    if (fund == -1) { // if no fund specified, display all histories
        cout << " by fund." << endl;
        for (const auto& a : acctFunds) {
            cout << a.FundName << ": $" << a.Balance << endl;
            for (const auto& i : a.FundRecord) {
                cout << "\t" << i << endl;
            }
        }
    } else {
        cout << "'s " << acctFunds[fund].FundName << ": $"
             << acctFunds[fund].Balance << endl;
        for (const auto& i : acctFunds[fund].FundRecord) {
            cout << "\t" << i << endl;
        }
    }
}

// helper function that records transactions to each fund
void Account::recordTrans(const string& transaction, int num) {
    acctFunds[num].FundRecord.push_back(transaction);
}

// returns ID of this account
int Account::getID() const { return accID; }

// returns client first name of this account
string Account::getFirst() const { return firstName; }

// returns client last name of this account
string Account::getLast() const { return lastName; }
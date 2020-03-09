//
// Created by Melanie Alexandra Palomino & Alana Yao on March 6, 2020.
//

#include "account.h"
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

using namespace std;
// displays account info and final fund balances
ostream& operator<<(ostream& out, const Account& other) {
    out << other.firstName << " " << other.lastName
        << " Account ID:" << other.accID << "\n";

    for (int i = 0; i < 10; i++) {
        out << "\t" << other.acctFunds[i].fundName << ": "
            << other.acctFunds[i].balance << "\n";
    }
    return out;
}

// creates account with name, lastname and accID
Account::Account(string lastName, string firstName, int accID) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->accID = accID;
    string name[] = {
        "Money Market",      "Prime Money Market", "Short-Term Bond",
        "500 Index Fund",    "Capital Value Fund", "Growth Equity Fund",
        "Growth Index Fund", "Value Fund",         "Value Stock Index"};
    for (int i = 0; i < 10; i++) {
        acctFunds[i].fundName = name[i];
    }
}

// destructor
Account::~Account() {}

// deposits amount into fund type of account
bool Account::deposit(int amt, int type) {
    // deposit amount
    acctFunds[type].balance += amt;

    return true;
}

// withdraws amount from fund type
bool Account::withdraw(int amt, int type) {
    // checks if amount is too high
    if (amt > acctFunds[type].balance) {
        return false;
    }
    
    // else, continue to withdraw from fund
    acctFunds[type].balance -= amt;

    return true;
}

// transfers amount into one fund type to another of the same account or other
bool Account::transfer(Account* other, int amt, int type, int oType) {
    // check if account has enough to withdraw
    if (!withdraw(amt, type)) { 
        return false;
    }

    withdraw(amt, type); // yes, withdraw from account
    other->deposit(amt, oType); // deposit to other account

    return true;
}

// displays history for account or single fund
void Account::displayTrans(int fund) const {
    cout << "Displaying Transaction History for " << firstName << " "
         << lastName;
    if (fund == -1) { // if no fund specified, display all histories
        cout << " by fund." << endl;
        for (Fund a : acctFunds) {
            cout << a.fundName << ": $" << a.balance << endl;
            for (int i = 0; i < a.fundRecord.size(); i++) {
                cout << "\t" << a.fundRecord[i] << endl;
            }
        }
    } else {
        cout << "'s " << acctFunds[fund].fundName << ": $"
             << acctFunds[fund].balance << endl;
        for (int i = 0; i < acctFunds[fund].fundRecord.size(); i++) {
            cout << "\t" << acctFunds[fund].fundRecord[i] << endl;
        }
    }
}

// helper function that records transactions to each fund
void Account::recordTrans(string& transaction, int num) {
    acctFunds[num].fundRecord.push_back(transaction);
}

// returns ID of this account
int Account::getID() const { return accID; }

// returns client first name of this account
string Account::getFirst() const { return firstName; }

// returns client last name of this account
string Account::getLast() const { return lastName; }
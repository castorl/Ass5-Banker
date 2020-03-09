//
// Created by <Name> on <Date>.
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
    string trans = "D " + to_string(accID) + to_string(type) + " " ;
    trans += to_string(amt);
    recordTrans(trans,type); 
    acctFunds[type].balance += amt;
    return true;
}

// withdraws ammunt from fund type
bool Account::withdraw(int amt, int type) {
    string trans;
    // checks if amount is too high
    if (amt > acctFunds[type].balance) {
        //calculate amount needed to cover the shortage
        int extra = -1 * (acctFunds[type].balance - amt); //make it positive
        int type2;
        if(type == 0 || type == 1){
            if(type == 0){
                type2 = 1;
                if(withdraw(extra, type2)){
                    cout << "Here 0:" << endl; //debug
                    deposit(extra,type);
                    withdraw(amt, type);
                    return true;
                }
            }
            else{
                type2 = 0;
                if(withdraw(extra, type2)){
                    cout << "Here 1:" << endl; //debug
                    deposit(extra,type);
                    withdraw(amt, type);
                    return true;
                }
            }
        }
        if(type == 2 || type == 3){
            if(type == 2){
                type2 = 3;
                if(withdraw(extra, type2)){
                    cout << "Here 2:" << endl; //debug
                    deposit(extra,type);
                    withdraw(amt, type);
                    return true;
                }
            }
            else{
                type2 = 2;
                if(withdraw(extra, type2)){
                    cout << "Here 3:" << endl; //debug
                    deposit(extra,type);
                    withdraw(amt, type);
                    return true;
                }
            }
        }
        trans = "W " + to_string(accID) + to_string(type) + " " ;
        trans += to_string(amt) + " FAILED";
        recordTrans(trans,type);
        cout << "Error, attempting to take out more than available balance.";
        return false;
    }

    trans = "W " + to_string(accID) + to_string(type) + " " ;
    trans += to_string(amt);
    recordTrans(trans,type);
    acctFunds[type].balance -= amt;
    return true;
}

// transfers amount into one fund type to another of the same account or other
bool Account::transfer(Account* other, int amt, int type, int oType) {
    string trans;
    // check if account has enough to withdraw
    if (other->withdraw(amt, type)) {
        trans = "T " + to_string(this->accID) + to_string(type)+ + " " ;
        trans += to_string(amt) + " " + to_string(other->accID) + to_string(type);
        recordTrans(trans,type);
        return deposit(amt, oType); // deposit to other account
    }
    trans = "T " + to_string(this->accID) + to_string(type)+ + " " ;
    trans += to_string(amt) + " " + to_string(other->accID) + to_string(type) + " FAILED";
    recordTrans(trans,type);
    return false;
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

void Account::recordTrans(string& transaction, int num) {
    acctFunds[num].fundRecord.push_back(transaction);
}

//returns ID
int Account::getID() const {
    return this->accID;
}


//return first name
string Account::getFirst() const{
    return this->firstName;
}

//returns lastname
string Account::getLast() const{
    return this->lastName;
}

//returns balance
int Account::getBalance(int fund) const {
    return acctFunds[fund].balance;
}

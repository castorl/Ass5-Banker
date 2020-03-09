//
// Created by <Name> on <Date>.
//
// Types of funds
// 0: Money Market
/*1: Prime Money Market
  2: Long-Term Bond
  3: Short-Term Bond
  4: 500 Index Fund
  5: Capital Value Fund
  6: Growth Equity Fund
  7: Growth Index Fund
  8: Value Fund
  9: Value Stock Index*/

#pragma once

#include <array>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

using namespace std;

const int MAX = 10;
class Account {
    // displays accounts first name, last name, account ID, and balances in each
    // fund
    friend ostream& operator<<(ostream& out, const Account& other);

public:
    // creates account with first, last, and accID
    explicit Account(string lastName, string firstName, int accID);

    // destructor
    virtual ~Account();


    // deposits amount into fund type of account
    bool deposit(int amt, int type);

    // withdraws amount from fund type
    bool withdraw(int amt, int type);

    // transfers amount into one fund type to another of the same account or
    // other
    bool transfer(Account* other, int amt, int type, int oType);

    // dipslays transaction history
    void displayTrans(int fund) const;

    //returns ID number
    int getID() const;

    //returns first name
    string getFirst() const;

    //returns last name
    string getLast() const;

    //returns balance
    int getBalance(int fund) const;

    //helper function to execute exception
    bool withdrawExcerption(int amt, int fund, int fund2, int extra);

private:
    // Fund has its own properties
    struct Fund {
        // name of fun
        string fundName;
        // balance for specific fund
        int balance;
        // list to record transactions for that fund
        vector<string> fundRecord;
    };

    // array of funds to keep track of everything
    Fund acctFunds[MAX];

    // name of account
    string firstName;
    string lastName;

    // account id number that links with the name of the account
    // 1000<= ID <= 9999
    int accID;

    // helper function that records transcations
    void recordTrans(string& transaction, int num);
};

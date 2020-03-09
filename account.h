//
// Created by Melanie Alexandra Palomino & Alana Yao on March 6, 2020.
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
    explicit Account(string lastName = nullptr, string firstName = nullptr, int accID = 0);

    // destructor
    virtual ~Account();

    // creates funds for new account
    bool openAccount(Account* account);

    // deposits amount into fund type of account
    bool deposit(int amt, int type);

    // withdraws ammunt from fund type
    bool withdraw(int amt, int type);

    // transfers amount into one fund type to another of the same account or
    // other
    bool transfer(Account* other, int amt, int type, int oType);

    // dipslays transaction history
    void displayTrans(int fund) const;

    // returns account ID
    int getID() const;

    // returns client first name
    string getFirst() const;

    // returns client last name
    string getLast() const;

    // helper function that records transcations to each fund
    void recordTrans(string& transaction, int num);
    
  private:
    // Fund has its own properties
    struct Fund {
        // name of fun
        string fundName;
        // balance for specific fund
        int balance = 0;
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
};

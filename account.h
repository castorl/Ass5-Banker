//
// Created by <Name> on <Date>.
//
//Types of funds 
//0: Money Market
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

#include <ostream>
#include <iostream> 
#include <string> 

using namespace std; 

class Account {
  public:
  // displays accounts first name, last name, account ID, and balances in each fund
  friend ostream& operator<<(ostream& out, const Account& other);
  //default constructor
  //Should we maybe make it explicit?
  Account();

  //creates account with first, last, and accID
	Account(string lastName, string firstName, int accID);

  // destructor
	virtual ~Account();
	
  //opens accounts 
  bool openAccount(stringstream& stream); 

  //deposits amount into fund type of account
	bool deposit(int amt, Funds type); 
	
  //transfers amount into one fund type to another of the same account or other
	bool transfer(Account* other, int amt, Funds type, Funds oType); 

  //withdraws ammunt from fund type
  bool withdraw(int amt, Funds type);

  //dipslays transaction history 
  void displayTrans(Funds fund) const; 

  //int getAccID() const; 
  
  //string getLast() const; 

  //string getFirst() const; 

  private:
  //name of account
  string firstName;
	string lastName;

  //account id number that links with the name of the account
  //1000<= ID <= 9999
  int accID;

  enum Funds{
      MoneyMarket,
      PrimeMoneyMarket,
      LongTermBond,
      ShortTermBond,
      IndexFund,
      CapitalValueFund,
      GrowthEquityFund,
      GrowthIndexFund,
      ValueFund,
      ValueStockIndex
  };
};



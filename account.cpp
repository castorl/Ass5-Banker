//
// Created by <Name> on <Date>.
//

#include "account.h"
#include <iostream>
#include <ostream>
#include <string>

using namespace std; 

ostream& operator<<(ostream& out, const Account& other);
  //default constructor
  //Should we maybe make it explicit?
Account::Account(){}

//creates account with name, lastname and accID
Account::Account(string lastName, string firstName, int accID){
  this->firstName = firstName; 
  this-> lastName = lastName; 
  this-> accID = accID;
}

// destructor
Account::~Account(){}

//creates new account 
bool Account::openAccount(stringstream& ss){
  //fill information from ss to last, first, ID 
  //check if account already exists 
      //no, then create account 
      //yes, print error 
  return false; 
}
  //sectioned >> lastname >> first >> ID; 
    //  account = new Account(lastname,first,ID);

//deposits amount into fund type of account
bool Account::deposit(int amt, Funds type){
  //deposit amount 
  //record transaction if valid
  return false; 
}
	
//transfers amount into one fund type to another of the same account or other
bool Account::transfer(Account* other, int amt, Funds type, Funds oType){
  //check if account has enough to withdraw 
    //yes, then deposit amount into other fund 
  //record transaction if valid
  return false; 
}

//withdraws ammunt from fund type
bool Account::withdraw(int amt, Funds type){
  //checks if amount is too high 
     //if so check type of fund to run exception Money Markey and other bond Funds
      //else, print error 
 //else, continue to withdraw from fund 
 //record transaction if valid
  return false; 
}

//displays history for account or single fund
void Account::displayTrans(Funds fund) const {
    //checks if fund type declared
    //if yes, display history of that fund
    //if not then display for all accounts
}





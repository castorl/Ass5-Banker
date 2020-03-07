//
// Created by <Name> on <Date>.
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
#include "accounttree.h"
#include "account.h"
#include "bank.h"
#include <queue>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std; 

// constuctor for bank 
Bank::Bank(){}

// destructor for bank 
Bank::~Bank(){
  //nothing to delete
}

// Function calls function to add transactions to queue
// Calls helper functions to processes transactions
void Bank::processTransactions(const string& fileName) {
  // call helper funciton to add and create structs
  addToQueue(fileName); 
  // transClassification();
}

// process file's lines as transactions and add to queue
// throws invalid_argument exception if fileName not found
void Bank::addToQueue(const string& fileName) {
  // create file reader 
  ifstream inFile;
  inFile.open(fileName);
   
  if(!inFile) {
    throw invalid_argument("Invalid file name!");
  }

  string line;
  char type; 
  string lastName;
  string firstName;
  int acctNum;
  int acctNum2;
  int amt;
  int fund;
  int fund2;


  // while not end of file
  // add transactions to queue
  while(!inFile.eof()) {
    getline(inFile, line);//check first letter 
    stringstream s(line);    
    s >> type; 
    
    switch(type) {
      case 'O': // open account
        s >> lastName >> firstName >> acctNum;

        Action newAcct = {.transType = type, .last = lastName, .first = firstName, .acctTo = acctNum};

        transactionsQ.push(newAcct);
        break;
      case 'D': // deposit
        s >> acctNum >> amt;
        fund = acctNum % 10; 
        acctNum = acctNum /10;

        Action deposit = {.transType = type, .acctTo = acctNum, .amount = amt, .fundTo = fund};

        transactionsQ.push(deposit);
        break;
      case 'W': // withdraw
        s >> acctNum >> amt;
        fund = acctNum % 10; 
        acctNum = acctNum /10;

        Action withdraw = {.transType = type, .acctFrom = acctNum, .amount = amt, .fundFrom = fund};
        
        transactionsQ.push(withdraw);
        break;
      case 'T': // transfer
        s >> acctNum >> amt >> acctNum2; 
        fund = acctNum % 10; 
        acctNum = acctNum /10;
        fund2 = acctNum2 % 10; 
        acctNum2 = acctNum2 /10;

        Action transfer = {.transType = type, .acctTo = acctNum, .acctFrom = acctNum2, .amount = amt, .fundFrom = fund, .fundTo = fund2};

        transactionsQ.push(transfer);
        break;
      case 'H': // display history
        s >> acctNum; 
        if(acctNum > 9999){ // display history of specific fund
          fund = acctNum % 10; 
          acctNum = acctNum /10;
        } else { // display history of whole account
          fund = -1; // no fund specified
        }
        Action history = {.acctTo = acctNum, .fundFrom = .fund};
        
        transactionsQ.push(history);
        break;
    }
  }

  inFile.close();
}

// helper function that executes transactions, uses switch case to decide 
// reminder to delete the structs after taking them from queue
void Bank::processQueue(){
  bool check = false; 
  // create account pointer 
  Account* account = nullptr; 
  Account* account2 = nullptr; 
  string first,lastname; 
  int ID, amt, fundNum, ID2, fundNum2; 
  Funds fundType, fundType2; 
  // keeps track of errors 
  bool success = false; 
   // start switch case
  switch(type){ 
    case 'O': // open new account
      break;
    case 'D': // deposit
      break; 
    case 'W': // withdraw
      break; 
    case 'T': // transfer
      break;  
    case 'H': // display transaction history
      
      break;  
    default: // incorrect transaction type
      cout << "Improper transaction type" << endl;
      break;  
  }
}

// displays accounts' fund balances
void Bank::displayAllBankBalances() const {}


/*
// helper function that executes transactions, uses switch case to decide 
// reminder to delete the structs after taking them from queue
void Bank::processQueue(){
  bool check = false; 
  // create account pointer 
  Account* account = nullptr; 
  Account* account2 = nullptr; 
  string first,lastname; 
  int ID, amt, fundNum, ID2, fundNum2; 
  Funds fundType, fundType2; 
  // keeps track of errors 
  bool success = false; 
   // start switch case
  switch(type){ 
    // open new account
    case 'O':
      break;
    // deposit 
    case 'D': 
      
      success = account->deposit(account,amt,fundType); 
      break; 
    // withdraw
    case 'W':
      s >> ID >> amt; 
      //set fundType
      fundNum = ID % 10; 
      ID = ID/10; 
      success = account->withdraw(amt,fundType);
      break; 
    // transfer
    case 'T':
      s >> ID >> amt >> ID2; 
      //set fundType
      fundNum = ID % 10; 
      ID = ID/10;
      fundNum2 = ID2 % 10;  
      ID2 = ID2/10; 
      success = account->transfer(account2,amt,fundType,fundType2); 
      break;  
    // history 
    case 'H':
      
      break;  
    default: // incorrect transaction type
      cout << "Improper transaction type" << endl;
      break;  
  }
}

//checks account ID validation 
bool Bank::checkData(stringstream& s,int& amt, int& fund, int& ID, int& ID2, int& fund2){
   s >> ID >> amt; 
   if(ID > 99999){
      return false; 
   }
   fund = ID % 10; 
   ID = ID/10; 
   //if stream is not done yet 
   if(!s.eof()){
     s >> ID2; 
     fund2 = ID2 % 10; 
     ID2 = ID2/10; 
   }
  return true; 
}


//helper function to execute transcations 
void Bank::transClassification(){
  struct Action; 
  while(!transactionsQ.empty()){
      //set value of front in queue to string
      Action = {transactionsQ.front()}; 
      //delete front from queue 
      transactionsQ.pop(); 
      //take the first character of line
      stringstream s(line);
      s >> transactionType; 
      processHelper(transactionType,line, s); 
  }
}
*/
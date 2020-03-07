//
// Created by <Name> on <Date>.
//

#include "bank.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main(int argc, char* argv[]) {
  Bank bank;

  for (int i = 1; i < argc; i++) {
    cout << "The command line argument(s) was " << argv[i] << endl;
    string fileName = argv[i];
    
    bool fileExists = false;
    while(!fileExists) {
      try {
        bank.processTransactions(fileName);
        fileExists = true;
      } catch (const invalid_argument& e) {
        cout << e << endl;
      }
    }
  }
  
  displayAllBankBalances();
  
  cout << "Done" << endl;

  return 0;
}
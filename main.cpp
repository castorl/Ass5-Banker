//
// Created by Melanie Alexandra Palomino & Alana Yao on March 6, 2020.
//

#include "bank.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    Bank bank; /*
    for (int i = 1; i < argc; i++) {
        cout << "The command line argument(s) was " << argv[i] << endl;
        string fileName = argv[i];

        bank.processTransactions(fileName)
        bank.displayAllBankBalances();
    }
    */

    bank.processTransactions("BankTransIn.txt");

    cout << "Processing Done. Final Balances." << endl;
    bank.displayAllBankBalances();

    cout << "Done" << endl;

    return 0;
}
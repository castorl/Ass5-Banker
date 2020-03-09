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

        try {
            bank.processTransactions(fileName);
        } catch (const invalid_argument& e) {
            cout << fileName << "could not be found." << endl;
        }

        bank.displayAllBankBalances();
    }
    */

    try {
        bank.processTransactions("BankTransIn.txt");
    } catch (const invalid_argument& e) {
        //cout << fileName << "could not be found." << endl;
    }

    cout << "Processing Done. Final Balances." << endl;
    bank.displayAllBankBalances();

    cout << "Done" << endl;

    return 0;
}
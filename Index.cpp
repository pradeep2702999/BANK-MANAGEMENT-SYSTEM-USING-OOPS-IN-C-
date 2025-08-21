#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

// Utility to get current timestamp
string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Bank Account Class
class Account {
private: 
    string accountHolder;
    int accountNumber;
    double balance;
    string accountType;
    string pin;
    vector<string> transactionHistory;

public:
    Account(string holder, int accNumber, double initialBalance, string type, string pinCode) {
        accountHolder = holder;
        accountNumber = accNumber;
        balance = initialBalance;
        accountType = type;
        pin = pinCode;
    }

    // Getters
    string getAccountHolder() const { return accountHolder; }
    string getAccountType() const { return accountType; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    vector<string> getTransactionHistory() const { return transactionHistory; }

    // PIN Validation
    bool validatePIN(string enteredPIN) { return pin == enteredPIN; }

    // Deposit
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.push_back(getCurrentTime() + " - Deposited: $" + to_string(amount));
            cout << "$" << amount << " deposited successfully.\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    // Withdraw
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactionHistory.push_back(getCurrentTime() + " - Withdrawn: $" + to_string(amount));
            cout << "$" << amount << " withdrawn successfully.\n";
        } else {
            cout << "Invalid or insufficient amount.\n";
        }
    }

    // Apply Interest
    void applyInterest() {
        if (accountType == "Savings") {
            double rate = 0.03;
            double interest = balance * rate;
            balance += interest;
            transactionHistory.push_back(getCurrentTime() + " - Interest Applied: $" + to_string(interest));
            cout << "Interest of $" << interest << " applied.\n";
        } else {
            cout << "No interest for Checking accounts.\n";
        }
    }

    // Display account
    void displayAccount() {
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Transaction History:\n";
        for (const auto& txn : transactionHistory) {
            cout << txn << endl;
        }
    }
};

// Bank Class
class Bank {
private:
    vector<Account> accounts;

public:
    void addAccount(string holder, int accNumber, double initialBalance, string type, string pinCode) {
        accounts.emplace_back(holder, accNumber, initialBalance, type, pinCode);
    }

    Account* findAccount(int accNumber) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNumber) {
                return &acc;
            }
        }
        return nullptr;
    }

    void displaySpecificAccount(int accNumber, const string& pinCode) {
        Account* acc = findAccount(accNumber);
        if (acc != nullptr && acc->validatePIN(pinCode)) {
            acc->displayAccount();
        } else {
            cout << "Account not found or invalid PIN.\n";
        }
    }

    void saveToCSV(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error writing to file.\n";
            return;
        }

        file << "AccountNumber,AccountHolder,AccountType,Balance,TransactionHistory\n";

        for (const auto& acc : accounts) {
            string history;
            auto txns = acc.getTransactionHistory();
            for (size_t i = 0; i < txns.size(); ++i) {
                history += txns[i];
                if (i < txns.size() - 1) history += "; ";
            }

            file << acc.getAccountNumber() << ","
                 << "\"" << acc.getAccountHolder() << "\","
                 << acc.getAccountType() << ","
                 << fixed << setprecision(2) << acc.getBalance() << ","
                 << "\"" << history << "\"\n";
                 
        }

        file.close();
        cout << "Accounts saved to " << filename << " successfully.\n";
    }
};

// Main Program
int main() {
    Bank myBank;

    // Preload 3 accounts
    myBank.addAccount("RAGHU", 1001, 1500.0, "Savings", "1234");
    myBank.addAccount("RAJU", 1002, 2000.0, "Checking", "5678");
    myBank.addAccount("SHIVA", 1003, 2500.0, "Savings", "9012");

    int choice, accNumber;
    string pinCode;
    double amount;

    while (true) {
        cout << "\n=== Bank Management System ===\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Apply Interest\n";
        cout << "4. Create New Account\n";
        cout << "5. Display Specific Account\n";
        cout << "6. Save Accounts to CSV\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account number: ";
                cin >> accNumber;
                cout << "Enter PIN: ";
                cin >> pinCode;
                if (Account* acc = myBank.findAccount(accNumber)) {
                    if (acc->validatePIN(pinCode)) {
                        cout << "Enter deposit amount: ";
                        cin >> amount;
                        acc->deposit(amount);
                    } else {
                        cout << "Invalid PIN.\n";
                    }
                } else {
                    cout << "Account not found.\n";
                }
                break;

            case 2:
                cout << "Enter account number: ";
                cin >> accNumber;
                cout << "Enter PIN: ";
                cin >> pinCode;
                if (Account* acc = myBank.findAccount(accNumber)) {
                    if (acc->validatePIN(pinCode)) {
                        cout << "Enter withdrawal amount: ";
                        cin >> amount;
                        acc->withdraw(amount);
                    } else {
                        cout << "Invalid PIN.\n";
                    }
                } else {
                    cout << "Account not found.\n";
                }
                break;

            case 3:
                cout << "Enter account number: ";
                cin >> accNumber;
                cout << "Enter PIN: ";
                cin >> pinCode;
                if (Account* acc = myBank.findAccount(accNumber)) {
                    if (acc->validatePIN(pinCode)) {
                        acc->applyInterest();
                    } else {
                        cout << "Invalid PIN.\n";
                    }
                } else {
                    cout << "Account not found.\n";
                }
                break;

            case 4: {
                string name, type, isSavings;
                cout << "Enter account holder name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter account number: ";
                cin >> accNumber;
                cout << "Enter initial deposit: ";
                cin >> amount;

                cout << "Is this a savings account? (yes/no): ";
                cin >> isSavings;
                if (isSavings == "yes" || isSavings == "Yes") {
                    type = "Savings";
                } else {
                    type = "Checking";
                }

                cout << "Set a 4-digit PIN: ";
                cin >> pinCode;
                myBank.addAccount(name, accNumber, amount, type, pinCode);
                cout << "Account created.\n";
                break;
            }

            case 5:
                cout << "Enter account number: ";
                cin >> accNumber;
                cout << "Enter PIN: ";
                cin >> pinCode;
                myBank.displaySpecificAccount(accNumber, pinCode);
                break;

            case 6:
                myBank.saveToCSV("accounts.csv");
                break;

            case 7:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

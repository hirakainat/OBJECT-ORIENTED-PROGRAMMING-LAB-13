#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Custom exception classes
class InvalidAmountException : public runtime_error {
public:
    InvalidAmountException() : runtime_error("Invalid amount entered.") {}
};

class InsufficientFundsException : public runtime_error {
public:
    InsufficientFundsException() : runtime_error("Insufficient funds for this operation.") {}
};

// BankAccount class definition
class BankAccount {
private:
    double balance;
    string accountNumber;

public:
    // Constructor
    BankAccount(string accNum, double initialBalance = 0.0) {
        accountNumber = accNum;
        if (initialBalance < 0) {
            throw InvalidAmountException();
        }
        balance = initialBalance;
    }

    // Deposit function
    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        balance += amount;
        cout << "Deposit successful. New balance: " << balance << endl;
    }

    // Withdraw function
    void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        if (amount > balance) {
            throw InsufficientFundsException();
        }
        balance -= amount;
        cout << "Withdrawal successful. New balance: " << balance << endl;
    }

    // Transfer function
    void transfer(BankAccount& other, double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        if (amount > balance) {
            throw InsufficientFundsException();
        }
        balance -= amount;
        other.balance += amount;
        cout << "Transfer successful. Your new balance: " << balance << endl;
    }

    // Check balance
    void checkBalance() const {
        cout << "Account " << accountNumber << " balance: " << balance << endl;
    }
};

// Global processTransaction function
void processTransaction(BankAccount& acc1, BankAccount& acc2) {
    try {
        int choice;
        cout << "Choose an operation: 1. Deposit  2. Withdraw  3. Transfer  4. Check Balance\n";
        cin >> choice;

        if (choice == 1) { // Deposit
            double amount;
            cout << "Enter deposit amount: ";
            cin >> amount;
            acc1.deposit(amount);
        }
        else if (choice == 2) { // Withdraw
            double amount;
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            acc1.withdraw(amount);
        }
        else if (choice == 3) { // Transfer
            double amount;
            cout << "Enter transfer amount: ";
            cin >> amount;
            acc1.transfer(acc2, amount);
        }
        else if (choice == 4) { // Check balance
            acc1.checkBalance();
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
    catch (InvalidAmountException& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (InsufficientFundsException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// Main function
int main() {
    try {
        // Create bank accounts
        BankAccount acc1("12345", 1000);
        BankAccount acc2("67890", 500);

        int repeat = 1;
        while (repeat) {
            cout << "Choose account to operate on (1 for Account 1, 2 for Account 2): ";
            int accountChoice;
            cin >> accountChoice;

            if (accountChoice == 1) {
                processTransaction(acc1, acc2);
            }
            else if (accountChoice == 2) {
                processTransaction(acc2, acc1);
            }
            else {
                cout << "Invalid account choice." << endl;
            }

            cout << "Do you want to perform another transaction? (1 for Yes, 0 for No): ";
            cin >> repeat;
        }
    }
    catch (exception& e) {
        cout << "An error occurred: " << e.what() << endl;
    }

    return 0;
}

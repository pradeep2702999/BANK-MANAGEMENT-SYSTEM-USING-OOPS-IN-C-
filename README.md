🏦 Bank Management System (C++)

This is a console-based Bank Management System implemented in C++ using Object-Oriented Programming (OOP) principles.  
It allows users to create and manage bank accounts, perform transactions, apply interest, and export account details to a CSV file for permanent storage.



✨ Features

- Account Creation
  - Create Savings or Checking accounts.
  - Set a 4-digit PIN for security.

- Deposit & Withdraw
  - Secure deposit and withdrawal operations after PIN verification.
  - Transaction logs maintained with **timestamps.

- Interest Application
  - Savings accounts earn 3% interest.
  - Checking accounts have no interest.

- Transaction History
  - Every deposit, withdrawal, and interest application is stored with the date & time.

- Account Viewing
  - View specific account details securely (with PIN authentication).

- Data Persistence
  - Save all accounts and transaction history into a **CSV file** (`accounts.csv`).



🛠️ Technologies Used
- **C++** (OOP, STL, File Handling)
- **CSV Export** for data persistence
- <iomanip>, <fstream>, <sstream> for formatting & file operations
- Timestamps using `<ctime>`



🚀 How to Run

1. Compile the program

   g++ main.cpp -o bank_system

2. Run the program

   ./bank_system



📋 Menu Options

When you run the program, you’ll see:

=== Bank Management System ===
1. Deposit Money
2. Withdraw Money
3. Apply Interest
4. Create New Account
5. Display Specific Account
6. Save Accounts to CSV
7. Exit


---

📊 Sample accounts (preloaded)

Account Holder	Account Number	Type	Balance

RAGHU	1001	Savings	1500.0
RAJU	1002	Checking	2000.0
SHIVA	1003	Savings	2500.0



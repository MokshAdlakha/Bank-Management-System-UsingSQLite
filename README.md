# 🏦 Bank Management System using SQLite (C++)

This is a console-based Bank Management System built in **C++** with **SQLite database integration**.  
It allows users to create, manage, search, deposit to, and withdraw from bank accounts, with all data stored persistently in an SQLite database file.

---

## 🚀 Features

- Create new accounts
- View all existing accounts
- Deposit money
- Withdraw money with balance check
- Search account by account number
- Delete an account
- Data stored using **SQLite** (`bank.db`)

---

## 🛠️ Technologies Used

- C++
- SQLite (`sqlite3.c` and `sqlite3.h`)
- Dev-C++ or VS Code (recommended)
- GCC / MinGW Compiler

  ---

## 🧪 How to Run

### ✅ Option 1: Using Dev-C++

1. Download and extract the project folder.
2. Open `Bank_OOP.cpp` in Dev-C++.
3. Add `sqlite3.c` to the project:  
   `Project → Add to Project → sqlite3.c`
4. Compile & Run:  
   `Execute → Compile & Run`

> Make sure `sqlite3.c` and `sqlite3.h` are in the same directory.

---

### ✅ Option 2: Using VS Code with g++

1. Make sure `g++` is installed.
2. Navigate to project folder in terminal.
3. Compile the program:

🔒 Note
bank.db will be auto-generated on first run.

📸 Sample Menu
-- Bank Management System (SQLite Version) --
1. Create Account
2. Display Accounts
3. Deposit
4. Withdraw
5. Search
6. Delete
7. Exit

📜 License
This project is open-source and free to use for educational purposes.

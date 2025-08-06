#include <iostream>
#include "sqlite3.h"
using namespace std;

sqlite3* db;

bool executeSQL(const string& sql) {
    char* errmsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
        cerr << "SQLite Error: " << errmsg << endl;
        sqlite3_free(errmsg);
        return false;
    }
    return true;
}

void createTable() {
    string sql = "CREATE TABLE IF NOT EXISTS ACCOUNT("
                 "ACCNUMBER INTEGER PRIMARY KEY, "
                 "NAME TEXT NOT NULL, "
                 "BALANCE REAL NOT NULL);";
    executeSQL(sql);
}

void createAccount() {
    int accNum;
    string name;
    double balance;

    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Initial Balance: ";
    cin >> balance;

    string sql = "INSERT INTO ACCOUNT (ACCNUMBER, NAME, BALANCE) VALUES (" +
                 to_string(accNum) + ", '" + name + "', " + to_string(balance) + ");";

    if (executeSQL(sql))
        cout << "Account created!\n";
}

void displayAccounts() {
    string sql = "SELECT * FROM ACCOUNT;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        cout << "\n-- All Accounts --\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int accNum = sqlite3_column_int(stmt, 0);
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            double balance = sqlite3_column_double(stmt, 2);

            cout << "Acc No: " << accNum << ", Name: " << name << ", Balance: " << balance << endl;
        }
    }
    sqlite3_finalize(stmt);
}

void depositMoney(int accNum, double amount) {
    string sql = "UPDATE ACCOUNT SET BALANCE = BALANCE + " + to_string(amount) +
                 " WHERE ACCNUMBER = " + to_string(accNum) + ";";
    if (executeSQL(sql))
        cout << "Deposit successful!\n";
}

void withdrawMoney(int accNum, double amount) {
    string checkSql = "SELECT BALANCE FROM ACCOUNT WHERE ACCNUMBER = " + to_string(accNum) + ";";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, checkSql.c_str(), -1, &stmt, nullptr) == SQLITE_OK &&
        sqlite3_step(stmt) == SQLITE_ROW) {

        double balance = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);

        if (balance >= amount) {
            string sql = "UPDATE ACCOUNT SET BALANCE = BALANCE - " + to_string(amount) +
                         " WHERE ACCNUMBER = " + to_string(accNum) + ";";
            if (executeSQL(sql))
                cout << "Withdrawal successful!\n";
        } else {
            cout << "Insufficient balance!\n";
        }
    } else {
        cout << "Account not found!\n";
        sqlite3_finalize(stmt);
    }
}

void searchAccount(int accNum) {
    string sql = "SELECT NAME, BALANCE FROM ACCOUNT WHERE ACCNUMBER = " + to_string(accNum) + ";";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK &&
        sqlite3_step(stmt) == SQLITE_ROW) {

        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        double balance = sqlite3_column_double(stmt, 1);
        cout << "Found: " << name << ", Balance: " << balance << endl;
    } else {
        cout << "Account not found!\n";
    }

    sqlite3_finalize(stmt);
}

void deleteAccount(int accNum) {
    string sql = "DELETE FROM ACCOUNT WHERE ACCNUMBER = " + to_string(accNum) + ";";
    if (executeSQL(sql))
        cout << "Account deleted.\n";
}

int main() {
    int choice, accNum;
    double amount;

    if (sqlite3_open("bank.db", &db) != SQLITE_OK) {
        cerr << "Error opening database.\n";
        return 1;
    }

    createTable();

    do {
        cout << "\n-- Bank Management System (SQLite Version) --\n";
        cout << "1. Create Account\n2. Display Accounts\n3. Deposit\n4. Withdraw\n5. Search\n6. Delete\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3:
                cout << "Enter Acc No: "; cin >> accNum;
                cout << "Amount to deposit: "; cin >> amount;
                depositMoney(accNum, amount); break;
            case 4:
                cout << "Enter Acc No: "; cin >> accNum;
                cout << "Amount to withdraw: "; cin >> amount;
                withdrawMoney(accNum, amount); break;
            case 5:
                cout << "Enter Acc No: "; cin >> accNum;
                searchAccount(accNum); break;
            case 6:
                cout << "Enter Acc No: "; cin >> accNum;
                deleteAccount(accNum); break;
            case 7:
                cout << "Exiting...\n"; break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    sqlite3_close(db);
    return 0;
}

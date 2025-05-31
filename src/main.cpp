#include "FinanceManager.h"
#include <iostream>
#include <limits>
#include <map>
#include <numeric>

// --- Helper Functions ---
void printTransaction(const Transaction& trans) {
    std::cout << "ID: " << trans.id << ", Date: " << trans.date << ", Amount: " << trans.amount
              << ", Category: " << trans.category << ", Desc: " << trans.description << std::endl;
}

template <typename T> T getValidatedInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid input. Please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Date getDateInput(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string date_str;
        std::getline(std::cin, date_str);
        try {
            return Date::fromString(date_str);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << " Please try again." << std::endl;
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// --- UI Functions ---
void addTransactionUI(FinanceManager& manager) {
    std::cout << "\n--- Add New Transaction ---\n";
    Date date = getDateInput("Enter date (YYYY-MM-DD): ");
    double amount = getValidatedInput<double>("Enter amount (+ for income, - for expense): ");
    std::string category = getStringInput("Enter category: ");
    std::string description = getStringInput("Enter description (optional): ");
    manager.addTransaction(date, amount, category, description);
    std::cout << "Transaction added successfully.\n";
}

void viewTransactionsUI(const FinanceManager& manager) {
    std::cout << "\n--- All Transactions ---\n";
    auto transactions = manager.getTransactions();
    if (transactions.empty()) {
        std::cout << "No transactions found.\n";
        return;
    }
    for (const auto& trans : transactions) {
        printTransaction(trans);
    }
}

void editTransactionUI(FinanceManager& manager) {
    std::cout << "\n--- Edit Transaction ---\n";
    size_t id = getValidatedInput<size_t>("Enter ID of transaction to edit: ");
    if (!manager.findTransactionById(id)) {
        std::cout << "Transaction with ID " << id << " not found.\n";
        return;
    }
    Date date = getDateInput("Enter new date (YYYY-MM-DD): ");
    double amount = getValidatedInput<double>("Enter new amount: ");
    std::string category = getStringInput("Enter new category: ");
    std::string description = getStringInput("Enter new description: ");
    if (manager.editTransaction(id, date, amount, category, description)) {
        std::cout << "Transaction updated successfully.\n";
    }
}

void deleteTransactionUI(FinanceManager& manager) {
    std::cout << "\n--- Delete Transaction ---\n";
    size_t id = getValidatedInput<size_t>("Enter ID of transaction to delete: ");
    if (manager.deleteTransaction(id)) {
        std::cout << "Transaction deleted successfully.\n";
    } else {
        std::cout << "Transaction with ID " << id << " not found.\n";
    }
}

void generateReportUI(const FinanceManager& manager) {
    std::cout << "\n--- Generate Report ---\n";
    Date start_date = getDateInput("Enter start date (YYYY-MM-DD): ");
    Date end_date = getDateInput("Enter end date (YYYY-MM-DD): ");

    double total_income = 0.0;
    double total_expense = 0.0;
    std::map<std::string, double> expenses_by_category;

    for (const auto& trans : manager.getTransactions()) {
        if (!(trans.date < start_date) && (trans.date < end_date || trans.date == end_date)) {
            if (trans.amount > 0) {
                total_income += trans.amount;
            } else {
                total_expense += trans.amount;
                expenses_by_category[trans.category] += trans.amount;
            }
        }
    }

    std::cout << "\n--- Report for " << start_date << " to " << end_date << " ---\n";
    std::cout << "Total Income: " << total_income << std::endl;
    std::cout << "Total Expense: " << total_expense << std::endl;
    std::cout << "Net Balance: " << total_income + total_expense << std::endl;
    std::cout << "\nExpenses by Category:\n";
    if (expenses_by_category.empty()) {
        std::cout << "  No expenses in this period.\n";
    } else {
        for (const auto& pair : expenses_by_category) {
            std::cout << "  - " << pair.first << ": " << pair.second << std::endl;
        }
    }
}

void printMenu() {
    std::cout << "\n===== Personal Finance Manager =====\n";
    std::cout << "1. Add Transaction\n";
    std::cout << "2. Edit Transaction\n";
    std::cout << "3. Delete Transaction\n";
    std::cout << "4. View All Transactions\n";
    std::cout << "5. Generate Report\n";
    std::cout << "0. Exit\n";
    std::cout << "====================================\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <data_file.csv>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    FinanceManager manager;

    try {
        manager.loadFromFile(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        // Continue with an empty manager
    }

    int choice;
    do {
        printMenu();
        choice = getValidatedInput<int>("Enter your choice: ");

        switch (choice) {
        case 1: addTransactionUI(manager); break;
        case 2: editTransactionUI(manager); break;
        case 3: deleteTransactionUI(manager); break;
        case 4: viewTransactionsUI(manager); break;
        case 5: generateReportUI(manager); break;
        case 0:
            std::cout << "Exiting and saving data...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    try {
        manager.saveToFile(filename);
        std::cout << "Data saved successfully to " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error saving data: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
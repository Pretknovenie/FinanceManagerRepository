#include "FinanceManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Transaction FinanceManager::addTransaction(const Date& date, double amount,
                                           const std::string& category,
                                           const std::string& description) {
    Transaction new_trans = {next_id_++, date, amount, category, description};
    transactions_.push_back(new_trans);
    return new_trans;
}

bool FinanceManager::editTransaction(size_t id, const Date& new_date, double new_amount,
                                     const std::string& new_category,
                                     const std::string& new_description) {
    for (auto& trans : transactions_) {
        if (trans.id == id) {
            trans.date = new_date;
            trans.amount = new_amount;
            trans.category = new_category;
            trans.description = new_description;
            return true;
        }
    }
    return false;
}

bool FinanceManager::deleteTransaction(size_t id) {
    auto it = std::remove_if(transactions_.begin(), transactions_.end(),
                             [id](const Transaction& trans) { return trans.id == id; });

    if (it != transactions_.end()) {
        transactions_.erase(it, transactions_.end());
        return true;
    }
    return false;
}

const Transaction* FinanceManager::findTransactionById(size_t id) const {
    for (const auto& trans : transactions_) {
        if (trans.id == id) {
            return &trans;
        }
    }
    return nullptr;
}

const std::vector<Transaction>& FinanceManager::getTransactions() const {
    return transactions_;
}

void FinanceManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // It's not an error if the file doesn't exist yet
        std::cerr << "Info: Data file not found. A new one will be created on exit."
                  << std::endl;
        return;
    }

    transactions_.clear();
    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;

        while (std::getline(ss, segment, ',')) {
            parts.push_back(segment);
        }

        if (parts.size() != 5) {
            throw std::runtime_error("CSV format error: Invalid number of columns in line: " +
                                     line);
        }

        try {
            Transaction trans;
            trans.id = std::stoull(parts[0]);
            trans.date = Date::fromString(parts[1]);
            trans.amount = std::stod(parts[2]);
            trans.category = parts[3];
            trans.description = parts[4];
            transactions_.push_back(trans);
        } catch (const std::exception& e) {
            throw std::runtime_error("CSV parsing error in line: " + line + " (" + e.what() +
                                     ")");
        }
    }
    updateNextId();
}

void FinanceManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing: " + filename);
    }

    file << "ID,Date,Amount,Category,Description\n";
    for (const auto& trans : transactions_) {
        file << trans.id << "," << trans.date.toString() << "," << trans.amount << ","
             << trans.category << "," << trans.description << "\n";
    }
}

void FinanceManager::updateNextId() {
    if (transactions_.empty()) {
        next_id_ = 1;
    } else {
        size_t max_id = 0;
        for (const auto& trans : transactions_) {
            if (trans.id > max_id) {
                max_id = trans.id;
            }
        }
        next_id_ = max_id + 1;
    }
}
#ifndef FINANCE_MANAGER_H
#define FINANCE_MANAGER_H

#include "Transaction.h"
#include <optional>
#include <string>
#include <vector>

/**
 * @class FinanceManager
 * @brief Manages all financial operations and data.
 *
 * This class is the core of the application, handling the storage,
 * manipulation, and analysis of transactions.
 */
class FinanceManager {
public:
    /**
     * @brief Adds a new transaction to the manager.
     * @param date The date of the transaction.
     * @param amount The transaction amount.
     * @param category The transaction category.
     * @param description An optional description.
     * @return The newly created Transaction object.
     */
    Transaction addTransaction(const Date& date, double amount, const std::string& category,
                               const std::string& description);

    /**
     * @brief Edits an existing transaction.
     * @param id The ID of the transaction to edit.
     * @param new_date The new date for the transaction.
     * @param new_amount The new amount.
     * @param new_category The new category.
     * @param new_description The new description.
     * @return True if the transaction was found and edited, false otherwise.
     */
    bool editTransaction(size_t id, const Date& new_date, double new_amount,
                         const std::string& new_category, const std::string& new_description);

    /**
     * @brief Deletes a transaction by its ID.
     * @param id The ID of the transaction to delete.
     * @return True if the transaction was found and deleted, false otherwise.
     */
    bool deleteTransaction(size_t id);

    /**
     * @brief Finds a transaction by its ID.
     * @param id The ID of the transaction to find.
     * @return A pointer to the transaction if found, nullptr otherwise.
     * @note The returned pointer is non-owning.
     */
    const Transaction* findTransactionById(size_t id) const;

    /**
     * @brief Retrieves all transactions.
     * @return A constant reference to the vector of all transactions.
     */
    const std::vector<Transaction>& getTransactions() const;

    /**
     * @brief Loads transactions from a CSV file.
     * @param filename The path to the CSV file.
     * @throws std::runtime_error on file I/O or parsing errors.
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Saves all transactions to a CSV file.
     * @param filename The path to the CSV file.
     * @throws std::runtime_error on file I/O errors.
     */
    void saveToFile(const std::string& filename) const;

private:
    std::vector<Transaction> transactions_; ///< Container for all transactions.
    size_t next_id_ = 1;                    ///< Counter for generating unique transaction IDs.

    /**
     * @brief Updates the next available ID based on current transactions.
     *
     * Ensures that new transactions always get a unique ID, even after
     * loading from a file.
     */
    void updateNextId();
};

#endif // FINANCE_MANAGER_H
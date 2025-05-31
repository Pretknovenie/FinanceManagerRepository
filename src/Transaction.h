#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Date.h"
#include <string>

/**
 * @struct Transaction
 * @brief Represents a single financial transaction.
 *
 * This struct holds all information related to a transaction, including its
 * unique ID, date, amount, category, and an optional description.
 */
struct Transaction {
    size_t id;                ///< Unique identifier for the transaction.
    Date date;                ///< The date of the transaction.
    double amount;            ///< The amount (positive for income, negative for expense).
    std::string category;     ///< The category of the transaction (e.g., "Food", "Salary").
    std::string description;  ///< An optional description of the transaction.
};

#endif // TRANSACTION_H
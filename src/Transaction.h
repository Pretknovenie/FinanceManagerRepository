#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Date.h"
#include <string>

/**
 * @struct Transaction
 * @brief Представляет единую финансовую транзакцию.
 *
 * Эта структура содержит всю информацию, связанную с транзакцией, включая ее
 * уникальный идентификатор, дату, сумму, категорию и необязательное описание.
 */
struct Transaction {
    size_t id;                ///< Уникальный идентификатор транзакции.
    Date date;                ///< Дата транзакции.
    double amount;            ///< Сумма (положительная для доходов, отрицательная для расходов).
    std::string category;     ///< Категория транзакции (например, «Еда», «Зарплата»).
    std::string description;  ///< Необязательное описание транзакции.
};

#endif // TRANSACTION_H
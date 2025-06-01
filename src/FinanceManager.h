#ifndef FINANCE_MANAGER_H
#define FINANCE_MANAGER_H

#include "Transaction.h"
#include <optional>
#include <string>
#include <vector>

/**
 * @class FinanceManager
 * @brief Управляет всеми финансовыми операциями и данными.
 *
 * Этот класс является ядром приложения, отвечающим за хранение,
 * обработку и анализ транзакций.
 */
class FinanceManager {
public:
    /**
     * @brief Добавляет новую транзакцию в менеджер.
     * @param date Дата транзакции.
     * @param amount Сумма транзакции.
     * @param category Категория транзакции.
     * @param description Описание (необязательное).
     * @return Вновь созданный объект транзакции.
     */
    Transaction addTransaction(const Date& date, double amount, const std::string& category,
                               const std::string& description);

    /**
     * @brief Редактирует существующую транзакцию.
     * @param id Идентификатор транзакции для редактирования.
     * @param new_date Новая дата транзакции.
     * @param new_amount Новая сумма.
     * @param new_category Новая категория.
     * @param new_description новое описание.
     * @return True, если транзакция была найдена и отредактирована, в противном случае — false.
     */
    bool editTransaction(size_t id, const Date& new_date, double new_amount,
                         const std::string& new_category, const std::string& new_description);

    /**
     * @brief Удаляет транзакцию по ее идентификатору.
     * @param id Идентификатор транзакции для удаления.
     * @return True, если транзакция была найдена и удалена, в противном случае — false.
     */
    bool deleteTransaction(size_t id);

    /**
     * @brief Находит транзакцию по ее идентификатору.
     * @param id Идентификатор транзакции, которую необходимо найти.
     * @return Указатель на транзакцию, если найден, в противном случае — nullptr.
     * @note Возвращенный указатель не является владеющим.
     */
    const Transaction* findTransactionById(size_t id) const;

    /**
     * @brief Извлекает все транзакции.
     * @return Константная ссылка на вектор всех транзакций.
     */
    const std::vector<Transaction>& getTransactions() const;

    /**
     * @brief Загружает транзакции из CSV-файла.
     * @param filename Путь к CSV-файлу.
     * @throws std::runtime_error при ошибках ввода-вывода файла или синтаксического анализа.
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Сохраняет все транзакции в CSV-файл.
     * @param filename Путь к CSV-файлу.
     * @throws std::runtime_error при ошибках ввода-вывода файла.
     */
    void saveToFile(const std::string& filename) const;

private:
    std::vector<Transaction> transactions_; ///< Контейнер для всех транзакций.
    size_t next_id_ = 1;                    ///< Счетчик для генерации уникальных идентификаторов транзакций.

    /**
     * @brief Обновляет следующий доступный идентификатор на основе текущих транзакций.
     *
     * Гарантирует, что новые транзакции всегда получают уникальный идентификатор,
     * даже после загрузки из файла.
     */
    void updateNextId();
};

#endif // FINANCE_MANAGER_H
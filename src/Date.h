#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

/**
 * @struct Date
 * @brief Показывает календарную дату.
 *
 * Эта структура хранит год, месяц и день в виде целых чисел и предоставляет
 * функциональные возможности для анализа, форматирования и сравнения.
 */
struct Date {
    int year;  ///< Компонент года.
    int month; ///< Компонент месяца (1-12).
    int day;   ///< Компонент дня (1-31).

    /**
     * @brief Конструктор по умолчанию. Инициализирует дату 0-0-0.
     */
    Date();

    /**
     * @brief Параметризованный конструктор.
     * @param y Год.
     * @param m Месяц.
     * @param d День.
     */
    Date(int y, int m, int d);

    /**
     * @brief Создает объект Date из строки. 
     * @param date_str Строка даты в формате «ГГГГ-ММ-ДД».
     * @return Объект Date.
     * @throws std::invalid_argument если формат строки некорректен.
     */
    static Date fromString(const std::string& date_str);

    /**
     * @brief Преобразует объект Date в строку.
     * @return Строковое представление даты в формате «ГГГГ-ММ-ДД».
     */
    std::string toString() const;

    /**
     * @brief Сравнивает два объекта Date на равенство.
     * @param other Другой объект Date для сравнения.
     * @return True если даты равны, в противном случае — false.
     */
    bool operator==(const Date& other) const;

    /**
     * @brief Сравнивает, является ли эта дата меньшей, чем другая.
     * @param other Другой объект Date для сравнения.
     * @return True, если эта дата раньше другой, в противном случае — false.
     */
    bool operator<(const Date& other) const;
};

/**
 * @brief Перегрузка для оператора выходного потока.
 * @param os Выходной поток.
 * @param date Объект Date для вывода.
 * @return Выходной поток.
 */
std::ostream& operator<<(std::ostream& os, const Date& date);

#endif // DATE_H

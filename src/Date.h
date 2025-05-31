#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

/**
 * @struct Date
 * @brief Represents a calendar date.
 *
 * This struct stores year, month, and day as integers and provides
 * functionality for parsing, formatting, and comparison.
 */
struct Date {
    int year;  ///< The year component.
    int month; ///< The month component (1-12).
    int day;   ///< The day component (1-31).

    /**
     * @brief Default constructor. Initializes date to 0-0-0.
     */
    Date();

    /**
     * @brief Parameterized constructor.
     * @param y Year.
     * @param m Month.
     * @param d Day.
     */
    Date(int y, int m, int d);

    /**
     * @brief Creates a Date object from a string.
     * @param date_str The date string in "YYYY-MM-DD" format.
     * @return A Date object.
     * @throws std::invalid_argument if the string format is incorrect.
     */
    static Date fromString(const std::string& date_str);

    /**
     * @brief Converts the Date object to a string.
     * @return A string representation of the date in "YYYY-MM-DD" format.
     */
    std::string toString() const;

    /**
     * @brief Compares two Date objects for equality.
     * @param other The other Date object to compare against.
     * @return True if the dates are the same, false otherwise.
     */
    bool operator==(const Date& other) const;

    /**
     * @brief Compares if this Date is less than another.
     * @param other The other Date object to compare against.
     * @return True if this date is earlier than the other, false otherwise.
     */
    bool operator<(const Date& other) const;
};

/**
 * @brief Overload for the output stream operator.
 * @param os The output stream.
 * @param date The Date object to output.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Date& date);

#endif // DATE_H
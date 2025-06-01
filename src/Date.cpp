#include "Date.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

Date::Date() : year(0), month(0), day(0) {}
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

Date Date::fromString(const std::string& date_str) {
    std::stringstream ss(date_str);
    std::string segment;
    std::vector<int> parts;

    while (std::getline(ss, segment, '-')) {
        try {
            parts.push_back(std::stoi(segment));
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid number format in date string.");
        } catch (const std::out_of_range& e) {
            throw std::invalid_argument("Number out of range in date string.");
        }
    }

    if (parts.size() != 3) {
        throw std::invalid_argument("Invalid date format. Expected YYYY-MM-DD.");
    }

    if (parts[1] < 1 || parts[1] > 12 || parts[2] < 1 || parts[2] > 31) {
        throw std::invalid_argument("Invalid month or day value.");
    }

    return Date(parts[0], parts[1], parts[2]);
}

std::string Date::toString() const {
    std::stringstream ss;
    ss << std::setfill('0') << year << "-" << std::setw(2) << month << "-" << std::setw(2) << day;
    return ss.str();
}

bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.toString();
    return os;
}
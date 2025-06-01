#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FinanceManager.h"
#include <fstream>
#include <cstdio> // Для std::remove

// Помощник для создания менеджера и добавления некоторых данных
FinanceManager create_test_manager() {
    FinanceManager manager;
    manager.addTransaction(Date(2023, 10, 25), -50.0, "Food", "Lunch");
    manager.addTransaction(Date(2023, 10, 26), 2000.0, "Salary", "October salary");
    manager.addTransaction(Date(2023, 10, 27), -15.5, "Transport", "Bus ticket");
    return manager;
}

TEST_CASE("Date Class Functionality") {
    SUBCASE("fromString and toString") {
        Date d = Date::fromString("2023-05-15");
        CHECK(d.year == 2023);
        CHECK(d.month == 5);
        CHECK(d.day == 15);
        CHECK(d.toString() == "2023-05-15");
    }

    SUBCASE("fromString with padding") {
        Date d = Date::fromString("2024-01-09");
        CHECK(d.year == 2024);
        CHECK(d.month == 1);
        CHECK(d.day == 9);
        CHECK(d.toString() == "2024-01-09");
    }

    SUBCASE("Comparison operators") {
        Date d1(2023, 10, 25);
        Date d2(2023, 10, 26);
        Date d3(2023, 10, 25);
        CHECK(d1 < d2);
        CHECK_FALSE(d2 < d1);
        CHECK(d1 == d3);
        CHECK_FALSE(d1 == d2);
    }
    
    SUBCASE("Invalid date string") {
        CHECK_THROWS_AS(Date::fromString("2023/10/25"), std::invalid_argument);
        CHECK_THROWS_AS(Date::fromString("not-a-date"), std::invalid_argument);
        CHECK_THROWS_AS(Date::fromString("2023-13-01"), std::invalid_argument);
    }
}

TEST_CASE("FinanceManager Core Functionality") {
    FinanceManager manager = create_test_manager();

    SUBCASE("Add Transaction") {
        CHECK(manager.getTransactions().size() == 3);
        manager.addTransaction(Date(2023, 11, 1), -100.0, "Shopping", "New shoes");
        CHECK(manager.getTransactions().size() == 4);
        const auto* new_trans = manager.findTransactionById(4);
        REQUIRE(new_trans != nullptr);
        CHECK(new_trans->category == "Shopping");
        CHECK(new_trans->amount == -100.0);
    }

    SUBCASE("Delete Transaction") {
        REQUIRE(manager.findTransactionById(1) != nullptr);
        CHECK(manager.deleteTransaction(1) == true);
        CHECK(manager.getTransactions().size() == 2);
        CHECK(manager.findTransactionById(1) == nullptr);
        // Отрицательный случай: удалить несуществующее
        CHECK(manager.deleteTransaction(999) == false);
    }

    SUBCASE("Edit Transaction") {
        bool success = manager.editTransaction(3, Date(2023, 10, 28), -20.0, "Transport", "Metro");
        CHECK(success == true);
        const auto* edited_trans = manager.findTransactionById(3);
        REQUIRE(edited_trans != nullptr);
        CHECK(edited_trans->amount == -20.0);
        CHECK(edited_trans->date.day == 28);
        CHECK(edited_trans->description == "Metro");
        // Отрицательный случай: редактировать несуществующее
        CHECK(manager.editTransaction(999, Date(), 0, "", "") == false);
    }
    
    SUBCASE("Find Transaction") {
        const auto* found = manager.findTransactionById(2);
        REQUIRE(found != nullptr);
        CHECK(found->category == "Salary");
        // Отрицательный случай: найти несуществующее
        const auto* not_found = manager.findTransactionById(999);
        CHECK(not_found == nullptr);
    }
}

TEST_CASE("File I/O") {
    const std::string test_filename = "test_data.csv";
    
    // Очистка перед тестом
    std::remove(test_filename.c_str());

    SUBCASE("Save and Load") {
        FinanceManager manager1 = create_test_manager();
        manager1.saveToFile(test_filename);

        FinanceManager manager2;
        manager2.loadFromFile(test_filename);

        const auto& trans1 = manager1.getTransactions();
        const auto& trans2 = manager2.getTransactions();

        REQUIRE(trans1.size() == trans2.size());
        for (size_t i = 0; i < trans1.size(); ++i) {
            CHECK(trans1[i].id == trans2[i].id);
            CHECK(trans1[i].date == trans2[i].date);
            CHECK(trans1[i].amount == doctest::Approx(trans2[i].amount));
            CHECK(trans1[i].category == trans2[i].category);
            CHECK(trans1[i].description == trans2[i].description);
        }

        // Проверка, правильно ли обновлен следующий идентификатор
        manager2.addTransaction(Date(2024, 1, 1), 1.0, "Test", "");
        CHECK(manager2.findTransactionById(4) != nullptr);
    }

    SUBCASE("Load from non-existent file") {
        FinanceManager manager;
        // Не следует бросать, просто информировать пользователя (или молчать)
        CHECK_NOTHROW(manager.loadFromFile("non_existent_file.csv"));
        CHECK(manager.getTransactions().empty());
    }

    SUBCASE("Load from malformed file") {
        std::ofstream malformed_file(test_filename);
        malformed_file << "ID,Date,Amount,Category,Description\n";
        malformed_file << "1,2023-10-10,100,Food\n";
        malformed_file.close();

        FinanceManager manager;
        CHECK_THROWS_AS(manager.loadFromFile(test_filename), std::runtime_error);
    }

    // Очистка после теста
    std::remove(test_filename.c_str());
}
#include <gtest/gtest.h>
#include "employee.h"
#include <cstring>

TEST(EmployeeTest, SalaryCalculation) {
    employee emp;
    emp.num = 1;
    std::strcpy(emp.name, "Alice");
    emp.hours = 40.0;
    double hourlyRate = 20.0;
    double expected = 800.0;
    double result = emp.hours * hourlyRate;
    EXPECT_DOUBLE_EQ(expected, result);
}

TEST(EmployeeTest, ZeroHoursSalary) {
    employee emp;
    emp.num = 2;
    std::strcpy(emp.name, "Bob");
    emp.hours = 0.0;
    double hourlyRate = 15.0;
    double expected = 0.0;
    double result = emp.hours * hourlyRate;
    EXPECT_DOUBLE_EQ(expected, result);
}

TEST(EmployeeTest, NegativeHoursSalary) {
    employee emp;
    emp.num = 3;
    std::strcpy(emp.name, "Carol");
    emp.hours = -5.0;
    double hourlyRate = 20.0;
    double expected = -100.0;
    double result = emp.hours * hourlyRate;
    EXPECT_DOUBLE_EQ(expected, result);
}

TEST(EmployeeTest, LargeHoursSalary) {
    employee emp;
    emp.num = 4;
    std::strcpy(emp.name, "David");
    emp.hours = 100.0;
    double hourlyRate = 25.0;
    double expected = 2500.0;
    double result = emp.hours * hourlyRate;
    EXPECT_DOUBLE_EQ(expected, result);
}

TEST(EmployeeTest, DecimalHoursSalary) {
    employee emp;
    emp.num = 5;
    std::strcpy(emp.name, "Eve");
    emp.hours = 37.5;
    double hourlyRate = 15.0;
    double expected = 562.5;
    double result = emp.hours * hourlyRate;
    EXPECT_DOUBLE_EQ(expected, result);
}

TEST(EmployeeTest, NameCopy) {
    employee emp;
    const char* name = "TestName";
    std::strcpy(emp.name, name);
    EXPECT_STREQ(emp.name, name);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

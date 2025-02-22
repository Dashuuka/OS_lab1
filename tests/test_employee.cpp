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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
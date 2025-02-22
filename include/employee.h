#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdexcept>
#include <cctype>  // for isprint

struct employee {
    int num;         // Employee ID (must be positive)
    char name[10];   // Employee name (max 9 characters + null terminator)
    double hours;    // Worked hours (must be non-negative)
};

inline void validateEmployee(const employee& emp) {
    // Check that employee number is positive.
    if (emp.num <= 0) {
        throw std::invalid_argument("Employee number must be positive");
    }

    // Check that working hours are non-negative.
    if (emp.hours < 0) {
        throw std::invalid_argument("Negative working hours");
    }

    // Check that name is not empty.
    if (emp.name[0] == '\0') {
        throw std::invalid_argument("Employee name cannot be empty");
    }

    // Check that name is null-terminated within the 10-character buffer
    int len = 0;
    bool nullFound = false;
    for (int i = 0; i < 10; i++) {
        if (emp.name[i] == '\0') {
            nullFound = true;
            break;
        }
        len++;
    }
    if (!nullFound) {
        throw std::invalid_argument("Employee name is not null-terminated");
    }

    // Check that name length does not exceed allowed length (max 9 characters)
    if (len > 9) {
        throw std::invalid_argument("Employee name is too long");
    }

    // Check that all characters in name are printable.
    for (int i = 0; i < len; i++) {
        if (!std::isprint(static_cast<unsigned char>(emp.name[i]))) {
            throw std::invalid_argument("Employee name contains non-printable characters");
        }
    }

    // Additional check: optionally, ensure that hours do not exceed a reasonable limit (e.g., 168 hours per week)
    if (emp.hours > 168.0) {
        throw std::invalid_argument("Working hours exceed maximum allowed limit (168 hours per week)");
    }
}

#endif // EMPLOYEE_H

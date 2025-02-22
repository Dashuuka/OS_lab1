#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include "employee.h"

// Reporter: Reads employee records from a binary file, calculates salary, and writes a text report.
struct EmployeeReport {
    employee emp;   // Employee data
    double salary;  // Calculated salary (hours * hourly rate)
};

int main(int argc, char* argv[]) {
    // Check for correct number of command-line arguments.
    if (argc != 4) {
        std::cerr << "Usage: Reporter <binary_file> <report_file> <hourly_rate>" << std::endl;
        return 1;
    }

    // Get command-line arguments.
    std::string binFileName = argv[1];    // Name of the binary file with employee data.
    std::string reportFileName = argv[2];   // Name of the output text report file.
    double hourlyRate = 0;

    // Convert the hourly rate from string to double.
    try {
        hourlyRate = std::stod(argv[3]);
    }
    catch (...) {
        std::cerr << "Invalid hourly rate" << std::endl;
        return 1;
    }

    // Open the binary file for reading.
    std::ifstream ifs(binFileName, std::ios::binary);
    if (!ifs) {
        std::cerr << "Cannot open binary file: " << binFileName << std::endl;
        return 1;
    }

    // Read employee records from the binary file.
    std::vector<EmployeeReport> reports;
    employee emp;
    while (ifs.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        EmployeeReport er;
        er.emp = emp;
        er.salary = emp.hours * hourlyRate; 
        reports.push_back(er);
    }
    ifs.close(); 

    // Sort the employee reports by employee number.
    std::sort(reports.begin(), reports.end(), [](const EmployeeReport& a, const EmployeeReport& b) {
        return a.emp.num < b.emp.num;
        });

    // Open the report file for writing.
    std::ofstream ofs(reportFileName);
    if (!ofs) {
        std::cerr << "Cannot open report file: " << reportFileName << std::endl;
        return 1;
    }

    ofs << "Report for file \"" << binFileName << "\"\n";
    ofs << "Num\tName\tHours\tSalary\n";

    // Write each employee record with calculated salary.
    for (const auto& er : reports) {
        ofs << er.emp.num << "\t" << er.emp.name << "\t"
            << er.emp.hours << "\t" << std::fixed << std::setprecision(2)
            << er.salary << "\n";
    }

    ofs.close();
    return 0;
}

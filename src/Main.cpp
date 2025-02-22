#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"

// Main: Coordinates the execution of Creator and Reporter utilities.

// Function to print the contents of the binary file to the console.
void printBinaryFile(const std::string& fileName) {
    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error opening binary file: " << fileName << std::endl;
        return;
    }
    employee emp;
    while (ifs.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        std::cout << "Num: " << emp.num << " Name: " << emp.name
            << " Hours: " << emp.hours << std::endl;
    }
}

// Function to print the contents of the report file to the console.
void printReport(const std::string& fileName) {
    std::ifstream ifs(fileName);
    if (!ifs) {
        std::cerr << "Error opening report file: " << fileName << std::endl;
        return;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << std::endl;
    }
}

int main() {
    std::string binFileName;
    int recordCount = 0;

    // Get binary file name and record count from user.
    std::cout << "Binary file name: ";
    std::cin >> binFileName;
    std::cout << "Number of records: ";
    std::cin >> recordCount;

    // Build the command to execute Creator.exe with required parameters.
    std::string creatorCmd = "Creator.exe " + binFileName + " " + std::to_string(recordCount);
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // Launch the Creator process to generate the binary file.
    if (!CreateProcess(NULL, const_cast<char*>(creatorCmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to start Creator process. Error: " << GetLastError() << std::endl;
        return 1;
    }
    // Wait for the Creator process to finish.
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Print the contents of the binary file to the console.
    printBinaryFile(binFileName);

    std::string reportFileName;
    double hourlyRate = 0;

    // Get report file name and hourly rate from user.
    std::cout << "Report file name: ";
    std::cin >> reportFileName;
    std::cout << "Hourly rate: ";
    std::cin >> hourlyRate;

    // Build the command to execute Reporter.exe with required parameters.
    std::string reporterCmd = "Reporter.exe " + binFileName + " " + reportFileName + " " + std::to_string(hourlyRate);

    // Launch the Reporter process to generate the text report.
    if (!CreateProcess(NULL, const_cast<char*>(reporterCmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to start Reporter process. Error: " << GetLastError() << std::endl;
        return 1;
    }
    // Wait for the Reporter process to finish.
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Print the generated report to the console.
    printReport(reportFileName);
    return 0;
}

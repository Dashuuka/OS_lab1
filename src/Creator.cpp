#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"

// Creator: Reads employee data from the console and writes records to a binary file.
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Creator <binary_file> <record_count>" << std::endl;
        return 1;
    }

    // Get binary file name and record count from arguments.
    std::string fileName = argv[1];
    int recordCount = 0;

    // Convert record count from string to integer.
    try {
        recordCount = std::stoi(argv[2]);
    }
    catch (...) {
        std::cerr << "Invalid record count" << std::endl;
        return 1;
    }

    // Open the binary file for writing.
    std::ofstream ofs(fileName, std::ios::binary);
    if (!ofs) {
        std::cerr << "Cannot open file for writing: " << fileName << std::endl;
        return 1;
    }

    // Loop to read each employee's data from the console.
    for (int i = 0; i < recordCount; ++i) {
        employee emp = {}; 
        std::cout << "Enter employee " << i + 1 << " (num name hours): ";

        // Read employee number, name, and working hours.
        if (!(std::cin >> emp.num >> emp.name >> emp.hours)) {
            std::cerr << "Input error" << std::endl;
            return 1;
        }

        // Write the employee record to the binary file.
        ofs.write(reinterpret_cast<char*>(&emp), sizeof(emp));
        if (!ofs) {
            std::cerr << "Write error" << std::endl;
            return 1;
        }
    }

    ofs.close();
    return 0;
}

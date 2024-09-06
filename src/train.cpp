#include <iostream>  // Include the iostream library for input and output
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>
#include "stdlib.h"


std::pair<std::vector<double>, std::vector<double> > readCSV(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::string line;
    std::vector<double> column1;
    std::vector<double> column2;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value;
            double col1, col2;

            // Read the first column
            if (std::getline(ss, value, ',')) {
                col1 = atof(value.c_str());
                column1.push_back(col1);
            }

            // Read the second column
            if (std::getline(ss, value, ',')) {
                col2 = atof(value.c_str());
                column2.push_back(col2);
            }
        }
        file.close();
        column1.erase(column1.begin());
        column2.erase(column2.begin());

    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return std::make_pair(column1, column2); // Return the vectors
}

int main() {
    // Call the function and get the vectors
    std::pair<std::vector<double>, std::vector<double> > columns = readCSV("data.csv");

    // Output the results
    for (size_t i = 0; i < columns.first.size(); i++) {
        std::cout << "Column 1: " << columns.first[i] << ", Column 2: " << columns.second[i] << std::endl;
    }
//
//    std::ifstream file("data.csv");
//    std::string line;
//    std::vector<double> km;
//    std::vector<double> price;
//
//    if (file.is_open()) {
//        while (std::getline(file, line)) {
//            std::stringstream ss(line);
//            std::string value;
//            double col1, col2;
//
//            // Read the first column
//            if (std::getline(ss, value, ',')) {
//                col1 = atof(value.c_str());
//                km.push_back(col1);
//            }
//
//            // Read the second column
//            if (std::getline(ss, value, ',')) {
//                col2 = atof(value.c_str());
//                price.push_back(col2);
//            }
//        }
//        file.close();
//    } else {
//        std::cout << "Unable to open file" << std::endl;
//        return 1;
//    }
//
//    // Output the results
//    for (size_t i = 0; i < km.size(); i++) {
//        std::cout << "Column 1: " << km[i] << ", Column 2: " << price[i] << std::endl;
//    }
//
//    return 0;
}

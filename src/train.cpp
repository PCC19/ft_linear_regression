#include <iostream>  // Include the iostream library for input and output
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>
#include "stdlib.h"
#include <limits>
#include <math.h>


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

std::vector<double> minus(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() != vec2.size()) {
        throw std::runtime_error("Vectors must have the same size.");
    }
    std::vector<double> result(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] - vec2[i];
    }

    return result;
}

std::vector<double> times(const std::vector<double>& vec, double constant) {
    std::vector<double> result(vec.size());

    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] * constant;
    }

    return result;
}

double estimatePrice(double milleage, double theta0, double theta1){
    return (theta0 + theta1*milleage);
}


int main() {
    // Load data from file
    std::pair<std::vector<double>, std::vector<double> > columns = readCSV("data.csv");

    // Output the results
    for (size_t i = 0; i < columns.first.size(); i++) {
        std::cout << "Column 1: " << columns.first[i] << ", Column 2: " << columns.second[i] << std::endl;
    }

    std::vector<double> dif;
    dif = times(columns.first, 3.0 );
    for (size_t i = 0; i < columns.first.size(); i++) {
        std::cout << "Dif: " << dif[i] << std::endl;
    }
    std::vector<double> milleage = columns.first;
    std::vector<double> price = columns.second;

    double theta0 = 0;
    double theta1 = 0;
    double tmp_theta0 = 0;
    double tmp_theta1 = 0;
    double learningRate = 0.2;
    double eps = 0.1;
    int max_iter = 10;
    int m = milleage.size();
    double error = std::numeric_limits<double>::infinity();
    double tmpError = 0;

        std::cout << "m: " << m << std::endl;

    int i = 0;
    bool cont = true;
    while (cont){
        i++;
        for (int j = 0; j < m; j++) {
            std::cout << "est: " << estimatePrice(milleage[j], theta0, theta1) << " price: " << price[j] << std::endl;
            tmp_theta0 += estimatePrice(milleage[j], theta0, theta1) - price[j];
            tmp_theta1 += (estimatePrice(milleage[j], theta0, theta1) - price[j])*milleage[j];
        }
        tmp_theta0 = tmp_theta0 * learningRate / m;
        tmp_theta1 = tmp_theta1 * learningRate / m;
        for (int j = 0; j < m; j++) {
            tmpError += abs((estimatePrice(milleage[j], theta0, theta1) - price[j]));
        }
        tmpError = tmpError / m;

            std::cout << "i: " << i << "\t";
            std::cout << "tmp_theta0: " << tmp_theta0 << "\t";
            std::cout << "tmp_theta1: " << tmp_theta1 << "\t";
            std::cout << "error: " << error << "\t";
            std::cout << "tmp_error: " << tmpError << std::endl;

        if (abs(error - tmpError) < eps) { cont = false; };
        if (i >= max_iter) {cont = false; };
        error = tmpError;
        tmpError = 0;
        theta0 -= tmp_theta0;
        theta1 -= tmp_theta1;

    } // while

}

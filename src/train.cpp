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

double estimate(double X, double t0, double t1){
    return (t0 + t1*X);
}

// perplexity
double hypothesis(double x, const std::vector<double>& theta) {
    return theta[0] + theta[1] * x;  // theta[0] is the intercept, theta[1] is the slope
}
void gradientDescent(const std::vector<double>& X, const std::vector<double>& y, std::vector<double>& theta, int n, double alpha, int iterations) {
    for (int iter = 0; iter < iterations; iter++) {
        double sum0 = 0.0; // For theta[0] (intercept)
        double sum1 = 0.0; // For theta[1] (slope)
        
        for (int i = 0; i < n; i++) {
            double h = hypothesis(X[i], theta); // Predicted value
            sum0 += h - y[i]; // Error for intercept
            sum1 += (h - y[i]) * X[i]; // Error for slope
                std::cout << "X: " << X[i] << " |y: " << y[i] << " |est: " << h << " | " << (h - y[i]) * X[i] << " |error: " << abs(h - y[i]) << std::endl;
        }
        
        // Update theta values
        theta[0] -= (alpha / n) * sum0; // Update intercept
        theta[1] -= (alpha / n) * sum1; // Update slope
                std::cout << "t0: " << theta[0] <<  " | t1: " << theta[1] << std::endl;
                std::cout << "-----------\n";
    }
}
// ---------------------


int main() {
    // Load data from file
    std::pair<std::vector<double>, std::vector<double> > columns = readCSV("data.csv");
    if (columns.first.size() < 2) {
        std::cout << "Dataset must have at least 2 data points\n";
        return 1;
    }

    // Output the results
    for (size_t i = 0; i < columns.first.size(); i++) {
        std::cout << "Column 1: " << columns.first[i] << ", Column 2: " << columns.second[i] << std::endl;
    }

    std::vector<double> X = columns.first;
    std::vector<double> Y = columns.second;


// perplexity

    std::vector<double> theta; // theta[0] for intercept, theta[1] for slope
        theta.push_back(0.0);
        theta.push_back(0.0);
    double alpha = 0.00001; // Learning rate
    int iterations = 10; // Number of iterations
    int n = X.size();

    // Perform gradient descent to fit the model
    gradientDescent(X, Y, theta, n, alpha, iterations);

    // Output the learned parameters
    std::cout << "Learned parameters:\n";
    std::cout << "Intercept (theta[0]): " << theta[0] << std::endl;
    std::cout << "Slope (theta[1]): " << theta[1] << std::endl;

    return 0;

// Calculate the regression coeficients
    double t0 = 0;
    double t1 = 0;
    double learningRate = 0.01;
    double eps = 0.1;
    int max_iter = 10;
    double error = std::numeric_limits<double>::infinity();


    int i = 0;
    bool cont = true;
    while (cont){
        i++;
        int m = X.size();
        double tmp0 = 0;
        double tmp1 = 0;
        double tmpError = 0;
        for (int j = 0; j < m; j++) {
            double eY = estimate(X[j], t0, t1);
            tmp0 += eY - Y[j];
            tmp1 += (eY - Y[j]) * X[j];
            tmpError += abs(eY - Y[j]);
                std::cout << "X: " << X[j] << " |Y: " << Y[j] << " |est: " << eY << " | " << (eY - Y[j]) * X[j] << " |error: " << abs(eY - Y[j]) << std::endl;
        }
        t0 -= tmp0 * (learningRate / m);
        t1 -= tmp1 * (learningRate / m);
        tmpError = tmpError / m;

                std::cout << "i: " << i << "\t";
                std::cout << "t0: " << t0 << "\t";
                std::cout << "t1: " << t1 << "\t";
                std::cout << "error: " << error << "\t";
                std::cout << "tmp_error: " << tmpError << std::endl;
                std::cout << "-----------------------------------------" << std::endl;

        if (abs(error - tmpError) < eps) { cont = false; };
        if (i >= max_iter) {cont = false; };
        error = tmpError;

    } // while

}

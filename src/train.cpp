#include <iostream>  // Include the iostream library for input and output
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>
#include "stdlib.h"
#include <limits>
#include <math.h>
#include <algorithm>

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

std::vector<double> normalize(std::vector<double>& v, double v_max, double v_min){
    std::vector<double> vn;
    for (size_t i = 0; i < v.size(); i++) {
        vn.push_back((v[i] - v_min) / (v_max - v_min));
    }
    return vn;
}

double max(std::vector<double> &x){
    double m = *std::max_element(x.begin(), x.end());
    return m;
}

double min(std::vector<double> &x){
    double m = *std::min_element(x.begin(), x.end());
    return m;
}

void plot_graphs(std::string filename) {
        std::ostringstream oss;

        oss << "gnuplot -p -c \"./src/" << filename << "\"" << std::endl;
        std::string tmp = oss.str();
        std::cout << "string: " << tmp << std::endl;
        system(tmp.c_str());
}

int main() {
    // Load data from file
    std::pair<std::vector<double>, std::vector<double> > columns = readCSV("data.csv");
    if (columns.first.size() < 2) {
        std::cout << "Dataset must have at least 2 data points\n";
        return 1;
    }
    // Create data vectors and normalize
    std::vector<double> X_raw = columns.first;
    std::vector<double> Y_raw = columns.second;

    std::vector<double> X = normalize(X_raw, max(X_raw), min(X_raw));
    std::vector<double> Y = normalize(Y_raw, max(Y_raw), min(Y_raw));

    // Output the file contents read
    for (size_t i = 0; i < columns.first.size(); i++) {
        std::cout << "Column 1: " << columns.first[i] << ", \t\t| Column 2: " << columns.second[i];
        std::cout << " \t\t| Xn : " << X[i] << ", \t\t| Yn: " << Y[i] << std::endl;
    }

    // Calculate the regression coeficients
    double t0 = 0;
    double t1 = 0;
    double learningRate = 0.01;
    double eps = 1e-6;
    int max_iter = 10000;
    double error = std::numeric_limits<double>::infinity();
    std::vector<double> e;
    std::string flag;

    int i = 0;
    bool cont = true;
    std::ofstream arq;
    arq.open ("train.txt");
    while (cont){
        i++;
        int m = X.size();
        double tmp0 = 0;
        double tmp1 = 0;
        double tmpError = 0;
        for (int j = 0; j < m; j++) {
            double Yp = estimate(X[j], t0, t1);
            tmp0 += Yp - Y[j];
            tmp1 += (Yp - Y[j]) * X[j];
            tmpError += abs(Yp - Y[j]);
            tmpError += (Yp - Y[j]) * (Yp - Y[j]);
        }
        t0 -= tmp0 * (learningRate / m);
        t1 -= tmp1 * (learningRate / m);
        tmpError = sqrt(tmpError / m);

        arq << t0 << " " << t1 << " " << tmpError << std::endl;

        if (abs(error - tmpError) < eps) { std::cout << i << " [Stop: max iter reached]\n"; cont = false; };
        if (i >= max_iter) {std::cout << i << " [Stop: min delta error reached]\n"; cont = false; };
        error = tmpError;
        e.push_back(error);

    } // while
    arq.close();

    // Output X, Y and Yp to file
    arq.open ("output_data.txt");
    for (size_t i = 0; i < columns.first.size(); i++) {
        arq << X[i] << " " << Y[i] << " " << t0 + t1*X[i] << std::endl;
    }
    arq.close();
    // Output error to file
    arq.open ("output_error.txt");
    for (size_t i = 1; i < e.size(); i++) {
        arq << i << " " << abs(e[i]) << " " << abs(e[i] - e[i - 1]) << std::endl;
    }
    arq.close();
    // Output theta parameters to file
    arq.open ("theta");
    arq << t0 << std::endl << t1 << std::endl;
    arq << max(X_raw) << std::endl << min(X_raw) << std::endl;
    arq << max(Y_raw) << std::endl << min(Y_raw) << std::endl;
    arq.close();
    // Plot graphs
    std::cout << "Do you want to plot the graph ? (y/n))" << std::endl;
    std::cin >> flag;
    if (flag == "y") {
        plot_graphs("plot_train.gnu");
        plot_graphs("plot_training_error.gnu");
        plot_graphs("plot_delta_error.gnu");

        // Generate 2d plot of error vs theta parameters
        int n = 20;
        double xi = 0;  // 6500
        double xf = 2;  // 10500
        double yi = 0;  // -0.5
        double yf = -2; // 0.5

        arq.open ("grid.txt");
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                t0 = xi + i * (xf - xi) / n;
                t1 = yi + k * (yf - yi) / n;
                double tmpError = 0;
                for (size_t j = 0; j < X.size(); j++) {
                    double Yp = estimate(X[j], t0, t1);
                    tmpError += sqrt((Yp - Y[j]) * (Yp - Y[j]));
                }
                arq << t0 << " " << t1 << " " << tmpError << std::endl;
            }
        }
        arq.close();
        plot_graphs("plot_grid.gnu");
    }
}

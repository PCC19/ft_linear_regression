#include "stdio.h"
#include "stdlib.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>  // Include the iostream library for input and output
                     //
//- [ ] Se nao existir arquivo
//	- [ ] Imprime msg e cria arquivo com pesos zerados
//- [ ] loop ate pressionar exit:
//	- [ ] Pede input do usuario (mileage)
//		- [ ] Check se positivo
//	- [ ] Le pesos do arquivo
//		- [ ] Checa se arquivo ok
//	- [ ] Calcular previsao
//	- [ ] Printa previsao
//	- [ ] Pergunta se quer grafico / terminal ou nada
//		- [ ] Plota grafico com gnuplot
//
//
//
bool file_exists(const std::string& filename) {
  struct stat buffer;   
  return (stat (filename.c_str(), &buffer) == 0); 
}

void initialize_theta_parameters(const std::string& file_name) {

    std::cout << "file_name " << file_name << std::endl;
    if (file_exists(file_name)) {
        std::cout << "Parameters Theta file found !" << std::endl; }
    else {
        std::ofstream outFile(file_name.c_str());
        std::cout <<  "Initialasing theta parameters file ... " << std::endl;
        if (outFile.is_open()) {
            outFile << 0 << std::endl;
            outFile << 0 << std::endl;
            outFile.close();
            std::cout << "File created and numbers written successfully." << std::endl;
            outFile.close();
        }
        else {
            std::cerr << "Error creating the file." << std::endl;
        }
    }
}
bool validate_input(const std::string& input) {
    // Check if the input is empty
    if (input.empty()) return false;

    // Allow for an optional leading negative sign
    size_t startIndex = 0;
    if (input[0] == '-') {
        startIndex = 1;
    }
    // Check each character in the string
    for (size_t i = startIndex; i < input.length(); ++i) {
        if (!isdigit(input[i])) {
            return false; // Found a non-digit character
        }
    }
    // Check if positive
    if (atof(input.c_str()) < 0){
        std::cout << "Mileage must be positive !!!" << std::endl;
        return false;
    };
    return true; // All characters were digits
}

void print_graph(double theta0, double theta1, double mileage) {
        std::ostringstream oss;

        oss << "gnuplot -p -c \"./src/plot.gnu\" " << theta0 << " " << theta1 << " " << mileage << std::endl;
        std::string tmp = oss.str();
//        std::cout << "string: " << tmp << std::endl;
        system(tmp.c_str());
}

int main() {
    const std::string       file_name = "theta";
    std::string             input;
    double                  mileage, pred_mileage;
    double                  theta0, theta1;
    std::string             flag;

    // Initizalize parameters file
    initialize_theta_parameters(file_name);
    // Prompt for user input
    std::cout << "Please input mileage: " << std::endl;
    std::cin >> input;
    if (!validate_input(input)) {
        std::cout << "Invalid mileage !!" << :: std::endl;
        return 1;
    }
    else {
        mileage = atof(input.c_str());
    }
    // Check parameter file
    std::ifstream           inputFile(file_name.c_str());
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1; // Exit with an error code
    }
    // Read two numbers from the file
    inputFile >> theta0 >> theta1;
    // Check if the read operation was successful
    if (inputFile.fail()) {
        std::cerr << "Error reading numbers from the file!" << std::endl;
        return 1; // Exit with an error code
    }
    // Calculates prediciton
    pred_mileage = theta0 + theta1 * mileage;
    // Display the output
    std::cout <<"Predicted price: " << pred_mileage << std::endl;
    // Close the file
    inputFile.close();
    // Plot graph ?
    std::cout << "Do you want to plot the graph ? (y/n))" << std::endl;
    std::cin >> flag;
    if (flag == "y") {
        print_graph(theta0, theta1, mileage);
    }
    return 0;  // Return 0 to indicate successful execution
}

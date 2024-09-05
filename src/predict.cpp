#include "stdio.h"
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

void initialize_theta_parameters(const std::string& filename) {
    std::ofstream outFile(filename.c_str());
    if (outFile.is_open()) {
        outFile << 0 << std::endl;
        outFile << 0 << std::endl;
        outFile.close();
        std::cout << "File created and numbers written successfully." << std::endl;
        outFile.close();
    } else {
        std::cerr << "Error creating the file." << std::endl;
    }
}

void generate_point_file_for_gnuplot(const std::string& filename, double theta0, double theta1) {
    std::ofstream outFile(filename.c_str());
    if (outFile.is_open()) {
        outFile << theta0 << std::endl;
        outFile << theta1<< std::endl;
        outFile.close();
        std::cout << "File created and numbers written successfully." << std::endl;
        outFile.close();
    } else {
        std::cerr << "Error creating the file." << std::endl;
    }
}


int main() {
    const std::string       file_name = "theta";
    double                  mileage, pred_mileage;
    double                  theta0, theta1;
    std::string             flag;

    // Initizalize parameters file
    std::cout << "Hello, World predict!" << std::endl;  // Output "Hello, World!" to the console
    if (file_exists(file_name)) {
        std::cout << "Parameters Theta file found !" << std::endl; }
    else {
        std::cout <<  "Initialasing theta parameters file ... " << std::endl;
        initialize_theta_parameters(file_name);
    };
    // Prompt for user input
    std::cout << "Please input mileage: " << std::endl;
    std::cin >> mileage;
    if (mileage < 0){
        std::cout << "Mileage must be positive !!!" << std::endl;
        return 1;
    };
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
    std::cout << "Do you want to plot the graph ?" << std::endl;
    std::cin >> flag;
    if (flag == "y") {
        std::cout << "Print\n";
        generate_point_file_for_gnuplot("point.dat", theta0, theta1);
        std::ostringstream oss; // Create a string stream
        oss << "gnuplot -p -c \"./src/plot.gnu\" " << theta0 << " " << theta1 << " " << mileage << std::endl; // Concatenate the string and doubles
        std::string tmp;
        tmp = oss.str();
        std::cout << "string: " << tmp << std::endl;
        system(tmp.c_str());
    }

    return 0;  // Return 0 to indicate successful execution
}

#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
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
    } else {
        std::cerr << "Error creating the file." << std::endl;
    }
}

//ibool isNumber(const std::string& str) {
//    for (char c : str) {
//        if (!isdigit(c)) {
//            return false;
//        }
//    }
//    return true;
//}

//double get_mileage(void){
//    double mileage;
//
//    std::cout << "Please input mileage: " << std::endl;
//    std::cin >> mileage;
//    if (mileage < 0){
//        std::cout << "Mileage must be positive !!!";
//    };
//    return (mileage);
//}



int main() {
    const std::string       file_name = "theta";
    std::ifstream           inputFile(file_name.c_str());
    double                  mileage, pred_mileage;
    double                  theta0, theta1;

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
    std::cout <<"Predicted mileage: " << pred_mileage << std::endl;

    // Close the file
    inputFile.close();

    return 0;  // Return 0 to indicate successful execution
}

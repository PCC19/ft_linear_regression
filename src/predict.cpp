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
bool file_exist (const std::string& filename) {
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

int main() {
    const std::string file_name = "theta";

    std::cout << "Hello, World predict!" << std::endl;  // Output "Hello, World!" to the console
    if (file_exist(file_name)) {
        std::cout << "Parameters Theta file found !" << std::endl; }
    else {
        std::cout <<  "Initialasing theta parameters file ... " << std::endl;
        initialize_theta_parameters(file_name);
    }

    return 0;  // Return 0 to indicate successful execution
}

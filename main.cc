#include <iostream>

#include "file_managment.h"

int main (int argc, char *argv[]) {
  if (argc - 1 != 4) {
    if (argc - 1 == 1) {
      std::string help = argv[1];
      if (help == "--help") {
        std::cout << "Este programa opera entre cadenas según la operación especificada ";
        std::cout << "Debes introducir tres parámetros:" << std::endl;
        std::cout << "./p01_strings filein.txt fileout.txt opcode\n";
        std::cout << "filein.txt: un fichero .txt que especifica los alfabetos y las cadenas\n";
        std::cout << "fileout.txt: un fichero .txt de salida con los resultados\n";
        std::cout << "[1] Concatenación\n";
        std::cout << "[2] Unión\n";
        std::cout << "[3] Intersección\n";
        std::cout << "[4] Diferencia\n";
        std::cout << "[5] Inversa\n";
        std::cout << "[6] Potencia\n";
        return 1;
      } 
    }
    std::cout << "Modo de empleo: ./p01_strings filein.txt fileout.txt opcode\n";
    std::cout << "Pruebe p01_strings --help’ para más información.\n";
    return 1;
  }
  const std::string INPUT_FILENAME_1 = argv[1]; 
  const std::string INPUT_FILENAME_2 = argv[2]; 
  const std::string OUTPUT_FILENAME = argv[3];
  std::string string_opcode = argv[4];
  const int OPCODE = std::stoi(string_opcode);

  if (OPCODE < 1 && OPCODE > 6) {
    std::cout << "Código de operación erroneo" << std::endl;
    std::cout << "[1] Concatenación\n";
    std::cout << "[2] Unión\n";
    std::cout << "[3] Intersección\n";
    std::cout << "[4] Diferencia\n";
    std::cout << "[5] Inversa\n";
    std::cout << "[6] Potencia\n";
    return 1;
  }

  FileManagment data_processed(INPUT_FILENAME_1, INPUT_FILENAME_2, OUTPUT_FILENAME, OPCODE);
  if (OPCODE >= 1 && OPCODE < 5) {
  data_processed.BinaryOperations();
  } else if (OPCODE >= 5 && OPCODE < 7) {
    data_processed.UnaryOperations();
  } else {
    std::cerr << "Código de operación inválido" << std::endl;
  }
}

/*

probando para github
<--TODO --!>
cambiar el metodo de obtener datos del fichero para recoger el identificador y el lenguaje,
[pair <ID, lang>]
*/
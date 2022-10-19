#include "file_managment.h"

FileManagment::FileManagment(std::string EXTERNAL_INPUT_FILENAME_1, std::string EXTERNAL_INPUT_FILENAME_2, std::string EXTERNAL_OUTPUT_FILENAME, int EXTERNAL_OPCODE) {
  
  INPUT_FILENAME_1 = EXTERNAL_INPUT_FILENAME_1;
  INPUT_FILENAME_2 = EXTERNAL_INPUT_FILENAME_2;
  OUTPUT_FILENAME = EXTERNAL_OUTPUT_FILENAME;
  OPCODE = EXTERNAL_OPCODE;
  
  std::ifstream input_1(INPUT_FILENAME_1);
  std::ifstream input_2(INPUT_FILENAME_2);
  std::ofstream output(OUTPUT_FILENAME);
  std::pair<Alphabet, Language> pair_alphabet_language_file1;
  std::pair<Alphabet, Language> pair_alphabet_language_file2;
  
    if (!input_1.good()) {
    std::cout << "Error en la apertura de fichero" << std::endl;
    exit(1);
  }
  if (!input_2.good()) {
    std::cout << "Error en la apertura del segundo fichero" << std::endl;
    exit(1);
  }

  if (OPCODE >= 1 && OPCODE < 5) {
    int FILE_1_LINES =NumberOfLines(INPUT_FILENAME_1);
    int FILE_2_LINES =NumberOfLines(INPUT_FILENAME_2);
    if ((FILE_1_LINES != FILE_2_LINES)) {
      std::cerr << "los ficheros de entrada no tienen el mismo número de lineas\n" << "Lineas del primer fichero: " 
      << NumberOfLines(INPUT_FILENAME_1) << "\t" <<  "Lineas del segundo fichero: " <<  NumberOfLines(INPUT_FILENAME_2) << std::endl;
      exit(1);
    } else {
      while (!input_1.eof()) {
        std::string file_line;
        std::getline(input_1, file_line);
        pair_alphabet_language_file1 = ObtainFileData(file_line);
        data_vector_file1.push_back(pair_alphabet_language_file1);
      }
      while (!input_2.eof()) {
        std::string file_line;
        std::getline(input_2, file_line);
        pair_alphabet_language_file2 = ObtainFileData(file_line);
        data_vector_file2.push_back(pair_alphabet_language_file2);
      }
    }
  } 
  else {
    while (!input_1.eof()) {
      std::string file_line;
      std::getline(input_1, file_line);
      pair_alphabet_language_file1 = ObtainFileData(file_line);
      data_vector_file1.push_back(pair_alphabet_language_file1);
    }
  }
}

void FileManagment::BinaryOperations() {
  Language result;
  switch (OPCODE) {
    case 1: {
      for (unsigned int data_vector_index = 0; data_vector_index < data_vector_file1.size(); ++data_vector_index) {
        WriteOutput(result.Concatenation(data_vector_file1[data_vector_index].second, data_vector_file2[data_vector_index].second));
      }
    }
      break;
    case 2: {
      for (unsigned int data_vector_index = 0; data_vector_index < data_vector_file1.size(); ++data_vector_index) {
        WriteOutput(result.Union(data_vector_file1[data_vector_index].second, data_vector_file2[data_vector_index].second));
      }
    }
    break;
    case 3: {
      for (unsigned int data_vector_index = 0; data_vector_index < data_vector_file1.size(); ++data_vector_index) {
        WriteOutput(result.Intersection(data_vector_file1[data_vector_index].second, data_vector_file2[data_vector_index].second));
      }
    }
    
    break;
    case 4: {
      for (unsigned int data_vector_index = 0; data_vector_index < data_vector_file1.size(); ++data_vector_index) {
        WriteOutput(result.Difference(data_vector_file1[data_vector_index].second, data_vector_file2[data_vector_index].second));
      }
    }
    
    break;
    default:
      break;
  }
}

void FileManagment::UnaryOperations() {
  Language result;
  switch (OPCODE) {
    case 5: {
      for (unsigned int data_vector_index = 0; data_vector_index < data_vector_file1.size(); ++data_vector_index) {
        WriteOutput(result.Inverse(data_vector_file1[data_vector_index].second));
      }
    }
      break;
    case 6: {
      int exponente;
      std::cout << "exponente" << std::endl;
      std::cin >>exponente;
      for (unsigned int data_vector_index = 0; data_vector_index < data_vector_file1.size(); ++data_vector_index) {
        WriteOutput(result.Potential(data_vector_file1[data_vector_index].second, exponente));
      }
    }
    break;
    default:
      break;
  }
}

void FileManagment::WriteOutput(Language operation_result) {
  std::ofstream output;
  output.open(OUTPUT_FILENAME, std::ofstream::app);
  output << operation_result << "\n";
  output.close();
}


int FileManagment::NumberOfLines(std::string input_file) {
  int number_of_lines = 0;
  std::string line;
  std::ifstream input(input_file);
  while(std::getline(input, line)) {
   number_of_lines++;
  }
  return number_of_lines;
}

std::pair<Alphabet,Language> FileManagment::ObtainFileData(std::string ext_fileline) {

  Word word;  
  Alphabet alphabet;
  Language language;
  std::string word_to_set;
  const char OPEN_BRACE = '{';
  const char CLOSE_BRACE = '}';
  const std::string WHITESPACE = " ";
  std::vector<Word> language_to_set;
  std::string file_line = ext_fileline;
  std::vector<std::string> alphabet_to_set;
  std::pair<Alphabet, Language> pair_alphabet_language;
  
  std::vector<std::string> file_alphabet_container;
  std::vector<std::string> file_language_container;

  int first_brace = file_line.find_first_of(OPEN_BRACE);
  int first_close_brace = file_line.find_first_of(CLOSE_BRACE);
  int second_brace = file_line.find_last_of(OPEN_BRACE);
  int second_close_brace = file_line.find_last_of(CLOSE_BRACE);

  for (int alphabet_separator = first_brace + 1; alphabet_separator < first_close_brace; ++alphabet_separator) {
    std::string symbol(1,file_line[alphabet_separator]);
    if (symbol != WHITESPACE) 
    alphabet_to_set.push_back(symbol);
  }
  alphabet.setAlphabet(alphabet_to_set);
  alphabet_to_set.clear();

  for (int language_index = second_brace + 2; language_index < second_close_brace ; ++language_index) {
    while (file_line[language_index] != ' ') {
      word_to_set.push_back(file_line[language_index]);
      language_index++;
    }
    word.setWord(word_to_set);
    word_to_set.clear();
    language_to_set.push_back(word);
  }
  language.setLanguage(language_to_set);
  language_to_set.clear();
  pair_alphabet_language.first = alphabet;
  pair_alphabet_language.second = language;
  return pair_alphabet_language;
}

/*

  for (int alphabet_index = first_brace + 1; alphabet_index < first_close_brace; ++alphabet_index) {
    std::string symbol(1,file_line[alphabet_index]);
    alphabet_to_set.push_back(symbol);
  }

  if (OPCODE >= 1 && OPCODE < 5) {
    while (!input_1.eof()) {
    std::string file_line;
    std::cout << file_line << std::endl;
    std::getline(input_1,file_line);
    std::cout << file_line << std::endl;
    //const char WHITESPACE = ' ';
    //const char OPEN_BRACE = '{';
    //const char CLOSE_BRACE = '}';
  }


for (unsigned int string_index = 0; string_index < file_line.size(); ++string_index) {
      if (file_line[string_index + 1] == WHITESPACE) {
        std::string str_symbol(1,file_line[string_index]);
        alphabet_to_set.push_back(str_symbol);
      }
    }
    alphabet.setAlphabet(alphabet_to_set);
    alphabet_to_set.clear();

    for (unsigned int word_index = file_line.find_last_of(WHITESPACE) + 1; word_index < file_line.size(); ++word_index) {
      word_to_set.push_back(file_line[word_index]);
    }
    word.setWord(word_to_set);
    word_to_set.clear();

    if(alphabet.getAlphabet().size() == 0) {
      for (unsigned int string_index = 0; string_index < file_line.size(); ++string_index) {
        if (file_line[string_index] != WHITESPACE) {
          std::string str_symbol(1,file_line[string_index]);
          alphabet_to_set.push_back(str_symbol);
          word.setWord(str_symbol);
        }
      }
      alphabet.setAlphabet(alphabet_to_set);
    }

    std::pair<Alphabet, Word> vector_data_pair;
    vector_data_pair.first = alphabet;
    vector_data_pair.second = word;
    data_vector.push_back(vector_data_pair);
*/
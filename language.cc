#include "language.h"

Language::Language() {
  language = {};
}

Language::Language(std::vector<Word> external_language) {
  language = external_language;
}

void Language::setLanguage(std::vector<Word> external_language) {
  language = external_language;
}

std::vector<Word> Language::getLanguage() {
  return language;
}

Language Language::Concatenation(Language file1_language, Language file2_language) {
  std::vector<Word> concatenation_result;
  std::string word_concatenated;
  for (unsigned int language1_index = 0; language1_index < file1_language.getLanguage().size(); ++language1_index) {
    for (unsigned int language2_index = 0; language2_index < file2_language.getLanguage().size(); ++language2_index) {
      word_concatenated = file1_language.getLanguage()[language1_index].getWord() + file2_language.getLanguage()[language2_index].getWord();
      concatenation_result.push_back(word_concatenated);
    }
  }
  return concatenation_result;
}

Language Language::Union(Language file1_language, Language file2_language) {
  Language union_result;
  std::vector<Word> word_vector_to_set;

  for (unsigned int language1_vector_index = 0; language1_vector_index < file1_language.getLanguage().size(); language1_vector_index++) {
    word_vector_to_set.push_back(file1_language.getLanguage()[language1_vector_index]);
  }
  for (unsigned int language2_vector_index = 0; language2_vector_index < file2_language.getLanguage().size(); language2_vector_index++) {
    word_vector_to_set.push_back(file2_language.getLanguage()[language2_vector_index]);
  }
  union_result.setLanguage(word_vector_to_set);
  return union_result;
}

Language Language::Intersection(Language file1_language, Language file2_language) {
  Language union_result;
  std::vector<Word> word_vector_to_set;

  for (unsigned int language1_index = 0; language1_index < file1_language.getLanguage().size(); ++language1_index) {
    for (unsigned int language2_index = 0; language2_index < file2_language.getLanguage().size(); ++language2_index) {
      if( file1_language.getLanguage()[language1_index].getWord() == file2_language.getLanguage()[language2_index].getWord()) {
        word_vector_to_set.push_back(file1_language.getLanguage()[language1_index].getWord());
      }
    }
  }
  union_result.setLanguage(word_vector_to_set);
  return union_result;
}

std::ostream& operator<<(std::ostream &os, Language &summoner_language) {
  os << "{";
  for (unsigned int vector_index = 0; vector_index < summoner_language.language.size(); vector_index++) {
    os << summoner_language.language[vector_index].getWord() << " ";
  } 
  os << "}";
  return os;
}
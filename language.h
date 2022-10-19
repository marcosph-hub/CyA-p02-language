#include <iostream>
#include <vector>

#include "word.h"

class Language {
  private:
  std::vector<Word> language;

  public:
  Language();
  Language(std::vector<Word> external_language);
  void setLanguage(std::vector<Word> external_language);
  std::vector<Word> getLanguage();
  friend std::ostream& operator<<(std::ostream &os, Language &summoner_language);
  Language Concatenation(Language file1_language, Language file2_language);
  Language Union(Language file1_language, Language file2_language);
  Language Intersection(Language file1_language, Language file2_language);
  Language Difference(Language file1_language, Language file2_language);
  Language Inverse(Language file1_language);
  Language Potential(Language file1_language, int exponente);

};
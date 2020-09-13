#include <iostream>
#include <string>
#include <vector>

bool isNormalSymbol(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9') || (c == '_');
}

bool isPunctuationSymbol(char c) { return !isNormalSymbol(c); }

void reverseWords(const char* text) {
  //   std::cout << "ReverseWords()\n";
  if (*text == '\0') return;

  static std::vector<std::vector<char>> vecPunctuationSymbols;

  std::string buff;
  while (*text != '\0' && isNormalSymbol(*text)) {
    // std::cout << "Add to buff: [" << *text << "]\n";
    buff += *text;
    ++text;
  }

  if (*text != '\0') {
    std::vector<char> punctuationSymbols;
    while (*text != '\0' && isPunctuationSymbol(*text)) {
      //   std::cout << "Adding punctuation symbol: [" << *text << "]\n";
      // points to punctuation symbol
      punctuationSymbols.push_back(*text);
      ++text;
    }
    vecPunctuationSymbols.push_back(punctuationSymbols);
  }

  reverseWords(text);
  std::cout << buff;
  if (!vecPunctuationSymbols.empty()) {
    // print punctuation symbol
    static auto it = vecPunctuationSymbols.begin();
    const auto& currPunctSymbols = *it;
    for (char punctSymbol : currPunctSymbols) {
      std::cout << punctSymbol;
    }
    ++it;
  }
}

int main() {
  //   reverseWords("Hello world, baby!");  // should print "baby world, Hello!"
  reverseWords("1;;2;3;4;;5.");  // prints "5;;4;3;2;;1."
}

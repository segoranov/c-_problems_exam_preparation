#include <cstring>
#include <iostream>
#include <utility>

int findPositionOfMostDistantEqualSymbol(int start, const char* str);

std::pair<int, int> getPositionsOfMostDistantEqualSymbols(const char* str) {
  const int length = std::strlen(str);

  int firstPos = 0, secondPos = 0;

  for (int currentSymbolPos = 0; currentSymbolPos < length;
       currentSymbolPos++) {
    char currentSymbol = str[currentSymbolPos];

    int mostDistantEqualSymbolPos =
        findPositionOfMostDistantEqualSymbol(currentSymbolPos, str);

    if (mostDistantEqualSymbolPos - currentSymbolPos > secondPos - firstPos) {
      firstPos = currentSymbolPos;
      secondPos = mostDistantEqualSymbolPos;
    }
  }

  return {firstPos, secondPos};
}

int findPositionOfMostDistantEqualSymbol(int startPos, const char* str) {
  const int length = std::strlen(str);
  char symbol = str[startPos];

  int result = startPos;

  for (int i = startPos; i < length; i++) {
    char currentSymbol = str[i];
    if (symbol == currentSymbol) {
      result = i;
    }
  }

  return result;
}

int main() {
  // Return value should be pair <4, 21>, the symbol space ' ' is on position 4
  // and 21, with distance 17 between them, which is the longest in our example
  auto testPositions =
      getPositionsOfMostDistantEqualSymbols("this is just a simple example");

  std::cout << "Result: <" << testPositions.first << ", "
            << testPositions.second << ">\n";
}

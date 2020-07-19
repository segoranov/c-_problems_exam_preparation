#include <cstring>
#include <iostream>
#include <string>

void validate(const char*** library, int m, int n) {
  if (m > 20) throw "Too many rows";
  if (n > 30) throw "Too many books in a row";

  for (int row = 0; row < m; row++) {
    for (int col = 0; col < n; col++) {
      if (strlen(library[row][col]) > 100) throw "Too many symbols in title";
    }
  }
}

bool isInAlphabeticalOrder(const char** row, int size) {
  // row[0] will be the first title

  for (int i = 0; i < size - 1; i++) {
    if (strcmp(row[i], row[i + 1]) > 0) {
      return false;
    }
  }

  return true;
}

bool isSpace(char c) { return c == ' '; }

void printTitleAsPassword(const char* title) {
  const int titleSize = std::strlen(title);

  int currentWordSize = 0;
  for (int i = 0; i < titleSize; i++) {
    if (isSpace(title[i])) {
      std::cout << currentWordSize << ' ';
      currentWordSize = 0;
    } else if (i == titleSize - 1) {  // last word, we will exit for loop
      ++currentWordSize;
      std::cout << currentWordSize << ' ';
    } else {
      ++currentWordSize;
    }
  }
}

void revealPassword(const char*** library, int m, int n) {
  // library[0][0] will be the first book title in the first row
  validate(library, m, n);

  for (int row = 0; row < m; row++) {
    if (isInAlphabeticalOrder(library[row], n)) {
      const char* middleTitle = library[row][n / 2];
      printTitleAsPassword(middleTitle);
    }
  }
  std::cout << '\n';
}

int main() {
  // clang-format off
    const char*** library = new const char**[3]{
        new const char*[3]{"Algebra", "Analytical Geometry", "Mathematical analysis"},
        new const char*[3]{"Data structures", "Introduction to programming", "Object oriented programming"},
        new const char*[3]{"Data bases", "Artifical intelligence", "Functional programming"}
    };
  // clang-format on

  // We should print "Analytical Geometry" and "Introduction to programming" as
  // password, which gives us '10 8 12 2 11'. The 3rd row should be skipped,
  // since it is not sorted alphabetically
  revealPassword(library, 3, 3);
}

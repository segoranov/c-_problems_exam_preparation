#include <string.h>

#include <iostream>
#include <string>

bool isSorted(const char* books[], int booksCnt) {
  for (int i = 0; i < booksCnt - 1; ++i) {
    if (strcmp(books[i], books[i + 1]) > 0) return false;
  }

  return true;
}

std::string processTitle(const char* title) {
  std::string result;
  int cnt = 0;
  while (*title != '\0') {
    if (*title != ' ') {
      ++cnt;
    } else {
      result += std::to_string(cnt);
      result += " ";
      cnt = 0;
    }
    ++title;
  }

  result += std::to_string(cnt);

  return result;
}

void revealPassword(const char** books[], int rows, int booksInRow) {
  std::string password;
  const int middle =
      (booksInRow % 2 == 0) ? (booksInRow - 1) / 2 : booksInRow / 2;

  for (int row = 0; row < rows; row++) {
    if (isSorted(books[row], booksInRow)) {
      password += processTitle(books[row][middle]);
      password += " ";
    }
  }

  std::cout << password << std::endl;
}

int main() {
  // clang-format off
    const char* row1[] = {"Algebra", "Analytical Geometry", "Mathematical analysis"};
    const char* row2[] = {"Data structures", "Introduction to programming", "Object oriented programming"};
    const char* row3[] = {"Data bases", "Artifical intelligence", "Functional programming"};
    const char** books[] = {row1, row2, row3};
  // clang-format on

  // We should print "Analytical Geometry" and "Introduction to programming" as
  // password, which gives us '10 8 12 2 11'. The 3rd row should be skipped,
  // since it is not sorted alphabetically

  revealPassword(books, 3, 3);
}

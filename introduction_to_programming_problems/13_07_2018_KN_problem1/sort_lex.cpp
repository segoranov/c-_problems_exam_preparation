#include <iostream>
#include <stack>
#include <string>

int fromChar(char c) { return c - 48; }

char fromInt(int i) { return i + 48; }

int compareLex(unsigned int lhs, unsigned int rhs) {
  std::stack<int> s1, s2;

  while (lhs != 0) {
    s1.push(lhs % 10);
    lhs /= 10;
  }

  while (rhs != 0) {
    s2.push(rhs % 10);
    rhs /= 10;
  }

  std::string str1, str2;

  while (!s1.empty()) {
    str1 += fromInt(s1.top());
    s1.pop();
  }

  while (!s2.empty()) {
    str2 += fromInt(s2.top());
    s2.pop();
  }

  if (str1 == str2)
    return 0;
  else if (str1 > str2)
    return 1;
  else
    return -1;
}

void swap(unsigned int& a, unsigned int& b) {
  unsigned int tmp = a;
  a = b;
  b = tmp;
}

void sortLex(unsigned int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    int max = i;
    for (int j = i + 1; j < n; j++) {
      if (compareLex(arr[max], arr[j]) == 1) {  // i.e. arr[j] > arr[max]
        max = j;
      }
    }
    swap(arr[max], arr[i]);
  }
}

void printArr(unsigned int arr[], int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::cout << compareLex(123, 9554) << std::endl;
  std::cout << compareLex(123, 123) << std::endl;
  std::cout << compareLex(9554, 123) << std::endl;

  unsigned int arr[] = {13, 14, 7, 2018, 9, 0};
  unsigned int arrSize = 6;
  printArr(arr, arrSize);
  sortLex(arr, arrSize);
  printArr(arr, arrSize);
}

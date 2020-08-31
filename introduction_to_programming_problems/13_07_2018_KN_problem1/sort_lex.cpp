#include <iostream>
#include <stack>
#include <string>

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

  while (!s1.empty() && !s2.empty()) {
    if (s1.top() < s2.top()) {
      return -1;
    } else if (s1.top() > s2.top()) {
      return 1;
    } else {  // equal
      s1.pop();
      s2.pop();
    }
  }

  if (!s2.empty()) {
    // '123' (s1) < '1234' (s2)
    return -1;
  }

  if (!s1.empty()) {
    return 1;
  }

  return 0;
}

int numberOfDigits(int x) {
  if (0 <= x && x <= 9) {
    return 1;
  }

  return 1 + numberOfDigits(x / 10);
}

int getNthDigit(int x, int n) {
  const int xNumDigits = numberOfDigits(x);
  if (n > xNumDigits)
    throw "Error: provided n is larger than the number of digits of x.";

  const int numberOfTimesToDivideByTen = xNumDigits - n;
  for (int i = 0; i < numberOfTimesToDivideByTen; ++i) {
    x /= 10;
  }
  return x % 10;
}

int compareLex1(unsigned int lhs, unsigned int rhs) {
  const int lhsNumDigits = numberOfDigits(lhs);
  const int rhsNumDigits = numberOfDigits(rhs);

  const int smallerNumDigits =
      (lhsNumDigits <= rhsNumDigits) ? lhsNumDigits : rhsNumDigits;

  for (int digitId = 1; digitId <= smallerNumDigits; digitId++) {
    const int lhsDigit = getNthDigit(lhs, digitId);
    const int rhsDigit = getNthDigit(rhs, digitId);
    if (lhsDigit > rhsDigit) return 1;
    if (rhsDigit > lhsDigit) return -1;
  }

  if (lhsNumDigits == rhsNumDigits) return 0;

  if (smallerNumDigits == lhsNumDigits)
    return -1;  // for example when we compare '123' and '1234'
  else
    return 1;  // for example when we compare '1234' and '123'
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
      if (compareLex1(arr[max], arr[j]) == 1) {  // i.e. arr[j] > arr[max]
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
  std::cout << compareLex1(123, 9554) << std::endl;
  std::cout << compareLex1(123, 123) << std::endl;
  std::cout << compareLex1(9554, 123) << std::endl;

  std::cout << compareLex1(1000, 100) << std::endl;
  std::cout << compareLex1(100, 1000) << std::endl;
  std::cout << compareLex1(100, 100) << std::endl;

  for (int i = 1; i <= 5; i++) {
    std::cout << i << "th digit of 12345: " << getNthDigit(12345, i) << '\n';
  }

  unsigned int arr[] = {13, 14, 7, 2018, 9, 0};
  unsigned int arrSize = 6;
  printArr(arr, arrSize);
  sortLex(arr, arrSize);
  printArr(arr, arrSize);
}

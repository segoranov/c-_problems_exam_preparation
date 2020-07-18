#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool areAnagrams(std::string str1, std::string str2) {
  if (str1.size() != str2.size()) {
    return false;
  }

  std::sort(str1.begin(), str1.end());
  std::sort(str2.begin(), str2.end());

  return str1 == str2;
}

int countAnagrams_v1(const char* word, int size, const char* words[]) {
  int result = 0;
  for (int i = 0; i < size; i++) {
    if (areAnagrams(word, words[i])) ++result;
  }

  return result;
}

int longestAnagramsCount_v1(int size, const char* words[]) {
  int maxAnagrams = 0;

  for (int i = 0; i < size; i++) {
    // words[i] -> c style string
    const int anagramsCount = countAnagrams_v1(words[i], size, words);
    if (anagramsCount > maxAnagrams) {
      maxAnagrams = anagramsCount;
    }
  }

  return maxAnagrams;
}

int countAnagrams_v2(const std::string& word,
                     const std::vector<std::string>& words) {
  int result = 0;
  for (const std::string& currentWord : words) {
    if (areAnagrams(word, currentWord)) ++result;
  }

  return result;
}

int longestAnagramsCount_v2(const std::vector<std::string>& words) {
  int maxAnagrams = 0;

  for (const std::string& word : words) {
    const int anagramsCount = countAnagrams_v2(word, words);
    if (anagramsCount > maxAnagrams) {
      maxAnagrams = anagramsCount;
    }
  }

  return maxAnagrams;
}

void test_v1() {
  const char* input[]{"string", "ginrts", "ringst", "strong",
                      "spong",  "shpong", "pongs"};
  std::cout << "TEST_v1 should be 3. Actual: "
            << longestAnagramsCount_v1(7, input) << std::endl;
}

void test_v2() {
  std::vector<std::string> input = {"string", "ginrts", "ringst", "strong",
                                    "spong",  "shpong", "pongs"};

  std::cout << "TEST_v2 should be 3. Actual: " << longestAnagramsCount_v2(input)
            << std::endl;
}

int main() {
  test_v1();
  test_v2();
}

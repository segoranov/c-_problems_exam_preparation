#include <iostream>

constexpr int MATRIX_SIZE = 3;

bool isBelowMainDiagonal(int x, int y) { return x >= y; }

bool isAboveSecondaryDiagonal(int x, int y) { return x + y <= MATRIX_SIZE; }

void updateMatrixWithAverageSymmetricValue(
    int x, int y, double matrix[MATRIX_SIZE][MATRIX_SIZE]) {
  // Some of the symmetric elements could be the same, for example if we
  // calculate symmetric elements for matrix[0][0]
  double& s1 = matrix[y][x];
  double& s2 = matrix[MATRIX_SIZE - 1 - x][MATRIX_SIZE - 1 - y];
  double& s3 = matrix[MATRIX_SIZE - 1 - y][MATRIX_SIZE - 1 - x];

  const double average = (matrix[x][y] + s1 + s2 + s3) / 4;
  matrix[x][y] = s1 = s2 = s3 = average;
}

void modifyMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      if (isBelowMainDiagonal(i, j) && isAboveSecondaryDiagonal(i, j)) {
        updateMatrixWithAverageSymmetricValue(i, j, matrix);
      }
    }
  }
}

void printMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void test() {
  std::cout << "\nBefore modification:\n";

  // clang-format off
    double testMatrix[MATRIX_SIZE][MATRIX_SIZE] =
    {
        {1, 9, 10},
        {1, 7, 8},
        {8, 6, 5}
    };
  // clang-format on

  printMatrix(testMatrix);

  std::cout << "\nAfter modification:\n";

  modifyMatrix(testMatrix);

  printMatrix(testMatrix);

  std::cout << "\n";
}

int main() { test(); }

#include <iostream>
#include <utility>
#include <cstring>

// Idea for solution: Start from the bottom right corner and move backwards by
// reversing the path. If the path contains 'N' (north), the backwards move is
// 'S' (south). If we reach a 'passable' cell, return true. False otherwise.

using Point = std::pair<int, int>;

bool isInLabyrinth(Point p, int labyrinthSize) {
  return (0 <= p.first && p.first < labyrinthSize) &&
         (0 <= p.second && p.second < labyrinthSize);
}

bool isPassable(Point p, int** labyrinth, int labyrinthSize) {
  return isInLabyrinth(p, labyrinthSize) && labyrinth[p.first][p.second] == 1;
}

bool isWall(Point p, int** labyrinth, int labyrinthSize) {
  return !isPassable(p, labyrinth, labyrinthSize);
}

Point getWestPoint(Point p) { return {p.first, p.second - 1}; }

Point getEastPoint(Point p) { return {p.first, p.second + 1}; }

Point getNorthPoint(Point p) { return {p.first - 1, p.second}; }

Point getSouthPoint(Point p) { return {p.first + 1, p.second}; }

bool makeMove(Point& currentPoint, Point nextPoint, int** labyrinth,
              int labyrinthSize) {
  if (!isInLabyrinth(nextPoint, labyrinthSize) ||
      isWall(nextPoint, labyrinth, labyrinthSize)) {
    return false;
  } else {
    currentPoint = nextPoint;  // make the move
    return true;
  }
}

bool makeReverseMove(char direction, Point& currentPoint, int** labyrinth,
                     int labyrinthSize) {
  switch (direction) {
    case 'N': {
      // moving south
      Point southPoint = getSouthPoint(currentPoint);
      if (!makeMove(currentPoint, southPoint, labyrinth, labyrinthSize)) {
        return false;
      }
      break;
    }
    case 'S': {
      // moving north
      Point northPoint = getNorthPoint(currentPoint);
      if (!makeMove(currentPoint, northPoint, labyrinth, labyrinthSize)) {
        return false;
      }
      break;
    }
    case 'W': {
      // moving east
      Point eastPoint = getEastPoint(currentPoint);
      if (!makeMove(currentPoint, eastPoint, labyrinth, labyrinthSize)) {
        return false;
      }
      break;
    }
    case 'E': {
      // moving west
      Point westPoint = getWestPoint(currentPoint);
      if (!makeMove(currentPoint, westPoint, labyrinth, labyrinthSize)) {
        return false;
      }
      break;
    }
    default: {
      throw "Invalid direction!";
    }
  }

  return true;
}

// path -> contains 'E', 'W', 'N', 'S'
bool walk(int** labyrinth, int labyrinthSize, const char* path) {
  const Point bottomRight{labyrinthSize - 1, labyrinthSize - 1};

  Point currentPoint = bottomRight;
  const int pathSize = std::strlen(path);
  for (int i = pathSize - 1; i >= 0; i--) {
    char direction = path[i];
    if (!makeReverseMove(direction, currentPoint, labyrinth, labyrinthSize)) {
      return false;
    }
  }

  return true;
}

// clang-format off
int** testLabyrinth1 = new int*[3]{
    new int[3]{1, 0 ,0},
    new int[3]{1, 0, 1},
    new int[3]{1, 1, 1}
};
// clang-format on

int main() {
  try {
    std::cout << "Is there path SSEE to bottom right in testLabyrinth1? : "
              << (walk(testLabyrinth1, 3, "SSEE") ? "YES\n" : "NO\n");

    std::cout << "Is there path SSEES to bottom right in testLabyrinth1? : "
              << (walk(testLabyrinth1, 3, "SSEES") ? "YES\n" : "NO\n");

    std::cout << "Is there path S to bottom right in testLabyrinth1? : "
              << (walk(testLabyrinth1, 3, "S") ? "YES\n" : "NO\n");

    std::cout << "Is there path SS to bottom right in testLabyrinth1? : "
              << (walk(testLabyrinth1, 3, "SS") ? "YES\n" : "NO\n");

    std::cout << "Is there path EE to bottom right in testLabyrinth1? : "
              << (walk(testLabyrinth1, 3, "EE") ? "YES\n" : "NO\n");
  } catch (const char* exc) {
    std::cout << "Exception: " << exc << std::endl;
  } catch (...) {
    std::cout << "Sorry, unhandled error." << std::endl;
  }
}

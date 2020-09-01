#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Graph {
 private:
  std::unordered_map<int, std::unordered_set<int>> adjList;

 public:
  void addEdge(int from, int to) {
    adjList[from].insert(to);
    adjList.insert({to, {}});
  }

  bool containsVertice(int v) const { return adjList.contains(v); }

  std::unordered_set<int> getNeighbors(int v) {
    if (!containsVertice(v)) throw "Non existent vertice";
    return adjList[v];
  }

  std::unordered_set<int> getVertices() {
    std::unordered_set<int> result;
    for (const auto& [vertice, neighbors] : adjList) {
      result.insert(vertice);
    }
    return result;
  }

  bool isConnected() {
    // I know that we perform twice more checks than needed, excuse me for the
    // inefficiency :-)
    for (const auto& v1 : getVertices()) {
      for (const auto& v2 : getVertices()) {
        if (!hasPath(v1, v2) && !hasPath(v2, v1)) return false;
      }
    }
    return true;
  }

  bool hasPath(int from, int to) {
    if (!containsVertice(from) || !containsVertice(to))
      throw "Non existent vertice.";

    if (from == to) return true;

    std::unordered_set<int> visited;
    return hasPath_rec(from, to, visited);
  }

 private:
  bool hasPath_rec(int from, int to, std::unordered_set<int>& visited) {
    visited.insert(from);
    if (from == to) return true;

    for (const auto& neighbor : getNeighbors(from)) {
      if (!visited.contains(neighbor) && hasPath_rec(neighbor, to, visited))
        return true;
    }

    return false;
  }
};

void test1() {
  std::cout << "test1()\n";
  Graph g;
  g.addEdge(1, 2);
  g.addEdge(2, 3);
  std::cout << "isConnected(): " << std::boolalpha << g.isConnected()
            << '\n';  // should be true
}

void test2() {
  std::cout << "test2()\n";
  Graph g;
  g.addEdge(2, 1);
  g.addEdge(2, 3);
  std::cout << "isConnected(): " << std::boolalpha << g.isConnected()
            << '\n';  // should be false
}

int main() {
  test1();
  test2();
}

#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

struct Node {
  Node(char sym, int val, const std::vector<Node*>& children = {})
      : c{sym}, v{val}, children{children} {}
  char c;
  int v;
  std::vector<Node*> children;

  bool isLeaf() const { return children.empty(); }
};

struct Branch {
  std::vector<Node*> p;
  std::string word() const {
    return std::accumulate(
        std::begin(p), std::end(p), std::string{},
        [](const std::string& acc, Node* node) { return acc + node->c; });
  }

  int value() const {
    return std::accumulate(std::begin(p), std::end(p), 0,
                           [](int acc, Node* node) { return acc + node->v; });
  }

  void addNode(Node* node) { p.push_back(node); }
  void removeLastNode() { p.pop_back(); }
};

namespace helpers {

void generateAllBranchesRec(Node* currentNode, std::vector<Branch>& paths,
                            Branch& currentBranch);

std::vector<Branch> generateAllBranches(Node* node) {
  if (!node) return {};

  std::vector<Branch> result;
  Branch currentBranch;
  generateAllBranchesRec(node, result, currentBranch);
  return result;
}

void generateAllBranchesRec(Node* currentNode, std::vector<Branch>& paths,
                            Branch& currentBranch) {
  currentBranch.addNode(currentNode);
  if (currentNode->isLeaf()) {
    paths.push_back(currentBranch);
  } else {
    for (auto child : currentNode->children) {
      generateAllBranchesRec(child, paths, currentBranch);
    }
  }

  currentBranch.removeLastNode();
}

auto getEqualWordBranchPairs(Node* u, Node* v) {
  auto branches_from_u = generateAllBranches(u);
  auto branches_from_v = generateAllBranches(v);

  std::vector<std::pair<Branch, Branch>> result;

  for (const Branch& branchU : branches_from_u) {
    for (const Branch& branchV : branches_from_v) {
      if (branchU.word() == branchV.word()) {
        result.push_back({branchU, branchV});
      }
    }
  }

  // Print for debugging
  for (const auto& branchPair : result) {
    std::cout << "Pair: <" << branchPair.first.word() << ", "
              << branchPair.second.word() << ">, <" << branchPair.first.value()
              << ", " << branchPair.second.value() << ">\n";
  }

  return result;
}

}  // namespace helpers

int sumVal(Node* u, Node* v) {
  auto pairsOfBranchesToSumUp = helpers::getEqualWordBranchPairs(u, v);

  int result = 0;
  for (const auto& branchPair : pairsOfBranchesToSumUp) {
    result += branchPair.first.value() + branchPair.second.value();
  }

  return result;
}

void printBranches(Node* root) {
  auto allBranches = helpers::generateAllBranches(root);
  for (const auto& branch : allBranches) {
    std::cout << "Branch: " << branch.word() << std::endl;
  }
}

int main() {
  Node* root = new Node{'a', 1};

  Node* v1 =
      new Node{'b',
               2,
               {new Node{'a', 1, {new Node{'b', 1, {new Node{'a', 1}}}}},
                new Node{'o', 1, {new Node{'b', 1}}},
                new Node{'e', 1, {new Node{'b', 1, {new Node{'e', 1}}}}}}};

  Node* v2 =
      new Node{'b',
               3,
               {new Node{'e', 4, {new Node{'b', 1, {new Node{'e', 1}}}}},
                new Node{'o', 1, {new Node{'b', 1}}},
                new Node{'e', 1, {new Node{'b', 1, {new Node{'e', 1}}}}}}};

  root->children.push_back(v1);
  root->children.push_back(v2);

  printBranches(root);

  int sum = sumVal(v1, v2);
  std::cout << "Sum: " << sum << std::endl;
}

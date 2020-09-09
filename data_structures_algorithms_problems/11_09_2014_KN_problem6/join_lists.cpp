#include <iostream>
#include <map>
#include <unordered_set>
#include <utility>

struct Node {
  Node(int data) : data{data} {}
  int data;
  Node* next = nullptr;
  Node* prev = nullptr;
};

void addElemAtEnd(Node*& list, int elem) {
  if (!list) {
    list = new Node{elem};
    return;
  }

  auto it = list;
  while (it->next != nullptr) {
    it = it->next;
  }

  it->next = new Node{elem};
  it->next->prev = it;
}

void printList(Node* list) {
  std::cout << "[ ";
  if (!list) return;
  while (list) {
    std::cout << list->data << ' ';
    list = list->next;
  }

  std::cout << "]\n";
}

int calcDistanceToEnd(Node* node) {
  if (!node) return 0;

  int dist = 0;
  while (node->next != nullptr) {
    node = node->next;
    ++dist;
  }

  return dist;
}

int calcDistanceToBeginning(Node* node) {
  if (!node) return 0;

  int dist = 0;
  while (node->prev != nullptr) {
    node = node->prev;
    ++dist;
  }

  return dist;
}

bool join(Node*& L1, Node*& L2) {
  using Distance = int;
  std::map<Distance, std::pair<Node*, Node*>> mapDistanceToNodePair;

  auto it1 = L1;
  auto it2 = L2;

  while (it1) {
    it2 = L2;
    while (it2) {
      const int d1 = calcDistanceToEnd(it1);
      const int d2 = calcDistanceToBeginning(it2);
      if (it1->data == it2->data && d1 == d2) {
        mapDistanceToNodePair[d1] = {it1, it2};
      }
      it2 = it2->next;
    }
    it1 = it1->next;
  }

  // If the map is empty, joining of lists is not possible
  // Otherwise mapDistanceToNodePair[0] will contain the pair of nodes with
  // minimum distance (the map is sorted by key)

  if (mapDistanceToNodePair.empty()) {
    return false;
  }

  const auto minDistance = mapDistanceToNodePair.begin()->first;
  const auto joiningNodeInL1 = mapDistanceToNodePair.begin()->second.first;
  const auto joiningNodeInL2 = mapDistanceToNodePair.begin()->second.second;

  std::cout << "Joining lists. Distance = " << minDistance
            << "; Data = " << joiningNodeInL1->data << '\n';

  // Join the two lists

  // forward it1 to the last node of L1
  it1 = L1;
  while (it1->next != nullptr) it1 = it1->next;

  // make it2 point to beginning of L2
  it2 = L2;

  it1->next =
      joiningNodeInL2;  // make last node of L1 point to 'joining' node in L2

  it2->prev =
      joiningNodeInL1;  // make first node of L2 point to 'joining' node in L1

  return true;
}

bool isJoined(Node* first /*, Node* last TODO SG: do we even need last??*/) {
  if (!first) {
    return false;
  }

  std::unordered_set<Node*> visited;

  auto it = first;
  while (it != nullptr && !visited.contains(it)) {
    visited.insert(it);
    if (it->prev && !visited.contains(it->prev)) {
      // reached an element from the other list
      return true;
    }
    it = it->next;
  }

  if (it != nullptr) {
    // we have made a cycle and returned to visited element, hence
    // the list is 'joined'
    return true;
  }

  return false;  // it == nullptr, reached the end of list
}

int sumJoined(Node* list) {
  if (!list) {
    return 0;
  }

  int sum = 0;

  std::unordered_set<Node*> visited;

  while (list) {
    sum += list->data;
    visited.insert(list);
    if (list->prev && !visited.contains(list->prev)) {
      // calcuate 'joined' part
      auto itPrev = list->prev;
      while (!visited.contains(itPrev)) {
        sum += itPrev->data;
        itPrev = itPrev->prev;
      }
    }

    list = list->next;
  }

  return sum;
}

int main() {
  Node* L1 = nullptr;
  addElemAtEnd(L1, 1);
  addElemAtEnd(L1, 3);
  addElemAtEnd(L1, 5);
  addElemAtEnd(L1, 7);
  addElemAtEnd(L1, 9);
  addElemAtEnd(L1, 6);

  std::cout << "L1: ";
  printList(L1);

  Node* L2 = nullptr;
  addElemAtEnd(L2, 3);
  addElemAtEnd(L2, 4);
  addElemAtEnd(L2, 8);
  addElemAtEnd(L2, 5);
  addElemAtEnd(L2, 7);

  std::cout << "L2: ";
  printList(L2);

  std::cout << "L1 is joined?: " << std::boolalpha << isJoined(L1) << '\n';
  std::cout << "L2 is joined?: " << std::boolalpha << isJoined(L1) << '\n';

  if (!join(L1, L2)) {
    std::cout << "Failed to join lists.\n";
  }

  std::cout << "L1 is joined?: " << std::boolalpha << isJoined(L1) << '\n';

  std::cout << "Sum of L1 (joined list!): " << sumJoined(L1);
  std::cout << "\nExpected sum: " << (1 + 3 + 5 + 7 + 9 + 6 + 5 + 8 + 4 + 3 + 7)
            << std::endl;
}

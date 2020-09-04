#include <iostream>

template <typename T>
struct Node {
  Node(const T& data) : data{data} {}
  T data;
  Node* next;
};

template <typename T>
void addElem(Node<T>*& list, const T& newElem) {
  if (!list) {
    list = new Node<T>{newElem};
    return;
  }

  Node<T>* it = list;
  while (it->next) {
    it = it->next;
  }

  // it->next == nullptr
  it->next = new Node<T>{newElem};
  it->next->next = nullptr;
}

template <typename T>
bool isSorted(Node<T>* list) {
  if (!list || !list->next) return true;

  auto it1 = list;
  auto it2 = it1->next;

  while (it2) {
    if (it1->data > it2->data) return false;
    it1 = it2;
    it2 = it2->next;
  }

  return true;
}

// Add add elements from l2 to l1
template <typename T>
void addAll(Node<T>*& l1, Node<T>* l2) {
  if (!l2) return;

  auto l2_it = l2;
  while (l2_it) {
    addElem(l1, l2_it->data);
    l2_it = l2_it->next;
  }
}

// Merg all sorted lists into one resulting in a newly created sorted list.
Node<int>* mergeSorted(Node<Node<int>*>* lists) {
  Node<int>* result = nullptr;

  while (lists) {
    auto currentList = lists->data;
    if (isSorted(currentList)) {
      addAll(result, currentList);
    }
    lists = lists->next;
  }

  return result;
}

// Prints list of int
void print(Node<int>* xs) {
  std::cout << "[ ";
  while (xs != nullptr) {
    std::cout << xs->data << ' ';
    xs = xs->next;
  }
  std::cout << "]\n";
}

// Prints list of lists of int
void print(Node<Node<int>*>* lists) {
  while (lists != nullptr) {
    print(lists->data);
    lists = lists->next;
  }
}

int main() {
  Node<int>* l1 = nullptr;  // sorted
  addElem(l1, 1);
  addElem(l1, 2);
  addElem(l1, 3);

  Node<int>* l2 = nullptr;  // not sorted
  addElem(l2, 4);
  addElem(l2, 6);
  addElem(l2, 5);

  Node<int>* l3 = nullptr;  // sorted
  addElem(l3, 7);
  addElem(l3, 8);
  addElem(l3, 9);

  Node<Node<int>*>* lists = nullptr;
  addElem(lists, l1);
  addElem(lists, l2);
  addElem(lists, l3);

  print(lists);
  std::cout << "After merging sorted: ";
  print(mergeSorted(lists));  // should print [ 1 2 3 7 8 9 ]
}

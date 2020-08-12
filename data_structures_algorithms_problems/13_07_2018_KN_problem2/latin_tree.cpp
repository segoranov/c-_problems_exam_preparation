#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

struct Node {
  Node(char c) : c{c} {}
  char c;
  std::vector<Node*> children;
};

bool isEmptyTree(Node* node) { return node->c == '!'; }

std::string readLast(Node* root) {
  if (!root) return "";

  std::queue<Node*> q;
  Node sentinel{'#'};
  Node* const pSentinel = &sentinel;

  q.push(root);
  q.push(pSentinel);

  std::string word;

  while (q.size() > 1) {  // size of 1 means only sentinel is left
    Node* cur = q.front();
    std::cout << "Front of queue: " << cur->c << '\n';
    q.pop();

    if (cur == pSentinel) {
      // prepare for next level word
      word.clear();
      q.push(pSentinel);
      std::cout << "Reset on sentinel...\n";
    } else {
      word += cur->c;
      for (auto child : cur->children) {
        if (!isEmptyTree(child)) q.push(child);
      }
    }
  }

  return word;
}

void serialize_rec(Node* cur, std::string& str);

void serialize(Node* root, const std::string& file) {
  std::ofstream ofs{file};
  if (!ofs) {
    throw std::runtime_error{"Could not open file " + file};
  }

  std::string serialized;
  serialize_rec(root, serialized);
  std::cout << "Serialization: " << serialized << '\n';
  ofs << serialized;
}

void serialize_rec(Node* cur, std::string& str) {
  if (isEmptyTree(cur)) {
    str += "*";
  } else {
    str += "(";
    str += cur->c;
    for (auto child : cur->children) {
      serialize_rec(child, str);
    }
    str += ")";
  }
}

int main() {
  // create test tree

  // level 0
  Node* b = new Node('b');  // root

  // level 1
  Node* x = new Node('x');
  Node* y = new Node('y');
  Node* e1 = new Node('!');  // empty tree

  // level 2
  Node* p = new Node('p');
  Node* q = new Node('q');
  Node* r = new Node('r');
  Node* e2 = new Node('!');  // empty tree
  Node* e3 = new Node('!');  // empty tree
  Node* s = new Node('s');

  // level 3
  Node* e4 = new Node('!');  // empty tree
  Node* e5 = new Node('!');  // empty tree
  Node* e6 = new Node('!');  // empty tree
  Node* e7 = new Node('!');  // empty tree
  Node* e8 = new Node('!');  // empty tree
  Node* e9 = new Node('!');  // empty tree
  Node* c = new Node('c');
  Node* e10 = new Node('!');  // empty tree
  Node* a = new Node('a');
  Node* e11 = new Node('!');  // empty tree
  Node* t = new Node('t');
  Node* e12 = new Node('!');  // empty tree

  // level 4
  Node* e13 = new Node{'!'};  // empty tree
  Node* e14 = new Node{'!'};  // empty tree
  Node* e15 = new Node{'!'};  // empty tree
  Node* e16 = new Node{'!'};  // empty tree
  Node* e17 = new Node{'!'};  // empty tree
  Node* e18 = new Node{'!'};  // empty tree
  Node* e19 = new Node{'!'};  // empty tree
  Node* e20 = new Node{'!'};  // empty tree
  Node* e21 = new Node{'!'};  // empty tree

  b->children = {x, y, e1};

  x->children = {p, q, r};
  y->children = {e2, e3, s};

  p->children = {e4, e5, e6};
  q->children = {e7, e8, e9};
  r->children = {c, e10, a};
  s->children = {e11, t, e2};

  c->children = {e13, e14, e15};
  a->children = {e16, e17, e18};
  t->children = {e19, e20, e21};

  auto lastLevelWord = readLast(b);
  std::cout << "Last level word: " << lastLevelWord << '\n';
  serialize(b, "serialized.txt");
}

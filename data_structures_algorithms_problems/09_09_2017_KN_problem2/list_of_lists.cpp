#include <iostream>

template <typename T>
struct Node {
    Node(const T& data) : data{data} {}
    T data;
    Node* next;
};

template <typename T>
void addElem(Node<T>*& list, const T& newElem) {
    if(!list) {
        list = new Node<T>{newElem};
        return;
    }

    Node<T>* it = list;
    while(it->next) {
        it = it->next;
    }

    // it->next == nullptr
    it->next = new Node<T>{newElem};
    it->next->next = nullptr;
}

// TODO
Node<int>* mergeAndSort(Node<Node<int>*> lists) {

}

// Prints list of int
void print(Node<int>* xs) {
    while(xs != nullptr) {
        std::cout << xs->data << ' ';
        xs = xs->next;
    }
    std::cout << '\n';
}

// Prints list of lists of int
void print(Node<Node<int>*>* lists) {
    while(lists != nullptr) {
        print(lists->data);
        lists = lists->next;
    }
}

int main()
{
    Node<int>* l1 = nullptr;
    addElem(l1, 1);
    addElem(l1, 2);
    addElem(l1, 3);

    Node<int>* l2 = nullptr;
    addElem(l2, 4);
    addElem(l2, 6);
    addElem(l2, 5);

    Node<Node<int>*>* lists = nullptr;
    addElem(lists, l1);
    addElem(lists, l2);

    print(lists);
}

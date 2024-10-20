#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
struct Node {
    T val;
    Node* next;
};

template <typename T>
struct Stack {
    Node<T>* head;
    Stack() {
        head = nullptr;
    }

    void push(T val) {
        Node<T>* newNode = new Node<T>{val, head};
        head = newNode;
    }

    void printbash() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->val;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }

    void pop() {
        if (head == nullptr) return;
        Node<T>* current = head->next;
        delete head;
        head = current;
    }

    T get() {
        if (head == nullptr) {
            throw runtime_error("Stack is empty");
        }
        return head->val;
    }
};

void task1();
void task3();
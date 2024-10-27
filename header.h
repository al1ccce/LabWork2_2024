#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <string>

using namespace std;

struct tNode{
    int value;
    tNode* left;
    tNode* right;

    tNode(int val) : value(val), left(nullptr), right(nullptr){}
};

template <typename K, typename V>
struct HashBucket {
    K key;
    V value;
    bool isDeleted;

    HashBucket() : isDeleted(false) {}
};

template <typename K, typename V>
struct HashTable {
    int size;
    int capacity;
    HashBucket<K, V>* table;

    HashTable(int cap) : size(0), capacity(cap) {
        table = new HashBucket<K, V>[capacity];
    }

    ~HashTable() {
        delete[] table;
    }

    int Hash1(const K& key) const {
        int hashz = 0;
        for (char c : key) {
            hashz += static_cast<int>(c);
        }
        return hashz % capacity;
    }

    int Hash2(int h) const {
        return 1 + (h % (capacity - 1));
    }

    int FinalHash(const K& key, int attempt) const {
        int h = Hash1(key);
        int g = Hash2(h);
        return (h + attempt * g) % capacity;
    }

    bool find(const K& key) const {
        int attempt = 0;
        int index;

        do {
            index = FinalHash(key, attempt);
            if (!table[index].isDeleted && table[index].key == key) {
                return true;
            }
            attempt++;
        } while (attempt < capacity);

        return false; // Возвращаем значение по умолчанию для типа V
    }

    void insert(const K& key, const V& value) {
        if (size >= capacity) {
            cout << "Таблица заполнена." << endl;
            return;
        }

        if (find(key) == true) {
            //cout << "Ключ уже существует." << endl;
            return;
        }

        int attempt = 0;
        int index;

        do {
            index = FinalHash(key, attempt);
            attempt++;
        } while (!table[index].key.empty() && !table[index].isDeleted);

        table[index].key = key;
        table[index].value = value;
        table[index].isDeleted = false;
        size++;
    }

    bool remove(const K& key) {
        int attempt = 0;
        int index;

        do {
            index = FinalHash(key, attempt);
            if (!table[index].isDeleted && table[index].key == key) {
                table[index].isDeleted = true;
                size--;
                cout << "Удалено." << endl;
                return true;
            }
            attempt++;
        } while (attempt < capacity);

        cout << "Ключ не найден." << endl;
        return false;
    }

    void printbash() const {
        for (int i = 0; i < capacity; i++) {
            if (!table[i].key.empty() && !table[i].isDeleted) {
                cout << table[i].key << " - " << table[i].value << endl;
            }
        }
    }

    void plusWorker(const K& key) {
        int attempt = 0;
        int index;

        do {
            index = FinalHash(key, attempt);
            if (!table[index].isDeleted && table[index].key == key) {
                table[index].value++;
                return;
            }
            attempt++;
        } while (attempt < capacity);
    }
};

struct FullBinaryTree {
    tNode* root;  

    FullBinaryTree(){
        root = nullptr;
    }
    void insert(tNode*& root, int value) {
        if (root == nullptr) {
            // Создаем новый узел, если дерево пустое
            tNode* newroot = new tNode(value);
            root = newroot;
            return;
        }
        if (value <= root->value) {
            // Рекурсивно добавляем в левое поддерево
            insert(root->left, value);
        } else {
            // Рекурсивно добавляем в правое поддерево
            insert(root->right, value);
        }

    }
    // Вернет nullptr, если отсутствует элемент
    tNode* search(int value) {
        return searchHelp(root, value);
    }
    tNode* searchHelp(tNode* node, int value) {
        if (node == nullptr || node->value == value) {
            return node;
        }

        if (value < node->value) {
            return searchHelp(node->left, value);
        } else {
            return searchHelp(node->right, value);
        }
    }

    void remove(int value) {
        root = removeHelp(root, value);
    }

    tNode* removeHelp(tNode* node, int value) {

        if (value < node->value) {
            node->left = removeHelp(node->left, value);
        } else if (value > node->value) {
            node->right = removeHelp(node->right, value);
        } else {
            // Узел имеет правого потомка
            if (node->left == nullptr) {
                tNode* temp = node->right;
                delete node;
                return temp; 
            // Узел имеет левого потомка
            } else if (node->right == nullptr) {
                tNode* temp = node->left;
                delete node;
                return temp; 
            }

            // Узел имеет двух детей
            tNode* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = removeHelp(node->right, temp->value);
        }
        return node;
    }

    tNode* minValueNode(tNode* node) {
        tNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    void printbash(){
        printbabash(root, 0);
    }

    void printbabash(tNode* root, int level){
        if (root != nullptr)
        {
            printbabash(root->right, level + 1);
            for (int i = 0; i < level; i++) cout << "   ";
            cout << root->value << endl;
            printbabash(root->left, level + 1);
        }
    }
};

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

template <typename T>
struct Vector {
    int size;
    int capacity;
    T* vec;

    Vector(int cap = 10){
        size = 0;
        capacity = cap;
        vec = new T[capacity];
    }

    void resize() {
        if (size < capacity) return;
        capacity *= 2;
        T* newVec = new T[capacity];
        for (int i = 0; i < size; ++i) {
            newVec[i] = vec[i];
        }
        delete[] vec;
        vec = newVec;
    }

    void push_back(T value) {
        resize();
        vec[size] = value; // Копируем строку
        ++size;
    }

    bool find(T value) {
        for (int i = 0; i < size; i++){
            if (vec[i] == value){
                return true;
            }
        }
        return false;
    }

    void printbash() {
        for (int i = 0; i < size; i++) {
            cout << vec[i] << " ";
        }
        cout << endl;
    }
};


void task1();
void task4();
void task5();
void task6();

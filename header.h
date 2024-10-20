#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

struct HashBucket {
    string key;
    bool isDeleted; 

};

struct set {
    int size;
    int capacity;
    HashBucket* table;

    set(int cap) : size(0), capacity(cap) {
        table = new HashBucket[capacity];
    }

    ~set() {
        delete[] table;
    }

    int Hash1(const string& key) const {
        int hashz = 0;
        for (char c : key) {
            hashz += static_cast<int>(c);
        }
        return hashz % capacity;
    }

    int Hash2(int h) const {
        return 1 + (h % (capacity - 1));
    }

    int FinalHash(const string& key, int attempt) const {
        int h = Hash1(key);
        int g = Hash2(h);
        return (h + attempt * g) % capacity;
    }

    bool find(const string& key) const {
        int attempt = 0;
        int index;

        do {
            index = FinalHash(key, attempt);
            if (!table[index].isDeleted && table[index].key == key) {
                return true;
            }
            attempt++;
        } while (attempt < capacity && !table[index].key.empty());

        return false;
    }

    void insert(const string& key) {
        if (size >= capacity) {
            cout << "Таблица заполнена." << endl;
            return;
        }

        if (find(key)) {
            //cout << "Ключ уже существует." << endl;
            return;
        }

        int attempt = 0;
        int index;

        do {
            index = FinalHash(key, attempt);
            if (table[index].key.empty() || table[index].isDeleted) {
                table[index].key = key;
                table[index].isDeleted = false; // Сбрасываем флаг удаления
                size++;
                return;
            }
            attempt++;
        } while (attempt < capacity);

    }

    bool remove(const string& key) {
        int attempt = 0;
        int index;

        do {
            index = FinalHash(key, attempt);
            if (!table[index].isDeleted && table[index].key == key) {
                table[index].isDeleted = true; // Помечаем ячейку как удаленную
                size--;
                cout << "Удалено." << endl;
                return true;
            }
            attempt++;
        } while (attempt < capacity && !table[index].key.empty());

        cout << "Ключ не найден." << endl;
        return false;
    }
    
    set unification(set& Set){
        int newcap = capacity + Set.capacity;
        set Union (newcap);
        for (int i = 0; i < capacity; i++) {
            if (!table[i].key.empty() && !table[i].isDeleted) {
                Union.insert(table[i].key);
            }
        }

    // Добавляем все элементы из другой таблицы в новую таблицу
        for (int i = 0; i < Set.capacity; i++) {
            if (!Set.table[i].key.empty() && !Set.table[i].isDeleted) {
                Union.insert(Set.table[i].key);
            }
        }
        return Union;
    }

    set intersection(set& Set){
        int newcap = capacity;
        set Inter(newcap);
        for (int i = 0; i < capacity; i++) {
            if (!table[i].key.empty() && !table[i].isDeleted && Set.find(table[i].key)) {
                Inter.insert(table[i].key);
            }
        }
        return Inter;
    }

    set difference(set& Set) {
        set diff(capacity);

        for (int i = 0; i < capacity; i++) {
            if (!table[i].key.empty() && !table[i].isDeleted && !Set.find(table[i].key)) {
                diff.insert(table[i].key);
            }
        }

    return diff;
}

    void print(const string& file, const string& namestruct) const {
        ofstream out;
        out.open(file);
        out << namestruct << endl;
        for (int i = 0; i < capacity; i++) {
            if (!table[i].key.empty() && !table[i].isDeleted) {
                out << table[i].key << ' ';
            }
        }
    }

    void printbash() const {
        for (int i = 0; i < capacity; i++) {
            if (!table[i].key.empty() && !table[i].isDeleted) {
                cout << i << " - " << table[i].key << endl;
            } else {
                cout << i << " - EMPTY" << endl;
            }
        }
    }
};

void addStructName(string file, string namestruct);
void hashFromFile(string file,  set &table);
string getResName(string namestruct, string file2, string secretword);
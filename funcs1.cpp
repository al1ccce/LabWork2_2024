#include "header.h"

int prior(char c) {
    switch (c) {
        case ')': return 777;
        case '^': case '|': return 4;
        case '&': return 3;
        case '!': return 2;
        case '(': return 1;
    }
    return 10;
}

void whileNotSkobka(Stack<char>& ops, string& polsky) {
    while (ops.head != nullptr && ops.get() != '(') {
        polsky += ops.get();
        ops.pop();
    }
    if (ops.head != nullptr) {
        ops.pop(); // Удаляем открывающую скобку
    }
}

void isHigher(Stack<char>& ops, int sw, char c, string& polsky) {
    while (ops.head != nullptr && prior(ops.get()) >= sw) {
        polsky += ops.get();
        ops.pop();
    }
    ops.push(c);
}

void createPolsky(string& polsky, Stack<char>& ops) {
    while (ops.head != nullptr) {
        polsky += ops.get();
        ops.pop();
    }
}

int chooseOp(char op, int a, int b) {
    switch (op) {
        case '&': return a & b;
        case '|': return a | b;
        case '^': return a ^ b;
        default: throw runtime_error("Unknown operator");
    }
}

void task1(){
    string str = "!(1 & !1)";
    cout << str << endl;
    string polsky = "";
    Stack<char> ops;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') continue;
        int sw = prior(str[i]);
        if (sw == 10) {
            polsky += str[i];
        } else if (sw == 1) {
            ops.push(str[i]);
        } else if (sw == 777) {
            whileNotSkobka(ops, polsky);
        } else {
            isHigher(ops, sw, str[i], polsky);
        }
    }
    createPolsky(polsky, ops);
    cout << polsky << endl;

    Stack<int> opers;
    for (int i = 0; i < polsky.size(); i++) {
        if (polsky[i] == '0' || polsky[i] == '1') {
            int num = static_cast<int>(polsky[i] - '0');
            opers.push(num);
        } else if (polsky[i] == '!') {
            int froms = opers.get();
            opers.pop();
            froms = !froms;
            opers.push(froms);
        } else {
            int froms1 = opers.get();
            opers.pop();
            int froms2 = opers.get();
            opers.pop();
            int res = chooseOp(polsky[i], froms2, froms1);
            opers.push(res);
        }
    }

    cout << opers.get() << endl;
}

void task4(){
    Vector<char> syms;
    for (int i = 33; i <= 41; ++i) {
        syms.push_back(static_cast<char>(i));
    }
    for (int i = 43; i <= 47; ++i) {
        syms.push_back(static_cast<char>(i));
    }
    for (int i = 58; i <= 62; ++i) {
        syms.push_back(static_cast<char>(i));
    }
    syms.push_back(static_cast<char>(64));
    string templ = "*?stud.nstu.??";
    cout << templ << endl;
    string da = "meow@stud.nstu.co";
    cout << da << endl;
    int i = 0, j = 0;
    while (i < da.size() && j < templ.size()) {
        if (da[i] == templ[j] || templ[j] == '?') {
            i++;
            j++;
        } else if (templ[j] == '*') {
            while (i < da.size() && !syms.find(da[i])) {
                i++;
            }
            j++;
        } else {
            cout << "Сломался на символе шаблона " << templ[j] << " и символе строки " << da[i] << endl;
            cout << "No.\n";
            return;
        }
    }

    while (j < templ.size() && templ[j] == '*') {
        j++;
    }

    if (i == da.size() && j == templ.size()) {
        cout << "Yes.\n";
    } else {
        cout << "No.\n";
    }
}

void task5(){
    cout << "elements: ";
    int el;
    FullBinaryTree tree;
    while(true){
        cin >> el;
        if (el == 0){
            break;
        }
        tree.insert(tree.root, el);
    }
    tree.printbash();
    cout << "delete: ";
    cin >> el;
    if (tree.search(el) == nullptr){
        cout << "Элемент отсутствует в дереве" << endl;
    }
    else{
        tree.remove(el);
        tree.printbash();
    }
    
}

void countRecursive(const HashTable<string, string>& baza, const string& manager, HashTable<string, int>& bazacount) {
    int count = 0;
    for (int i = 0; i < baza.capacity; i++) {
        if (!baza.table[i].key.empty() && !baza.table[i].isDeleted && baza.table[i].value == manager) {
            count++;
            countRecursive(baza, baza.table[i].key, bazacount);
        }
    }
    bazacount.plusWorker(manager);
}

void task6(){
    cout << "Пар:";
    int capa;
    cin >> capa;

    HashTable<string,string> baza(capa*2);
    HashTable <string, int> bazacount(capa*2);
    for (int i = 0; i < capa; i++){
        cout << "сотрудник - менеджер:";
        string key;
        string val;
        cin >> key >> val;
        baza.insert(key, val);
        bazacount.insert(key, 0);
        bazacount.insert(val, 0);
    }
    capa = capa * 2;

    for (int i = 0; i < capa; i++){
        if (!baza.table[i].key.empty() && !baza.table[i].isDeleted){
            string manager = baza.table[i].value;
            if (baza.table[i].key == baza.table[i].value){
                bazacount.plusWorker(manager);
            }
            bazacount.plusWorker(manager);
        }
    }
    bazacount.printbash();
}

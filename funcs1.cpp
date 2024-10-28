#include "header.h"


int prior(char op) {
    if (op == '!') return 3; // highest
    if (op == '&') return 2;
    if (op == '|') return 1;
    if (op == '^') return 2; // XOR
    return 0;
}

void toPolsky(const string& infix, string& polsky) {
    Stack<char> opStack;
    stringstream ss(infix);
    string element;

    while (ss >> element) {
        if (element == "0" || element == "1") { // operands
            polsky += element + " ";
        } else if (element[0] == '(') {
            opStack.push(element[0]);
        } else if (element[0] == ')') {
            while (!opStack.isEmpty() && opStack.get() != '(') {
                polsky += opStack.get();
                polsky += " "; 
                opStack.pop();
            }
            opStack.pop(); // pop '('
        } else { // операторы
            while (!opStack.isEmpty() && prior(opStack.get()) >= prior(element[0])) {
                polsky += opStack.get();
                polsky += " ";
                opStack.pop();
            }
            opStack.push(element[0]);
        }
    }

    while (!opStack.isEmpty()) {
        polsky += opStack.get();
        polsky += " "; 
        opStack.pop();
    }
}

bool chooseOp(char op, bool a, bool b) {
    switch (op) {
        case '&': return a && b; // AND
        case '|': return a || b; // OR
        case '^': return a ^ b;   // XOR
        default: throw runtime_error("Unknown operator");
    }
}

bool solvePolsky(const string& polsky) {
    Stack<bool> valueStack;
    stringstream ss(polsky);
    string element;

    while (ss >> element) {
        if (element == "0") {
            valueStack.push(false);
        } else if (element == "1") {
            valueStack.push(true);
        } else {
            bool right = valueStack.get(); 
            valueStack.pop();
            bool result;

            if (element == "!") {
                result = !right; 
                valueStack.push(result);
            } else {
                bool left = valueStack.get(); 
                valueStack.pop();
                result = chooseOp(element[0], left, right); // Теперь используем chooseOp
                valueStack.push(result);
            }
        }
    }
    return valueStack.get(); // возвращаем окончательный результат
}

void task1() {
    string infix = "( 1 ^ 0 ) & ( 0 | 1 )";
    string polsky;
    cout << infix << endl;

    toPolsky(infix, polsky);
    cout << polsky << endl;

    bool result = solvePolsky(polsky);
    cout << result << endl;

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
    string templ = "*.el?o";
    cout << templ << endl;
    string da = "HHHhhh.ello";
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

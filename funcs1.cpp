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
    string str = "(1 & 0) | (1 ^ 0)";
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

void task3(){
    string templ = "*@stud.nstu.?";
    cout << templ;
    string da = "meow@stud.nstu.com"

}

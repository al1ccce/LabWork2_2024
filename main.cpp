#include "header.h"

int main() {
    int task;
    cout << "task: ";
    try {
        cin >> task;
    } catch (...) {
        cerr << "error\n";
        return 0;
    }

    switch(task){
        case 1: 
            task1();
            break;
        case 3:
            task3();
        default:
            cout << "incorrect task\n";
            break;
    }
    return 0;
}
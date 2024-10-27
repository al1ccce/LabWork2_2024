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
        case 4:
            task4();
            break;
        case 5:
            task5();
            break;
        case 6:
            task6();
            break;
        default:
            cout << "incorrect task\n";
            break;
    }
    return 0;
}

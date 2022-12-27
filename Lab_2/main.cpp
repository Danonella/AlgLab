#include <iostream>
#include "Array.h"
#include "Bit.h"
#include "List.h"
#include "MachineWord.h"

using namespace std;

bool *SetCreate() {
    bool *set = new bool[33];
    for (int i = 0; i < 33; i++) {
        if (rand() % 2) {
            set[i] = true;
        } else {
            set[i] = false;
        }
    }
    return set;
}

int main() {
    wcout << "\n\tTask: (A || B) \\ (C & D)\n";

    srand(time(0));
    setlocale(LC_CTYPE, "rus");
    bool **set = new bool *[4];

    for (int i = 0; i < 4; i++) {
        set[i] = SetCreate();
    }

    Array array = Array(set[0], set[1], set[2], set[3]);
    array.print();

    List list = List(set[0], set[1], set[2], set[3]);
    list.print();

    Bit bit = Bit(set[0], set[1], set[2], set[3]);
    bit.print();

    MachineWord machineWord = MachineWord(set[0], set[1], set[2], set[3]);
    machineWord.print();

    delete [] set;

    return 0;
}

#pragma once

using namespace std;

class MachineWord {
private:
    wchar_t alphabet[34] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    int CONST = 1000000;
    clock_t wordStart, wordEnd;
    bool *A, *B, *C, *D;
    long long wordA = 0, wordB = 0, wordC = 0, wordD = 0, wordE = 0;

public:
    void print() {
        wcout << endl << "\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i];
        }
        wcout << "\n\tWordA    = ";
        for (int i = 0; i < 33; i++) {
            wcout << ((wordA >> i) & 1LL);
        }

        wcout << endl << "\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i];
        }
        wcout << endl << "\tWordB    = ";
        for (int i = 0; i < 33; i++) {
            wcout << ((wordB >> i) & 1LL);
        }

        wcout << endl << "\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i];
        }
        wcout << endl << "\tWordC    = ";
        for (int i = 0; i < 33; i++) {
            wcout << ((wordC >> i) & 1LL);
        }

        wcout << endl << "\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i];
        }
        wcout << endl << "\tWordD    = ";
        for (int i = 0; i < 33; i++) {
            wcout << ((wordD >> i) & 1LL);
        }

        wcout << endl << "\n\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i];
        }
        wcout << endl << "\tWordE    = ";
        for (int i = 0; i < 33; i++) {
            wcout << ((wordE >> i) & 1LL);
        }

        wcout << "\n\tTime Machine word:\t" << (wordEnd - wordStart) / 1000.0 << endl;
    }

    void initWord() {
        for (int i = 0; i < 33; i++) {
            if (A[i]) {
                wordA |= (1LL << i);
            }
            if (B[i]) {
                wordB |= (1LL << i);
            }
            if (C[i]) {
                wordC |= (1LL << i);
            }
            if (D[i]) {
                wordD |= (1LL << i);
            }
        }
    }

    MachineWord(bool *a, bool *b, bool *c, bool *d) : A(a), B(b), C(c), D(d) {
        initWord();

        wordStart = clock();
        for (int k = 0; k < CONST; k++) {
            wordE = ((wordA | wordB) | (wordC & wordD)) ^ (wordC & wordD);
        }
        wordEnd = clock();
    }
};

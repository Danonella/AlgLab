#pragma once

using namespace std;

class Bit {
private:
    wchar_t alphabet[34] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    int CONST = 1000000;
    clock_t bitStart, bitEnd;
    unsigned int bitA[33], bitB[33], bitC[33], bitD[33], bitE[33];
    bool *A, *B, *C, *D;


public:
    void print() {
        wcout << endl << "\n\t---Bit---\n";

        wcout << endl << "\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i] << " ";
        }
        wcout << "\n\tBitA     = ";
        for (unsigned int i : bitA) {
            wcout << i << " ";
        }

        wcout << endl << "\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i] << " ";
        }
        wcout << endl << "\tBitB     = ";
        for (unsigned int i : bitB) {
            wcout << i << " ";
        }

        wcout << endl << "\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i] << " ";
        }
        wcout << endl << "\tBitC     = ";
        for (unsigned int i : bitC) {
            wcout << i << " ";
        }

        wcout << endl << "\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i] << " ";
        }
        wcout << endl << "\tBitD     = ";
        for (unsigned int i : bitD) {
            wcout << i << " ";
        }

        wcout << endl << "\n\tUniverse = ";
        for (int i = 0; i < 33; i++) {
            wcout << alphabet[i] << " ";
        }
        wcout << endl << "\tBitE     = ";
        for (unsigned int i : bitE) {
            wcout << i << " ";
        }

        wcout << "\n\tTime Bit:\t" << (bitEnd - bitStart) / 1000.0 << endl;
    }

    void initBit() {
        for (int i = 0; i < 33; i++) {
            bitA[i] = A[i];
            bitB[i] = B[i];
            bitC[i] = C[i];
            bitD[i] = D[i];
        }
    }

    Bit(bool *a, bool *b, bool *c, bool *d) : A(a), B(b), C(c), D(d) {
        initBit();

        bitStart = clock();
        for (int k = 0; k < CONST; k++) {
            for (int i = 0; i < 33; i++) {
                bitE[i] = (bitA[i] || bitB[i]) && !(bitC[i] && bitD[i]);
            }
        }
        bitEnd = clock();
    }
};
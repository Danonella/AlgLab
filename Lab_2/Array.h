#pragma once

using namespace std;

class Array {
private:
    wchar_t alphabet[34] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    int CONST = 1000000;
    clock_t arrStart, arrEnd;
    int lenA = 0, lenB = 0, lenC = 0, lenD = 0, lenAB = 0, lenCD = 0;
    int check;
    wchar_t *arrayA, *arrayB, *arrayC, *arrayD, arrayE[33], *arrayAB, *arrayCD;
    bool *A, *B, *C, *D;

    void calcLen() {
        for (int i = 0; i < 33; i++) {
            if (A[i]) {
                lenA += 1;
            }
            if (B[i]) {
                lenB += 1;
            }
            if (C[i]) {
                lenC += 1;
            }
            if (D[i]) {
                lenD += 1;
            }
        }

        lenAB = min(33, lenA + lenB), lenCD = min(lenC, lenD);
        arrayA = new wchar_t[lenA];
        arrayB = new wchar_t[lenB];
        arrayC = new wchar_t[lenC];
        arrayD = new wchar_t[lenD];
        arrayAB = new wchar_t[lenAB];
        arrayCD = new wchar_t[lenCD];
    }

public:
    void print() {
        wcout << "\n\t---Array---\n\n";


        wcout << "\tArrayA = ";
        for (int i = 0; i<lenA; i++) {
            wcout << arrayA[i];
        }

        wcout << endl << "\tArrayB = ";
        for (int i = 0; i<lenB; i++) {
            wcout << arrayB[i];
        }

        wcout << endl << "\tArrayC = ";
        for (int i = 0; i<lenC; i++) {
            wcout << arrayC[i];
        }

        wcout << endl << "\tArrayD = ";
        for (int i = 0; i<lenD; i++) {
            wcout << arrayD[i];
        }

        wcout << endl << "\n\tArrayE = ";
        for (int i = 0; i < check; i++) {
            wcout << arrayE[i];
        }
        wcout << "\n\tTime Array:\t" << (arrEnd - arrStart) / 1000.0 << endl;
    }

    void initArr() {
        int h = 0, n = 0;
        while (h < lenA) {
            if (A[n]) {
                arrayA[h] = alphabet[n];
                arrayAB[h] = alphabet[n];
                h++;
            }
            n++;
        }

        h = 0, n = 0;
        while (h < lenB) {
            if (B[n]) {
                arrayB[h] = alphabet[n];
                h++;
            }
            n++;
        }

        h = 0, n = 0;
        while (h < lenC) {
            if (C[n]) {
                arrayC[h] = alphabet[n];
                h++;
            }
            n++;
        }

        h = 0, n = 0;
        while (h < lenD) {
            if (D[n]) {
                arrayD[h] = alphabet[n];
                h++;
            }
            n++;
        }
    }

    Array(bool *a, bool *b, bool *c, bool *d) : A(a), B(b), C(c), D(d) {
        calcLen();
        initArr();

        arrStart = clock();
        bool flag;

        for (int k = 0; k < CONST; k++) {
            flag = true;
            check = lenA;

            for (int i = 0; i < lenB; i++) {
                for (int p = 0; p < lenA; p++) {
                    if (arrayB[i] == arrayAB[p]) {
                        flag = false;
                    }
                }
                if (flag) {
                    arrayAB[check] = arrayB[i];
                    check++;
                }
                flag = true;
            }

            lenAB = check;
            flag = false;
            check = 0;

            for (int i = 0; i < lenC; i++) {
                for (int p = 0; p < lenD; p++) {
                    if (arrayC[i] == arrayD[p]) {
                        flag = true;
                        break;
                    }
                }
                if (flag) {
                    arrayCD[check] = arrayC[i];
                    check++;
                }
                flag = false;
            }

            lenCD = check;
            flag = true;
            check = 0;

            for (int i = 0; i < lenAB; i++) {
                for (int p = 0; p < lenCD; p++) {
                    if (arrayAB[i] == arrayCD[p]) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    arrayE[check] = arrayAB[i];
                    check++;
                }
                flag = true;
            }
        }
        arrEnd = clock();
    }
};
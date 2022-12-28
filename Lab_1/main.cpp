#include <iostream>

using namespace std;

wchar_t alphabet[34] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
int CONST = 1000000;

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


struct SList {
    wchar_t el;
    SList *next;

    SList(wchar_t e, SList *n = nullptr) : el(e), next(n) {}
};

SList *setToList(const bool *set) {
    SList *list = nullptr;
    for (int i = 0; i < 33; i++)
        if (set[i])
            list = new SList(alphabet[i], list);
    return list;
}

void clearMemory(SList* basket) {
    while (basket != nullptr) {
        SList* elNext = basket -> next;
        delete basket;
        basket = elNext;
    }
}

int main() {
    wcout << "\n\tTask: (A || B) \\ (C & D)\n";

    srand(time(0));
    setlocale(LC_CTYPE, "rus");
    bool **set = new bool *[4];
    int lenA = 0, lenB = 0, lenC = 0, lenD = 0;

    // ARRAY

    wcout << "\n\t---Array---\n\n";

    for (int i = 0; i < 4; i++) {
        set[i] = SetCreate();
    }

    for (int i = 0; i < 33; i++) {
        if (set[0][i]) {
            lenA += 1;
        }
        if (set[1][i]) {
            lenB += 1;
        }
        if (set[2][i]) {
            lenC += 1;
        }
        if (set[3][i]) {
            lenD += 1;
        }
    }

    int lenAB = min(33, lenA+lenB), lenCD = min(lenC, lenD);
    wchar_t arrayA[lenA], arrayB[lenB], arrayC[lenC], arrayD[lenD], arrayE[33], arrayAB[lenAB], arrayCD[lenCD];

    wcout << "\tArrayA = ";
    int h = 0, j = 0;
    while (h < lenA) {
        if (set[0][j]) {
            arrayA[h] = alphabet[j];
            arrayAB[h] = alphabet[j];
            wcout << arrayA[h];
            h++;
        }
        j++;
    }

    wcout << endl << "\tArrayB = ";
    h = 0, j = 0;
    while (h < lenB) {
        if (set[1][j]) {
            arrayB[h] = alphabet[j];
            wcout << arrayB[h];
            h++;
        }
        j++;
    }

    wcout << endl << "\tArrayC = ";
    h = 0, j = 0;
    while (h < lenC) {
        if (set[2][j]) {
            arrayC[h] = alphabet[j];
            wcout << arrayC[h];
            h++;
        }
        j++;
    }

    wcout << endl << "\tArrayD = ";
    h = 0, j = 0;
    while (h < lenD) {
        if (set[3][j]) {
            arrayD[h] = alphabet[j];
            wcout << arrayD[h];
            h++;
        }
        j++;
    }

    wcout << endl;

    clock_t arrStart = clock();
    bool flag;

    for (int k = 0; k < CONST; k++) {
        flag = true;
        j = lenA;
        for (int i = 0; i < lenB; i++) {
            for (int p = 0; p < lenA; p++) {
                if (arrayB[i] == arrayAB[p]) {
                    flag = false;
                }
            }
            if (flag) {
                arrayAB[j] = arrayB[i];
                j++;
            }
            flag = true;
        }

        lenAB = j;

        flag = false;
        j = 0;
        for (int i = 0; i < lenC; i++) {
            for (int p = 0; p < lenD; p++) {
                if (arrayC[i] == arrayD[p]) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                arrayCD[j] = arrayC[i];
                j++;
            }
            flag = false;
        }

        lenCD = j;

        flag = true;
        j = 0;
        for (int i = 0; i < lenAB; i++) {
            for (int p = 0; p < lenCD; p++) {
                if (arrayAB[i] == arrayCD[p]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                arrayE[j] = arrayAB[i];
                j++;
            }
            flag = true;
        }
    }

    clock_t arrEnd = clock();

    wcout << "\n\tArrayE = ";
    for (int i = 0; i < j; i++) {
        wcout << arrayE[i];
    }

    wcout << "\n\tTime Array:\t" << (arrEnd - arrStart) / 1000.0 << endl;

    // LIST

    wcout << endl << "\n\t---List---\n";

    SList *listA = setToList(set[0]);
    SList *listB = setToList(set[1]);
    SList *listC = setToList(set[2]);
    SList *listD = setToList(set[3]);
    SList *listCD, *listAB;
    SList *currList;
    SList *listE;

    wcout << "\n\tListA = ";
    currList = listA;
    while (currList != nullptr) {
        wcout << currList->el;
        currList = currList->next;
    }

    wcout << endl << "\tListB = ";
    currList = listB;
    while (currList != nullptr) {
        wcout << currList->el;
        currList = currList->next;
    }

    wcout << endl << "\tListC = ";
    currList = listC;
    while (currList != nullptr) {
        wcout << currList->el;
        currList = currList->next;
    }

    wcout << endl << "\tListD = ";
    currList = listD;
    while (currList != nullptr) {
        wcout << currList->el;
        currList = currList->next;
    }

    clock_t listStart = clock();
    for (int k = 0; k <= CONST; k++) {

        listCD = nullptr;
        listAB = nullptr;
        currList = listA;

        while (currList != nullptr) {
            listAB = new SList(currList->el, listAB);
            currList = currList->next;
        }

        for (SList *c = listC; c; c = c->next) {
            for (SList *d = listD; d; d = d->next) {
                if (c->el == d->el) {
                    listCD = new SList(c->el, listCD);
                }
            }
        }

        for (SList *b = listB; b; b = b->next) {
            bool check = true;
            for (SList *ab = listAB; ab; ab = ab->next) {
                if (ab->el == b->el) {
                    check = false;
                    break;
                }
            }
            if (check) {
                listAB = new SList(b->el, listAB);
            }
        }

        listE = nullptr;

        for (SList *ab = listAB; ab; ab = ab->next) {
            bool check = true;
            for (SList *cd = listCD; cd; cd = cd->next) {
                if (ab->el == cd->el) {
                    check = false;
                    break;
                }
            }
            if (check) {
                listE = new SList(ab->el, listE);
            }
        }

        clearMemory(listAB);

        clearMemory(listCD);

        if (k != CONST) {
            clearMemory(listE);
        }
    }
    clock_t listEnd = clock();

    wcout << endl << "\n\tListE = ";
    currList = listE;
    while (currList != nullptr) {
        wcout << currList->el;
        currList = currList->next;
    }

    clearMemory(listA);

    clearMemory(listB);

    clearMemory(listC);

    clearMemory(listD);

    clearMemory(listE);

    wcout << "\n\tTime List:\t" << (listEnd - listStart) / 1000.0 << endl;

    // BIT

    wcout << endl << "\n\t---Bit---\n";

    unsigned int bitA[33], bitB[33], bitC[33], bitD[33], bitE[33];

    for (int i = 0; i < 33; i++) {
        bitA[i] = set[0][i];
        bitB[i] = set[1][i];
        bitC[i] = set[2][i];
        bitD[i] = set[3][i];
    }

    clock_t bitStart = clock();
    for (int k = 0; k < CONST; k++) {
        for (int i = 0; i < 33; i++) {
            bitE[i] = (bitA[i] || bitB[i]) && !(bitC[i] && bitD[i]);
        }
    }
    clock_t bitEnd = clock();

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

    // Machine word

    wcout << endl << "\n\t---Machine word---\n";

    long long wordA, wordB, wordC, wordD, wordE;
    wordA = 0;
    wordB = 0;
    wordC = 0;
    wordD = 0;

    for (int i = 0; i < 33; i++) {
        if (set[0][i]) {
            wordA |= (1LL << i);
        }
        if (set[1][i]) {
            wordB |= (1LL << i);
        }
        if (set[2][i]) {
            wordC |= (1LL << i);
        }
        if (set[3][i]) {
            wordD |= (1LL << i);
        }
    }

    clock_t wordStart = clock();
    for (int k = 0; k < CONST; k++) {
        wordE = ((wordA | wordB) | (wordC & wordD)) ^ (wordC & wordD);
    }
    clock_t wordEnd = clock();

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

    delete [] set;

    return 0;
}

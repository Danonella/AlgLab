#pragma once

using namespace std;

class List {
private:
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

    wchar_t alphabet[34] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    int CONST = 10000;
    clock_t listStart, listEnd;
    bool *A, *B, *C, *D;
    SList *listA, *listB, *listC, *listD, *listCD, *listAB, *currList, *listE;

public:
    void print() {
        wcout << endl << "\n\t---List---\n";

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

        wcout << endl << "\n\tListE = ";
        currList = listE;
        while (currList != nullptr) {
            wcout << currList->el;
            currList = currList->next;
        }

        wcout << "\n\tTime List:\t" << (listEnd - listStart) / 1000.0 << endl;

        clearMemory(listA);
        clearMemory(listB);
        clearMemory(listC);
        clearMemory(listD);
        clearMemory(listE);
    }

    void initList() {
        listA = setToList(A);
        listB = setToList(B);
        listC = setToList(C);
        listD = setToList(D);
    }

    void clearMemory(SList* basket) {
        while (basket != nullptr) {
            SList* elNext = basket -> next;
            delete basket;
            basket = elNext;
        }
    }

    List(bool *a, bool *b, bool *c, bool *d) : A(a), B(b), C(c), D(d) {
        initList();

        listStart = clock();
        for (int k = 0; k <= CONST; k++) {

            listCD = nullptr;
            listAB = nullptr;
            currList = listA;

            while (currList != nullptr) {
                listAB = new SList(currList->el, listAB);
                currList = currList->next;
            }

            for (SList *elC = listC; elC; elC = elC->next) {
                for (SList *elD = listD; elD; elD = elD->next) {
                    if (elC->el == elD->el) {
                        listCD = new SList(elC->el, listCD);
                    }
                }
            }

            for (SList *elB = listB; elB; elB = elB->next) {
                bool check = true;
                for (SList *elAB = listAB; elAB; elAB = elAB->next) {
                    if (elAB->el == elB->el) {
                        check = false;
                        break;
                    }
                }
                if (check) {
                    listAB = new SList(elB->el, listAB);
                }
            }

            listE = nullptr;

            for (SList *elAB = listAB; elAB; elAB = elAB->next) {
                bool check = true;
                for (SList *elCD = listCD; elCD; elCD = elCD->next) {
                    if (elAB->el == elCD->el) {
                        check = false;
                        break;
                    }
                }
                if (check) {
                    listE = new SList(elAB->el, listE);
                }
            }

            clearMemory(listAB);

            clearMemory(listCD);

            if (k != CONST) {
                clearMemory(listE);
            }
        }
        listEnd = clock();
    }
};
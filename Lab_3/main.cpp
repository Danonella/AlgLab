#include <iostream>
#include <string.h>
#include <random>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Node {
    char d; // тег узла
    Node *lft; // левый сын
    Node *mdl; // средний сын
    Node *rgt; // правый сын
public:
    Node() : lft(nullptr), mdl(nullptr), rgt(nullptr) {} //конструктор узла
    ~Node() { // деструктор узла
        if (lft) delete lft;
        if (mdl) delete mdl;
        if (rgt) delete rgt;
    }

    friend class Tree; // дружественный класс дерево
};

class Tree {
    Node *root;    // указатель на корень дерева
    char num, maxNum;        //счётчик тегов и максимальный тег
    int maxRow, offSet;        //максимальная глубина, смещение корня
    char **screen;    // память для выдачи на экран
    void clearMemory();    // очистка рабочей памяти
    Node *makeNode(int depth);    // создание поддерева
    void outNodes(Node *v, int r, int c); // выдача поддерева
    Tree(const Tree &);    // фиктивный конструктор копии
    Tree operator=(const Tree &) const = delete;    // присваивание
public:
    unordered_map<char, int> nodeParentsCount;

    Tree(char nm, char mnm, int mxr);

    ~Tree();

    void makeTree() {// ввод — генерация дерева
        root = makeNode(0);
    }

    bool exist() { // проверка «дерево не пусто»
        return root != nullptr;
    }

    int bfs();    // обход «в ширину»
    void outTree();    // выдача на экран
};

Tree::Tree(char nm, char mnm, int mxr) :
        num(nm), maxNum(mnm), maxRow(mxr), offSet(40), root(nullptr),
        screen(new char *[maxRow]) { for (int i = 0; i < maxRow; ++i) screen[i] = new char[80]; }

Tree::~Tree() {
    for (int i = 0; i < maxRow; ++i) delete[]screen[i];
    delete[]screen;
    delete root;
}

Node *Tree::makeNode(int depth) {
    Node *v = nullptr;
    int Y = (depth < rand() % 6 + 1) && (num <= 'z');
    cout << num << " " << Y << endl;
    if (Y) {    // создание узла, если Y = 1
        v = new Node;
        v->d = num++;     // разметка в прямом порядке (= «в глубину»)
        v->lft = makeNode(depth + 1);
        v->mdl = makeNode(depth + 1);
        v->rgt = makeNode(depth + 1);
    }
    return v;
}

void Tree::outTree() {
    clearMemory();
    outNodes(root, 1, offSet);
    for (int i = 0; i < maxRow; i++) {
        screen[i][79] = 0;
        cout << "\n" << screen[i];
    }
    cout << "\n";
}

void Tree::clearMemory() {
    for (int i = 0; i < maxRow; i++) {
        memset(screen[i], '.', 80);
    }
}

void Tree::outNodes(Node *v, int r, int c) {
    if (r && c && (c < 80)) screen[r - 1][c - 1] = v->d; // вывод метки
    if (r < maxRow) {
        if (v->lft) outNodes(v->lft, r + 1, c - (offSet >> r)); //левый сын
        if (v->mdl) outNodes(v->mdl, r + 1, c);    // средний сын
        if (v->rgt) outNodes(v->rgt, r + 1, c + (offSet >> r)); //правый сын
    }
}

template<class Item>
class Queue {
    Item *Q;
    int h, t, N;
public:
    Queue(int maxQ) : h(0), t(0), N(maxQ), Q(new Item[maxQ + 1]) {}

    int empty() const { return (h % N) == t; }

    void push(Item item) {
        Q[t++] = item;
        t %= N;
    }

    Item pop() {
        h %= N;
        return Q[h++];
    }
};


int Tree::bfs() {
    const int maxQ = 100; //максимальный размер очереди
    int count = 0;
    int current_depth = 0;
    Queue<Node *> Q(maxQ);  //создание очереди указателей на узлы
    Q.push(root); // Queue <- root поместить в очередь корень дерева
    char lastIterDepthElement = root->d;
    Node *depthLastRightChild = root;
    while (!Q.empty()) //пока очередь не пуста
    {
        Node *v = Q.pop();// взять из очереди,
        cout << v->d << '_';
        nodeParentsCount[v->d] = current_depth;
        count++; // выдать тег, счёт узлов
        if (v->lft) Q.push(v->lft); // Queue <- (левый сын)
        if (v->mdl) Q.push(v->mdl); // Queue <- (средний сын)
        if (v->rgt) Q.push(v->rgt); // Queue <- (правый сын)

        Node *tempLastChildren = (v->rgt) ? v->rgt : (v->mdl) ? v->mdl : (v->lft) ? v->lft : nullptr;
        if (tempLastChildren != nullptr) depthLastRightChild = tempLastChildren;
        if (v->d == lastIterDepthElement) {

            if (depthLastRightChild != nullptr) {
                lastIterDepthElement = depthLastRightChild->d;
                depthLastRightChild = nullptr;
                current_depth++;
            }
        }
    }
    return count;
}

bool comp(pair<char, int> a, pair<char, int> b) {
    return a.second < b.second;
}

int main() {
    int n = 0;
    Tree tree('a', 'z', 8);
    srand(time(nullptr));
    tree.makeTree();
    if (tree.exist()) {
        tree.outTree();
        cout << "\n" << "Depth-First Search: ";
        n = tree.bfs();
        cout << " Nodes passed = " << n << endl;
        cout << "Parent count: " << endl;
        vector<pair<char, int>> elems(tree.nodeParentsCount.begin(), tree.nodeParentsCount.end());
        sort(elems.begin(), elems.end(), comp);
        for (pair<const char, int> nodeName: elems) {
            cout << nodeName.first << ": " << nodeName.second << " ";
        }
    } else cout << "The Tree is empty!";
    cout << "\n" << "=== The end ===";
    return 0;
}


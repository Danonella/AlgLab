#include <iostream>
#include <string.h>
#include <random>
#include <unordered_map>
#include <algorithm>

using namespace std;

int choice;

class Node {
    char d;
    Node *lft;
    Node *mdl;
    Node *rgt;
public:
    Node() : lft(nullptr), mdl(nullptr), rgt(nullptr) {}
    ~Node() {
        if (lft) delete lft;
        if (mdl) delete mdl;
        if (rgt) delete rgt;
    }

    friend class Tree;
};

class Tree {
    Node *root;
    char num, maxNum;
    int maxRow, offSet;
    char **screen;
    void clearMemory();
    Node *makeNode(int depth);
    void outNodes(Node *v, int r, int c);
    Tree(const Tree &);
    Tree operator=(const Tree &) const = delete;
public:
    unordered_map<char, int> nodeParentsCount;

    Tree(char nm, char mnm, int mxr);

    ~Tree();

    void makeTree() {
        root = makeNode(0);
    }

    bool exist() {
        return root != nullptr;
    }

    int bfs();
    void outTree();
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
    int Y;

    if (choice == 1) {
        Y = (depth < rand() % 6 + 1) && (num <= 'z');
    } else {
        cout << "Node (" << num << ',' << depth << ")1/0:";
        cin >> Y;
    }

    if (Y) {
        v = new Node;
        v->d = num++;
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
    if (r && c && (c < 80)) screen[r - 1][c - 1] = v->d;
    if (r < maxRow) {
        if (v->lft) outNodes(v->lft, r + 1, c - (offSet >> r));
        if (v->mdl) outNodes(v->mdl, r + 1, c);
        if (v->rgt) outNodes(v->rgt, r + 1, c + (offSet >> r));
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
    const int maxQ = 100;
    int count = 0;
    int current_depth = 0;
    Queue<Node *> Q(maxQ);
    Q.push(root);
    char lastIterDepthElement = root->d;
    Node *depthLastRightChild = root;
    while (!Q.empty())
    {
        Node *v = Q.pop();
        cout << v->d << '_';
        nodeParentsCount[v->d] = current_depth;
        count++;
        if (v->lft) Q.push(v->lft);
        if (v->mdl) Q.push(v->mdl);
        if (v->rgt) Q.push(v->rgt);

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
    cout << "Choose the type of data entry:\n";
    cout << "1. Generation\n2. Manual input\n";
    cin >> choice;

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


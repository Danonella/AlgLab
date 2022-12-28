#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

// Структура данных для хранения ребра Graph
struct Edge {
    int src, dest;
};

// Класс для представления graph-объекта
class Graph {
public:
    vector<vector<int>> adjList;
    vector<int> in;
    vector<Edge> inpEdges;
    int size = 0;

    // Конструктор Graphа
    Graph(int n, vector<Edge> const &edges = {}) {
        adjList.resize(n);
        in.resize(n);
        inpEdges.resize(n);
        inpEdges = edges;
        size = n;
        for (auto &edge: edges) {
            addEdge(edge.src, edge.dest);
        }
    }

    bool hasEulerianCycle(int n);

    void buildEulerianCycle(int vertex, int edges);


private:
    void addEdge(int u, int v);

    void DFS(int u, vector<bool> &visited);

    Graph buildTranspose(int n);

    bool isSC(int n);

    bool isVisited(const vector<bool> &visited);

    vector<vector<int>> getMatrix(int n) {
        vector<vector<int>> output;
        output.resize(n, vector<int>(n));

        for (Edge edj: inpEdges) {
            output[edj.src][edj.dest] = 1;
        }
        return output;
    }

};

// Вспомогательная функция для добавления ребра (u, v) к графу
void Graph::addEdge(int u, int v) {
    adjList[u].push_back(v);
    in[v]++;
}

// Обход в глубину
void Graph::DFS(int u, vector<bool> &visited) {
    visited[u] = true;

    for (int v: adjList[u]) {
        if (!visited[v]) {
            DFS(v, visited);
        }
    }
}

// Создание траспонированного графа
Graph Graph::buildTranspose(int n) {
    Graph g(n);

    for (int u = 0; u < n; u++) {
        for (int v: adjList[u]) {
            g.addEdge(u, v);
        }
    }
    return g;
}

// Проверка посещаемости всех вершин графа с ненулевой степенью
bool Graph::isVisited(const vector<bool> &visited) {
    for (int i = 0; i < visited.size(); i++) {
        if (adjList[i].size() && !visited[i]) {
            return false;
        }
    }
    return true;
}

// Алгоритм Косарайю
bool Graph::isSC(int n) {
    vector<bool> visited(n);
    int i;
    for (i = 0; i < n; i++) {
        if (adjList[i].size()) {
            DFS(i, visited);
            break;
        }
    }

    if (!isVisited(visited)) {
        return false;
    }

    fill(visited.begin(), visited.end(), false);
    Graph g = buildTranspose(n);
    DFS(i, visited);

    return isVisited(visited);
}

// Проверка на наличие эйлерова цикла
bool Graph::hasEulerianCycle(int n) {
    for (int i = 0; i < n; i++) {
        if (adjList[i].size() != in[i]) {
            return false;
        }
    }

    return isSC(n);
}

// Построение эйлерова цикла
void Graph::buildEulerianCycle(int vertex, int edges) {
    vector<int> vertexOfEulerianCycle(edges + 1);
    stack<int> S;
    S.push(vertex);
    vector<vector<int>> gr = getMatrix(size);
    int i = 0;

    while (!S.empty()) {
        int w = S.top();
        bool fe = false;

        for (int u = 0; u < in.size(); ++u) {
            if (gr[w][u] != 0) {
                S.push(u);
                gr[w][u] = 0;
                fe = true;
                break;
            }
        }

        if (!fe) {
            S.pop();
            vertexOfEulerianCycle[i] = w;
            i++;
        }
    }
    reverse(vertexOfEulerianCycle.begin(), vertexOfEulerianCycle.end());

    for (int currVert: vertexOfEulerianCycle) {
        cout << currVert << " ";
    }
}

// Генерация графов
vector<Edge> generateTests(int countVertex, int countEdges) {
    vector<Edge> edges;
    int a, b;

    while (edges.size() < countEdges) {
        a = rand() % countVertex;
        b = rand() % countVertex;
        Edge createdEdge = {a, b};
        bool containsEdge = false;
        for (Edge edge: edges) {
            if ((edge.src == a && edge.dest == b) || (edge.src == b && edge.dest == a)) {
                containsEdge = true;
                break;
            }
        }
        if (!containsEdge && (a != b)) {
            cout << a << " " << b << endl;
            edges.push_back(createdEdge);
        }
    }
    vector<Edge> output;
    output.assign(edges.begin(), edges.end());
    return output;
}

int main() {
    srand(time(nullptr));
    vector<Edge> edges;
    int countVertex, countEdges, a, b, choice, maxCountEdges;

    cout << "Choose the type of data entry:\n";
    cout << "1. Generation\n2. Manual input\n";
    cin >> choice;

    if (choice == 1) {
        countVertex = rand() % 10 + 2;
        cout << "Number of vertex:\n" << countVertex;
        maxCountEdges = (countVertex * (countVertex - 1)) / 2;
        countEdges = rand() % maxCountEdges + 1;
        cout << "\nNumber of edges:\n" << countEdges;
        cout << "\nGraph:\n";
        edges = generateTests(countVertex, countEdges);
    } else {
        cout << "Enter number of vertex:\n";
        cin >> countVertex;

        cout << "Enter number of edges:\n";
        cin >> countEdges;

        cout << "Enter edges like:  1 2\nVertices are numbered starting from 0\n";
        for (int i = 0; i < countEdges; i++) {
            cin >> a >> b;
            edges.push_back({a, b});
        }
    }

    Graph graph(countVertex, edges);

    if (graph.hasEulerianCycle(countVertex)) {
        cout << "The graph has an Eulerian cycle:" << endl;
        graph.buildEulerianCycle(0, countEdges);
    } else {
        cout << "The Graph does not contain Eulerian cycle" << endl;
    }

    return 0;
}
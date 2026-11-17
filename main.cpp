#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
using Edges = vector<tuple<int, int, int>>;

void compareAlgorithms(int n, const Edges& edges, int start);

bool readGraph(const string& filename, int& n, int& start, Edges& edges) {
    ifstream file(filename);
    int m;
    if (!(file >> n >> m >> start) || n <= 0 || m < 0 || start < 0 || start >= n)
        return false;

    edges.clear();
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        if (!(file >> u >> v >> w) || u < 0 || u >= n || v < 0 || v >= n || w < 0)
            return false;
        edges.emplace_back(u, v, w);
    }

    string extra;
    return !(file >> extra); // Лишние данные в конце файла запрещены.
}

int main(int argc, char* argv[]) {
    vector<string> files = {
        "graph_small.txt", "graph_large_weights.txt", "graph_disconnected.txt",
        "graph_many_vertices.txt", "graph_dense.txt"
    };
    if (argc > 1) files.assign(argv + 1, argv + argc);

    for (const string& filename : files) {
        int n, start;
        Edges edges;
        if (!readGraph(filename, n, start, edges)) {
            cerr << "Ошибка чтения графа: " << filename << '\n';
            continue;
        }

        cout << "\nFILE=" << filename << " V=" << n
             << " E=" << edges.size() << " START=" << start << '\n';
        compareAlgorithms(n, edges, start);
    }
}

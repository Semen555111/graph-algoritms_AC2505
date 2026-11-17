#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
using Edges = vector<tuple<int, int, int>>;
using Distances = vector<long long>;

// Все алгоритмы получают одинаковые входные данные и возвращают расстояния.
namespace dijkstra { Distances shortestPaths(int, const Edges&, int); }
namespace bellman_ford { Distances shortestPaths(int, const Edges&, int); }
namespace floyd_warshall { Distances shortestPaths(int, const Edges&, int); }
namespace levit { Distances shortestPaths(int, const Edges&, int); }
namespace johnson { Distances shortestPaths(int, const Edges&, int); }

struct Algorithm {
    const char* name;
    Distances (*run)(int, const Edges&, int);
};

// Выводим только первые 10 расстояний, чтобы не загромождать консоль.
void printDistances(const Distances& distances) {
    const long long INF = numeric_limits<long long>::max() / 4;
    cout << " DIST:";
    for (size_t i = 0; i < distances.size() && i < 10; ++i) {
        if (distances[i] == INF) cout << " INF";
        else cout << ' ' << distances[i];
    }
    if (distances.size() > 10) cout << " ...";
    cout << '\n';
}

void compareAlgorithms(int n, const Edges& edges, int start) {
    const Algorithm algorithms[] = {
        {"Dijkstra", dijkstra::shortestPaths},
        {"Bellman-Ford", bellman_ford::shortestPaths},
        {"Floyd-Warshall", floyd_warshall::shortestPaths},
        {"Levit", levit::shortestPaths},
        {"Johnson", johnson::shortestPaths}
    };

    Distances reference; // Результат первого реализованного алгоритма.
    for (const Algorithm& algorithm : algorithms) {
        try {
            auto begin = chrono::steady_clock::now();
            Distances distances = algorithm.run(n, edges, start);
            auto end = chrono::steady_clock::now();

            if (distances.size() != static_cast<size_t>(n) || distances[start] != 0)
                throw runtime_error("INVALID_RESULT");

            double ms = chrono::duration<double, milli>(end - begin).count();
            cout << left << setw(16) << algorithm.name << " ALGO_MS="
                 << fixed << setprecision(4) << ms;

            if (reference.empty()) {
                reference = distances;
                cout << " BASELINE";
            } else {
                cout << (distances == reference ? " MATCH" : " MISMATCH");
            }
            printDistances(distances);
        } catch (const exception& error) {
            cout << algorithm.name << " " << error.what() << '\n';
        }
    }
}

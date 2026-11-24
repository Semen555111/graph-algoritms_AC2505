#include <vector>
#include <tuple>

#include "shortest_path.h"

// Реализацию алгоритма участник пишет самостоятельно.
// Не меняйте имя функции, параметры и тип результата.
namespace floyd_warshall {

std::vector<long long> shortestPaths(
    int n,
    const std::vector<std::tuple<int, int, int>>& edges,
    int start
) {
    std::vector<std::vector<long long>> Q(n, std::vector<long long>(n, INF));

    for (int i = 0; i < n; i++) {
        Q[i][i] = 0;
    }

    for (const auto& [u, v, w] : edges) {
        long long weight = static_cast<long long>(w);
        if (weight < Q[u][v]) {
            Q[u][v] = weight;
            Q[v][u] = weight;
        }
    }
    
    for (int k = 0; k < n; k++) { 
        for (int i = 0; i < n; i++) {
            if (Q[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (Q[k][j] == INF) continue;
                long long new_w = Q[i][k] + Q[k][j];
                if (new_w < Q[i][j]) {
                    Q[i][j] = new_w;
                }
                }
            }
        }
    

    return Q[start];
}
}


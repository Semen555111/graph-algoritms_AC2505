
#include <vector>
#include <tuple>

#include "shortest_path.h"

namespace bellman_ford {

std::vector<long long> shortestPaths(
    int n,
    const std::vector<std::tuple<int, int, int>>& edges,
    int start
) {
    std::vector<long long> dist(n, INF);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool changed = false;

        for (const auto& [u, v, w] : edges) {

            // Путь из u в v
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = true;
            }

            // Путь из v в u (граф неориентированный)
            if (dist[v] != INF && dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                changed = true;
            }
        }

        if (!changed) {
            break;
        }
    }

    return dist;
}

}

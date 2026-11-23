
#include <vector>
#include <tuple>
#include <queue>
#include <functional>
#include <utility>

#include "shortest_path.h"

namespace dijkstra {

std::vector<long long> shortestPaths(
    int n,
    const std::vector<std::tuple<int, int, int>>& edges,
    int start
) {

    std::vector<std::vector<std::pair<int, long long>>> graph(n);

    // Заполняем граф рёбрами
    for (const auto& [u, v, w] : edges) {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    // Изначально все расстояния бесконечны
    std::vector<long long> dist(n, INF);
    dist[start] = 0;

    using Node = std::pair<long long, int>;

    std::priority_queue<
        Node,
        std::vector<Node>,
        std::greater<Node>
    > pq;

    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (currentDist != dist[u]) {
            continue;
        }
        for (const auto& [v, weight] : graph[u]) {
            long long newDist = currentDist + weight;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                pq.push({newDist, v});
            }
        }
    }

    return dist;
}

}

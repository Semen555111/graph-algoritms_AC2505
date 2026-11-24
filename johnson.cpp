#include <vector>
#include <tuple>
#include <limits>
#include <queue>

#include "shortest_path.h"

namespace johnson {

std::vector<long long> shortestPaths(
    int n,
    const std::vector<std::tuple<int, int, int>>& edges,
    int start
) {
    const long long INF = std::numeric_limits<long long>::max() / 4;

    std::vector<long long> h(n + 1, INF);
    h[n] = 0;

    for (int i = 0; i < n; ++i) {
        bool updated = false;
        for (const auto& [u, v, w] : edges) {
            if (h[u] != INF && h[u] + w < h[v]) {
                h[v] = h[u] + w;
                updated = true;
            }
            if (h[v] != INF && h[v] + w < h[u]) {
                h[u] = h[v] + w;
                updated = true;
            }
        }
        if (!updated) break;
    }

    std::vector<std::vector<std::pair<int, long long>>> adj(n);
    for (const auto& [u, v, w] : edges) {
        long long new_w = (long long)w + h[u] - h[v];
        adj[u].push_back({v, new_w});
        adj[v].push_back({u, new_w});
    }

    std::vector<long long> dist_new(n, INF);
    std::priority_queue<
        std::pair<long long, int>, 
        std::vector<std::pair<long long, int>>, 
        std::greater<>
    > pq;
    
    dist_new[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist_new[u]) continue;

        for (const auto& [v, weight] : adj[u]) {
            if (dist_new[u] + weight < dist_new[v]) {
                dist_new[v] = dist_new[u] + weight;
                pq.push({dist_new[v], v});
            }
        }
    }

    std::vector<long long> result(n, INF);
    for (int i = 0; i < n; ++i) {
        if (dist_new[i] != INF) {
            result[i] = dist_new[i] - h[start] + h[i];
        }
    }

    return result;
}

}
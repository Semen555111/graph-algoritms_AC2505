#ifndef SHORTEST_PATHS_H
#define SHORTEST_PATHS_H

#include <vector>
#include <tuple>
#include <limits>

constexpr long long INF =
    std::numeric_limits<long long>::max() / 4;
std::vector<long long> shortestPaths(
    int n,
    const std::vector<std::tuple<int, int, int>>& edges,
    int start
);

#endif


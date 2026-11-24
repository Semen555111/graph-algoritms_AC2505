#include <vector>
#include <tuple>
#include <queue>
#include <limits>
#include <utility>

namespace levit {

    std::vector<long long> shortestPaths(
        int vertexCount,
        const std::vector<std::tuple<int, int, int>>& edges,
        int startVertex
    ) {
        const long long INF =
            std::numeric_limits<long long>::max() / 4;

        std::vector<std::vector<std::pair<int, int>>> graph(vertexCount);

        for (const auto& [fromVertex, toVertex, weight] : edges) {
            graph[fromVertex].push_back({ toVertex, weight });
            graph[toVertex].push_back({ fromVertex, weight });
        }

        std::vector<long long> distance(vertexCount, INF);
        std::vector<int> vertexState(vertexCount, 0);

        std::queue<int> mainQueue;
        std::queue<int> urgentQueue;

        distance[startVertex] = 0;
        vertexState[startVertex] = 1;
        mainQueue.push(startVertex);

        while (!mainQueue.empty() || !urgentQueue.empty()) {
            int currentVertex;

            if (!urgentQueue.empty()) {
                currentVertex = urgentQueue.front();
                urgentQueue.pop();
            }
            else {
                currentVertex = mainQueue.front();
                mainQueue.pop();
            }

            vertexState[currentVertex] = 2;

            for (const auto& [neighborVertex, edgeWeight] : graph[currentVertex]) {
                long long newDistance =
                    distance[currentVertex] + edgeWeight;

                if (newDistance >= distance[neighborVertex])
                    continue;

                distance[neighborVertex] = newDistance;

                if (vertexState[neighborVertex] == 0) {
                    mainQueue.push(neighborVertex);
                    vertexState[neighborVertex] = 1;
                }
                else if (vertexState[neighborVertex] == 2) {
                    urgentQueue.push(neighborVertex);
                    vertexState[neighborVertex] = 1;
                }
            }
        }

        return distance;
    }

}

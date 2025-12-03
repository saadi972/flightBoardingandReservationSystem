#include "../include/graph.h"
#include <queue>
#include <limits>
#include <algorithm>  // for std::reverse

void Graph::addEdge(std::string src, std::string dest, int weight) {
    adj[src].push_back({dest, weight});
}

std::vector<std::string> Graph::shortestPath(std::string start, std::string end) {

    std::map<std::string, int> dist;
    std::map<std::string, std::string> parent;

    for (auto &p : adj)
        dist[p.first] = INT_MAX;

    dist[start] = 0;

    std::priority_queue<
        std::pair<int, std::string>,
        std::vector<std::pair<int, std::string>>,
        std::greater<std::pair<int, std::string>>
    > pq;

    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if (node == end)
            break;

        for (auto &edge : adj[node]) {
            auto [next, weight] = edge;

            if (d + weight < dist[next]) {
                dist[next] = d + weight;
                parent[next] = node;
                pq.push({dist[next], next});
            }
        }
    }

    std::vector<std::string> path;
    std::string cur = end;

    while (cur != "") {
        path.push_back(cur);
        if (parent.find(cur) == parent.end()) break;
        cur = parent[cur];
    }

    std::reverse(path.begin(), path.end());
    return path;
}

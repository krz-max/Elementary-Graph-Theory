#include <bits/stdc++.h>

#define ll long long

class UnionFind
{
public:
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }
    ~UnionFind() {}
    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

ll minCost(std::vector<std::tuple<int, int, int>> &edges, int cities)
{
    int n = cities;
    UnionFind uf(n);
    ll totalCost = 0;

    // Kruskal's algorithm to find the minimum spanning tree
    for (const auto &edge : edges)
    {
        int u, v;
        ll cost;
        std::tie(u, v, cost) = edge;

        if (uf.find(u) != uf.find(v))
        {
            uf.unionSets(u, v);
            totalCost += cost;
        }
    }

    return totalCost;
}

int main()
{
    int Q;
    std::cin >> Q;

    for (int q = 0; q < Q; ++q)
    {
        int n, m;
        std::cin >> n >> m;

        std::vector<int> cities(n);
        for (int i = 0; i < n; ++i)
        {
            std::cin >> cities[i];
        }
        std::vector<std::vector<int>> adjList(n, std::vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                adjList[i][j] = adjList[j][i] = cities[i] + cities[j];
            }
        }
        for (int i = 0; i < m; ++i)
        {
            int x, y, z;
            std::cin >> x >> y >> z;
            adjList[x - 1][y - 1] = adjList[y - 1][x - 1] = std::min(adjList[x - 1][y - 1], z);
        }
        std::vector<std::tuple<int, int, int>> edges;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; ++j)
            {
                edges.emplace_back(i, j, adjList[i][j]);
            }
        }
        std::sort(edges.begin(), edges.end(), [](const auto &a, const auto &b)
                  { return std::get<2>(a) < std::get<2>(b); });
        std::cout << minCost(edges, n) << std::endl;
        // std::cout << "Minimum cost for query " << q + 1 << ": " << result << std::endl;
    }

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005; // Maximum number of nodes

vector<int> adj[MAXN];
int height[MAXN];
int parent[MAXN];

void dfs(int node, int par) {
    height[node] = 0; // Initialize height of leaf node to 0
    parent[node] = par;

    for (int child : adj[node]) {
        if (child != par) {
            dfs(child, node);
            height[node] = max(height[node], 1 + height[child]); // Update height based on children
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    cin >> n;

    // Initialize adjacency list
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS to compute heights and parents
    dfs(1, -1);

    // Output heights and parents
    for (int i = 1; i <= n; ++i) {
        cout << height[i] << " " << parent[i] << endl;
    }

    return 0;
}

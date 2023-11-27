#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005; // Maximum number of nodes

class Solution
{
private:
    int num_of_nodes;
    vector<int> height;
    vector<int> parent;
    vector<vector<int>> adjList;

public:
    Solution()
    {
        cin >> num_of_nodes;
        // Initialize adjacency list
        height.resize(num_of_nodes + 1);
        parent.resize(num_of_nodes + 1);
        adjList.resize(num_of_nodes + 1);
        for (int i = 1; i <= num_of_nodes - 1; ++i)
        {
            int u, v;
            cin >> u >> v;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        // statistics();
    };
    // Print the data
    void statistics()
    {
        cout << "num_of_nodes: " << num_of_nodes << endl;
        for (int i = 1; i <= num_of_nodes; ++i)
        {
            cout << "Node " << i << " has neighbors: ";
            for (auto &j : adjList[i])
            {
                cout << j << " ";
            }
            cout << endl;
        }
        return;
    };
    void dfs(int node, int par)
    {
        height[node] = 0; // Initialize height of leaf node to 0
        parent[node] = par;

        for (int child : adjList[node])
        {
            if (child != par)
            {
                dfs(child, node);
                height[node] = max(height[node], 1 + height[child]); // Update height based on children
            }
        }
    };
    void EasyRootedTree()
    {
        dfs(1, -1);
        for (int i = 1; i <= num_of_nodes; ++i)
        {
            cout << height[i] << " " << parent[i] << endl;
        }
        return;
    }
};

int main()
{
    Solution solution;
    solution.EasyRootedTree();
    return 0;
}

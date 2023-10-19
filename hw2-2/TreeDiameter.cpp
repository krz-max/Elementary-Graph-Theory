#include <bits/stdc++.h>

using namespace std;

class TreeDiameter
{
public:
    TreeDiameter(){};
    int solve()
    {
        build_tree();
        int endpoint1, n;
        bfs(0, endpoint1); // First Pass
        cout << bfs(endpoint1, n) << endl; // n is not used
        return 0;
    };

private:
    void build_tree()
    {
        int n;
        cin >> n;
        mat.resize(n);
        while (--n)
        {
            int u, v;
            cin >> u >> v;
            mat[u - 1].push_back(v - 1);
            mat[v - 1].push_back(u - 1);
        }
    };
    /* 
    This function does a simple BFS to reach the farthest point from the start point. 
    The resulting endpoint is updated and the length of the path btwn start and endpoint is returned
    @param start    : The starting point.
    @param endpoint : The farthest poing from the starting point.
    @return diameter: The distance of the path between start and endpoint.
     */
    int bfs(int start, int &endpoint)
    {
        int diam = 0, n = mat.size();
        queue<int> q;
        vector<bool> visited(n, false);
        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int m = q.size();

            for (int i = 0; i < m; i++)
            {
                int current_node = q.front();
                q.pop();
                endpoint = current_node;

                for (auto neighbor : mat[current_node])
                {
                    if (!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            if (q.size())
                diam++;
        }
        return diam;
    };
    vector<vector<int>> mat;
};

int main()
{
    TreeDiameter Solution;
    Solution.solve();
    return 0;
}
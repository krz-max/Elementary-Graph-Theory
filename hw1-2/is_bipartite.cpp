#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    bool is_bipartite(const vector<vector<int>> &graph, int start)
    {
        vector<int> color(graph.size(), -1);
        queue<pair<int, int>> q;
        q.push({start, 0});
        color[start] = 0;

        while (!q.empty())
        {
            int node = q.front().first;
            int c = q.front().second;
            q.pop();

            for (int neighbor : graph[node])
            {
                if (color[neighbor] == -1)
                {
                    color[neighbor] = (c == 0) ? 1 : 0;
                    q.push({neighbor, color[neighbor]});
                }
                else if (color[neighbor] == c)
                {
                    return false;
                }
            }
        }

        return true;
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
    Solution Answer;
    if (Answer.is_bipartite(graph, 0))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}

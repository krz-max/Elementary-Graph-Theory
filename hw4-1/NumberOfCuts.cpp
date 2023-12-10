#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    int num_of_nodes;
    int num_of_edges;
    int num_of_cuts;
    vector<list<int>> adj_list;
    vector<int> visited_time;
    vector<int> low_link;
    vector<int> cut_vertex_flag;

public:
    Solution()
    {
        cin >> num_of_nodes >> num_of_edges;
        // Enter the edges
        adj_list.resize(num_of_nodes + 1);
        cut_vertex_flag.resize(num_of_nodes + 1);
        num_of_cuts = 0;
        for(int i = 0; i < num_of_edges; i++)
        {
            int u, v;
            cin >> u >> v;
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }
        // statistics();
    };
    // Print the data
    void statistics()
    {
        cout << "num_of_nodes: " << num_of_nodes << endl;
        cout << "num_of_edges: " << num_of_edges << endl;
        for (int i = 1; i <= num_of_nodes; ++i)
        {
            cout << "Node " << i << " has neighbors: ";
            for (auto &j : adj_list[i])
            {
                cout << j << " ";
            }
            cout << endl;
        }
        return;
    };
    void dfs(int parent, int root, int &time)
    {
        visited_time[root] = low_link[root] = ++time;
        int children = 0;
        for(auto &v : adj_list[root])
        {
            if(visited_time[v] == 0)
            {
                children++;
                dfs(root, v, time);
                low_link[root] = min(low_link[root], low_link[v]);
                if(low_link[v] >= visited_time[root] && parent != 0)
                {
                    // cout << root << " is a cut vertex" << endl;
                    if(cut_vertex_flag[root] == 0) num_of_cuts++;
                    cut_vertex_flag[root] = 1;
                }
            }
            else
            {
                low_link[root] = min(low_link[root], visited_time[v]);
            }
        }
        if(parent == 0 && children > 1)
        {
            // cout << root << " is a cut vertex" << endl;
            if(cut_vertex_flag[root] == 0) num_of_cuts++;
            cut_vertex_flag[root] = 1;
        }
        return ;
    }
    void NumberOfCuts()
    {
        visited_time.resize(num_of_nodes + 1);
        low_link.resize(num_of_nodes + 1);
        int time = 0;
        dfs(0, 1, time);
        cout << num_of_cuts << endl;
        int j = 0;
        while(cut_vertex_flag[j] == 0) j++;
        cout << j++;
        for(int i = 1; i < num_of_cuts; i++){
            while(cut_vertex_flag[j] == 0) j++;
            cout << " " << j++;
        }
        cout << endl;
        return ;
    }
};

int main()
{
    Solution solution;
    solution.NumberOfCuts();
    return 0;
}
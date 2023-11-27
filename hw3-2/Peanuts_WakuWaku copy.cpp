#include <bits/stdc++.h>

#define ll long long

using namespace std;

void single_destination_dijkstra(vector<vector<ll>> &adjList, vector<ll> &distance, int destination)
{
    distance[destination] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push({0, destination});
    while (!pq.empty())
    {
        ll end_point = pq.top().second;
        int n = distance.size();
        pq.pop();
        for (int start_point = 0; start_point < n; start_point++)
        { // Iterate through all incoming edges to end_point
            ll weight = adjList[end_point][start_point];
            if (weight == LONG_MAX)
                continue; // Skip if there is no edge
            if (distance[end_point] + weight < distance[start_point])
            {
                distance[start_point] = distance[end_point] + weight;
                pq.push({distance[start_point], start_point});
            }
        }
    }
    return;
}
void solve(vector<vector<ll>> &adjList, int n, int k)
{
    // From the nodes to the destination
    vector<ll> distance1(n, LONG_MAX);
    int destination = 0;
    single_destination_dijkstra(adjList, distance1, destination);
    if (k == 1)
    {
        for (auto i : distance1)
        {
            if (i != LONG_MAX)
                cout << i << " ";
            else
                cout << -1 << " ";
        }
        cout << "\n";
        return;
    }
    // Find the distance from all nodes to restaurant n
    vector<ll> distance2(n, LONG_MAX);
    destination = n - 1;
    single_destination_dijkstra(adjList, distance2, destination);
    // Update the distance from all nodes to "both" restaurants 1 and n
    for (int i = 0; i < n; ++i)
    {
        // adj[n] is a pseudo node that represents both restaurants 1 and n
        if (distance1[i] != LONG_MAX && distance2[i] != LONG_MAX)
            adjList[n][i] = (distance1[i] + distance2[i]);
    }
    // Calculate the shortest path from all nodes to "both" restaurants 1 and n
    vector<ll> distance3(n + 1, LONG_MAX);
    destination = n;
    single_destination_dijkstra(adjList, distance3, destination);
    distance3.pop_back();
    for (auto i : distance3)
    {
        if (i != LONG_MAX)
            cout << i << " ";
        else
            cout << -1 << " ";
    }
    cout << endl;
    return;
}

int main()
{
    int t, sub;
    cin >> t >> sub;
    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<ll>> adjList(n + 1, vector<ll>(n + 1, LONG_MAX));
        for (int i = 0; i < m; ++i)
        {
            ll u, v, w;
            cin >> u >> v >> w;
            // Reverse the direction to calculate single destination shortest path
            adjList[v - 1][u - 1] = w;
        }
        solve(adjList, n, k);
    }
    return 0;
}
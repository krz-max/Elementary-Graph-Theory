#include <bits/stdc++.h>

#define ull unsigned long long

using namespace std;

vector<ull> single_destination_dijkstra(vector<vector<ull>>& adjList, int n, int destination){
    vector<ull> distance(n, ULLONG_MAX);
    distance[destination] = 0;
    priority_queue<pair<ull, ull>, vector<pair<ull, ull>>, greater<pair<ull, ull>>> pq;
    pq.push({0, destination});
    while(!pq.empty()){
        int end_point = pq.top().second;
        pq.pop();
        for(ull start_point = 0; start_point < adjList[end_point].size(); start_point++){ // Iterate through all incoming edges to end_point
            ull weight = adjList[end_point][start_point];
            if(weight == ULLONG_MAX) continue; // Skip if there is no edge
            if(distance[end_point] + weight < distance[start_point]){
                distance[start_point] = distance[end_point] + weight;
                pq.push({distance[start_point], start_point});
            }
        }
    }
    return distance;
}
void solve(vector<vector<ull>>& adjList, int n, int k){
    // From the nodes to the destination
    vector<ull> distance1;
    int destination = 0;
    distance1 = single_destination_dijkstra(adjList, n, destination);
    if(k == 1){
        for(auto i: distance1){
            if(i != ULLONG_MAX)
                cout << i << " ";
            else
                cout << -1 << " ";
        }
        cout << "\n";
        return;
    }
    // Find the distance from all nodes to restaurant n
    vector<ull> distance2;
    destination = n - 1;
    distance2 = single_destination_dijkstra(adjList, n, destination);
    // Update the distance from all nodes to "both" restaurants 1 and n
    for(int i = 0; i < n; ++i){
        // adj[n] is a pseudo node that represents both restaurants 1 and n
        if(distance1[i] != ULLONG_MAX && distance2[i] != ULLONG_MAX)
            adjList[n][i] = (distance1[i] + distance2[i]);
    }
    // Calculate the shortest path from all nodes to "both" restaurants 1 and n
    vector<ull> distance3(n + 1, ULLONG_MAX);
    destination = n;
    distance3 = single_destination_dijkstra(adjList, n + 1, destination);
    distance3.pop_back();
    for(auto i: distance3){
        if(i != ULLONG_MAX)
            cout << i << " ";
        else
            cout << -1 << " ";
    }
    cout << endl;
    return ;
}

int main(){
    int t, sub;
    cin >> t >> sub;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<ull>> adjList(n+1, vector<ull>(n+1, ULLONG_MAX));
        for(int i = 0; i < m; ++i){
            ull u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            // Reverse the direction to calculate single destination shortest path
            adjList[v][u] = w;
        }
        solve(adjList, n, k);
    }
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

int bfs(int start, const vector<vector<int>>& mat, int& endpoint){
    int diam = 0, n = mat.size();
    queue<int> q;
    vector<bool> visited(n, false);
    visited[start] = true;
    q.push(start);
    
    while(!q.empty()){
        int m = q.size();

        for(int i = 0; i < m; i++){
            int current_node = q.front();
            q.pop();
            endpoint = current_node;

            for(auto neighbor : mat[current_node]){
                if(!visited[neighbor]){
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        if(q.size()) diam++;
    }
    return diam;
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> mat(n);
    while(--n){
        int u, v;
        cin >> u >> v;
        mat[u-1].push_back(v-1);
        mat[v-1].push_back(u-1);
    }
    
    int endpoint1;
    // First Pass
    bfs(0, mat, endpoint1);
    cout << bfs(endpoint1, mat, n); // n is not used

    return 0;
}
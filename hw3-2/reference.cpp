#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll>
using namespace std;

void dijkstra(vector<vector<pii>>& adj, int n, int src, int k){
    vector<ll> dis1(n, LONG_MAX);
    dis1[src] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, src});
    while(!pq.empty()){
        ll v = pq.top().second;
        pq.pop();
        for(auto& [u, w]: adj[v]){
            if(dis1[v] + w < dis1[u]){
                dis1[u] = dis1[v] + w;
                pq.push({dis1[u], u});
            }
        }
    }
    if(k == 1){
        for(auto i: dis1){
            if(i != LONG_MAX)
                cout << i << " ";
            else
                cout << -1 << " ";
        }
        cout << "\n";
        return;
    }
    vector<ll> dis2(n, LONG_MAX);
    dis2[n - 1] = 0;
    pq.push({0, n - 1});
    while(!pq.empty()){
        ll v = pq.top().second;
        pq.pop();
        for(auto& [u, w]: adj[v]){
            if(dis2[v] + w < dis2[u]){
                dis2[u] = dis2[v] + w;
                pq.push({dis2[u], u});
            }
        }
    }
    for(int i = 0; i < n; ++i){
        if(dis1[i] != LONG_MAX && dis2[i] != LONG_MAX)
            adj[n].push_back({i, dis1[i] + dis2[i]});
    }
    vector<ll> dis3(n + 1, LONG_MAX);
    dis3[n] = 0;
    pq.push({0, n});
    while(!pq.empty()){
        ll v = pq.top().second;
        pq.pop();
        for(auto& [u, w]: adj[v]){
            if(dis3[v] + w < dis3[u]){
                dis3[u] = dis3[v] + w;
                pq.push({dis3[u], u});
            }
        }
    }
    dis3.pop_back();
    for(auto i: dis3){
        if(i != LONG_MAX)
            cout << i << " ";
        else
            cout << -1 << " ";
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, sub;
    cin >> t >> sub;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<pii>> adj(n + 1);
        for(int i = 0; i < m; ++i){
            ll u, v, w;
            cin >> u >> v >> w;
            adj[--v].push_back({--u, w});
        }
        dijkstra(adj, n, 0, k);
    }
    return 0;
}
#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

int findSet(int i, vector<int>& parent){
    if(parent[i] != i)
        parent[i] = findSet(parent[i], parent);
    return parent[i];
}

void mergeSet(int u, int v, vector<int>& parent, vector<int>& rnk){
    if(rnk[u] > rnk[v])
        parent[v] = u;
    else
        parent[u] = v;
    if (rnk[u] == rnk[v])
        rnk[u]++;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int Q;
    cin >> Q;
    while(Q--){
        int n, m;
        cin >> n >> m;
        vector<pii> coin;
        vector<pair<int, pii>> specials;
        for(int i = 1; i <= n; i++){
            int num;
            cin >> num;
            coin.push_back({num, i});
        }
        sort(coin.begin(), coin.end());
        for(int i = 0; i < m; i++){
            int x, y, w;
            cin >> x >> y >> w;
            specials.push_back({w, {x, y}});
        }
        sort(specials.begin(), specials.end());
        ll ans = 0;
        vector<int> parent(n + 1), rnk(n + 1, 0);
        for(int i = 1; i <= n; i++)
            parent[i] = i;
        int k = 1, l = 0;
        int init_set = findSet(coin[0].second, parent);
        rnk[init_set] = INT_MAX;
        int edge = 0;
        while(edge < n - 1){
            int w1 = coin[k].first;
            int v1 = coin[k].second;
            int w2 = INT_MAX, v2 = -1, v3 = -1;
            if(l < m){
                w2 = specials[l].first;
                v2 = specials[l].second.first;
                v3 = specials[l].second.second;
            }
            if(w1 + coin[0].first < w2){
                int set_v1 = findSet(v1, parent);
                if(set_v1 != init_set){
                    mergeSet(set_v1, init_set, parent, rnk);
                    ans += (ll)w1 + coin[0].first;
                    ++edge;
                }
                ++k;
            }
            else{
                int set_v2 = findSet(v2, parent);
                int set_v3 = findSet(v3, parent);
                if(set_v2 != set_v3){
                    mergeSet(set_v2, set_v3, parent, rnk);
                    ans += (ll)w2;
                    ++edge;
                }
                ++l;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
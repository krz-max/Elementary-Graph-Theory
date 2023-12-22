#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
#define Equal(X, Y, Z) X == Y && Y == Z
#define ALL(v) v.begin(),v.end()

class PlanarGraph{
private:
    using ListOfIntegerPairs = vector<pair<int,int>>;
    using AdjacencyMatrix = vector<vector<bool>>;
    int num_of_vertex;
    int num_of_edge;
    bool is_planar; // assume the graph is planar at first
    ListOfIntegerPairs edges;
public:
    PlanarGraph(int n, int m): num_of_vertex(n), num_of_edge(m), is_planar(true){
        while(m--){
            int u, v;
            cin >> u >> v;
            edges.emplace_back(u, v);
        }
    };
    ~PlanarGraph() = default;
    void solve(){
        // Iterate through all possible subset of edges (brute force)
        // For each subset of edges, do contraction and check if the graph has K5 or K3,3
        for(int i = 1; i < (1 << num_of_edge); ++i){
            if(!is_planar) break;
            
            // Build the adjacency matrix for the current subset of edges
            AdjacencyMatrix adj(num_of_vertex + 1, vector<bool>(num_of_vertex + 1, false));
            for(int j = 0; j < num_of_edge; ++j){
                if((i >> j) & 1){
                    adj[edges[j].first][edges[j].second] = true;
                    adj[edges[j].second][edges[j].first] = true;
                }
            }
            // Contract the graph
            bool has_subdivision = true;
            while(has_subdivision){
                has_subdivision = false;
                for(int u = 1; u <= num_of_vertex; ++u){
                    if(count(ALL(adj[u]), true) == 2){
                        has_subdivision = true;
                        int v = 1, w = 1;
                        while(!adj[u][v]) ++v;
                        while(!adj[u][w] || w == v) ++w;
                        adj[u][v] = adj[v][u] = false;
                        adj[u][w] = adj[w][u] = false;
                        adj[v][w] = adj[w][v] = true;
                    }
                }
            }

            // Check if the contracted graph has K5
            // 1. Find all degree 4 vertices
            // 2. Check if there are 5 vertices in total (because we check all possible selection of edges, so this is feasible)
            vector<int> degree_4_vertices;
            unordered_set<int> K5_candidate;
            for(int u = 1; u <= num_of_vertex; ++u){
                if(count(ALL(adj[u]), true) == 4) degree_4_vertices.emplace_back(u);
            }
            if(degree_4_vertices.size() == 5){
                for(int u : degree_4_vertices){
                    K5_candidate.insert(u);
                    for(int v = 1; v <= num_of_vertex; ++v){
                        if(adj[u][v]) K5_candidate.insert(v);
                    }
                }
                if(K5_candidate.size() == 5) is_planar = false;
            }

            // Check if the contracted graph has K3,3
            // 1. Find all degree 3 vertices
            // 2. Sort the degree 3 vertices by their neighbors
            // 3. Check if there are 6 vertices in total
            // 4. Check if the first 3 vertices' neighbors are the same as the last 3 vertices
            vector<pair<int, vector<int>>> degree_3_vertices;
            for(int u = 1; u <= num_of_vertex; ++u){
                if(count(ALL(adj[u]), true) == 3){
                    vector<int> neighbors;
                    for(int v = 1; v <= num_of_vertex; ++v){
                        if(adj[u][v]) neighbors.emplace_back(v);
                    }
                    degree_3_vertices.emplace_back(u, neighbors);
                }
            }
            sort(ALL(degree_3_vertices), [](auto &a, auto &b){
                return a.second < b.second;
            });
            if(degree_3_vertices.size() == 6 
            && Equal(degree_3_vertices[0].second, degree_3_vertices[1].second, degree_3_vertices[2].second) 
            && Equal(degree_3_vertices[3].second, degree_3_vertices[4].second, degree_3_vertices[5].second) 
            && degree_3_vertices[2].second != degree_3_vertices[3].second){
                is_planar = false;
            }
        }
        cout << (is_planar ? "Yes" : "No") << '\n';
        return ;
    }
};

int main(){
    int num_of_query, num_of_vertex, num_of_edge;
    cin >> num_of_query;
	while(num_of_query--){
        cin >> num_of_vertex >> num_of_edge;
        PlanarGraph test(num_of_vertex, num_of_edge);
        test.solve();
	}
}
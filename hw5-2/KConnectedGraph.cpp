// Reference: https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Edge {
private:
    int dest;
    int flow;
    int capacity;
    int reverse_edge;
public:
    enum class Operator { ADD, SUBTRACT, CLEAR };
    Edge(int _dest, int _flow, int _capacity, int _reverse_edge): dest(_dest), flow(_flow), capacity(_capacity), reverse_edge(_reverse_edge) {};
    
    bool flowIsNotFull() const { return flow < capacity; };

    const int &getDest() const { return dest; };
    const int &getReverseEdgeIdx() const { return reverse_edge; };
    int getSlack() const { return capacity - flow; }

    void modifyFlow(int _flow, Operator op) {
        switch(op){
            case Operator::ADD:
                flow += _flow;
                break;
            case Operator::SUBTRACT:
                flow -= _flow;
                break;
            case Operator::CLEAR:
                flow = 0;
                break;
        }
    }
};
class KConnectedGraph{
private:
    int num_of_vertices;
    int num_of_edges;
    vector<vector<Edge>> edges;
    vector<int> level_of_vertices;
    /**
     * @brief Check if more flows are available to send and label the levels of vertices.
     * @param sink_vtx The sink vertex.
     * @param tank_vtx The tank vertex.
     * @return True if more flows are available to send, false otherwise.
     */
    bool bfs(int sink_vtx, int tank_vtx){
        // BFS using queue
        level_of_vertices = vector<int>(num_of_vertices, -1);
        level_of_vertices[sink_vtx] = 0;
        queue<int> q;
        q.push(sink_vtx);
        
        while(!q.empty()){
            int cur_vtx = q.front();
            q.pop();
            for(const Edge &i : edges[cur_vtx]){
                const int &destination = i.getDest();
                if(level_of_vertices[destination] == -1 && i.flowIsNotFull()){
                    level_of_vertices[destination] = level_of_vertices[cur_vtx] + 1;
                    q.push(destination);
                }
            }
        }
        return level_of_vertices[tank_vtx] != -1;
    }
    /**
     * @brief Send flow using dfs from the source vertex to the tank vertex after the vertices are labeled and there are possible flow distribution(indicated by bfs())
     * @param cur_vtx The current vertex.
     * @param neighbor_vtx The tank vertex.
     * @param cur_flow The current flow.
     * @param start_of_edges The index of the edge that each vertex should visit next. (i.e. how many edges have been visited)
     */
    int sendFlow(int cur_vtx, int neighbor_vtx, int cur_flow, vector<int> &start_of_edges){
        if(cur_vtx == neighbor_vtx) return cur_flow;
        for(; start_of_edges[cur_vtx] < static_cast<int>(edges[cur_vtx].size()); ++start_of_edges[cur_vtx]){
            Edge &e = edges[cur_vtx][start_of_edges[cur_vtx]];
            const int &neighbor = e.getDest();
            if(level_of_vertices[neighbor] == level_of_vertices[cur_vtx] + 1 && e.flowIsNotFull()){
                int flow = sendFlow(neighbor, neighbor_vtx, min(cur_flow, e.getSlack()), start_of_edges);
                if(flow > 0){
                    e.modifyFlow(flow, Edge::Operator::ADD);
                    edges[neighbor][e.getReverseEdgeIdx()].modifyFlow(flow, Edge::Operator::SUBTRACT);
                    return flow;
                }
            }
        }
        return 0;
    }
    /**
     * @brief Run Dinic's algorithm to find the maximum flow from the sink vertex to the tank vertex.
     * @param sink_vtx The sink vertex.
     * @param tank_vtx The tank vertex.
     * @return The maximum flow from the sink vertex to the tank vertex.
     */
    int dinicMaxFlow(int sink_vtx, int tank_vtx){
        int max_flow = 0;
        while(bfs(sink_vtx, tank_vtx) == true){
            vector<int> start_of_edges(num_of_vertices + 1, 0);
            while(int flow = sendFlow(sink_vtx, tank_vtx, INT_MAX, start_of_edges)){
                max_flow += flow;
            }
        }
        return max_flow;
    }
    /**
     * @brief Reset the flow of each edge to 0.
     */
    void resetFlow(){
        for(int i = 0; i < num_of_vertices; ++i){
            for(Edge &e : edges[i]){
                e.modifyFlow(0, Edge::Operator::CLEAR);
            }
        }
    }
public:
    KConnectedGraph(int n, int m): num_of_vertices(n), num_of_edges(m) {
        edges = vector<vector<Edge>>(n);
        int u, v;
        while(m--){
            cin >> u >> v;
            Edge forward1(v-1, 0, 1, edges[v-1].size());
            Edge backward1(u-1, 0, 0, edges[u-1].size());
            Edge forward2(u-1, 0, 1, edges[u-1].size());
            Edge backward2(v-1, 0, 0, edges[v-1].size());
            edges[u-1].emplace_back(forward1);
            edges[v-1].emplace_back(backward1);
            edges[v-1].emplace_back(forward2);
            edges[u-1].emplace_back(backward2);
        }
    };
    ~KConnectedGraph() = default;
    /**
     * @brief Run Dinic's algorithm using all possible pairs of vertex pair as sink and tank to find the maximum flow.
     */
    void solve(){
        int min_cut_set_size = INT_MAX;
        for(int i = 0; i < num_of_vertices; ++i){
            for(int j = 0; j < num_of_vertices; ++j){
                if(i == j) continue;
                resetFlow();
                min_cut_set_size = min(min_cut_set_size, dinicMaxFlow(i, j));
            }
        }
        cout << min_cut_set_size << endl;
    };
};

int main () {
    int n, m;
    cin >> n >> m;
    KConnectedGraph solution(n, m);
    solution.solve();
    return 0;
}
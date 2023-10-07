#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // Initialize adjacency matrix with all zeroes
    vector<vector<int>> graph(n, vector<int>(n, 0));

    vector<int> inDegree(n, 0);
    vector<int> outDegree(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        // Add directed edge from u to v with weight w
        graph[u-1][v-1] = w;
        outDegree[u-1]++;
        inDegree[v-1]++;
    }

    // Output matrix representation
    // cout << "Matrix representation:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    // Output indegree and outdegree
    // cout << "Indegree and Outdegree:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << inDegree[i] << " " << outDegree[i] << endl;
    }

    return 0;
}

#include <bits/stdc++.h>

using namespace std;

class Key_Blueprint
{
public:
    Key_Blueprint(){};
    void build_key_blueprint()
    {
        cin >> num_of_nodes;
        graph = vector<vector<int>>(num_of_nodes);
        for(int i = 0; i < num_of_nodes; i++)
        {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        construct_joint_nodes();
        print_joint_nodes();
        construct_possible_keys();
    };
    bool compare_with_keys(const vector<int>& another_key){
        for(const auto& vec : possible_keys){
            int n = vec.size(), m = another_key.size();
            if(n != m) continue;
            bool same = true;
            for(int i = 0; i < n; i++){
                if(vec[i] != another_key[i]){
                    same = false;
                    break;
                }
            }
            if(same) return true;
        }
        return false;
    }
    void print_joint_nodes(){
        for(const auto& node:joint_nodes){
            cout << node._self << ", ";
            for(auto it:node._edges) cout << it << ", ";
            for(auto it:node._branch_len) cout << it << ", ";
            cout << endl;
        }
    }
private:
    int num_of_nodes;
    struct joint_node{
        joint_node(int self, vector<int> edges){
            _self = self;
            _edges = edges;
            sort(_edges.begin(), _edges.end());
            _branch_len = construct_b_len();
        };
        int _self;
        bool _is_border;
        vector<int> _edges;
        vector<int> _branch_len;
        vector<int> construct_b_len(){
            // to-do
            // update _is_border here
            return {-1, -1, -1};
        };
    };
    vector<joint_node> joint_nodes;
    vector<vector<int>> graph;
    vector<vector<int>> possible_keys;

    void construct_joint_nodes(){
        for(int i = 0; i < num_of_nodes; i++){
            if(graph[i].size() == 3){
                joint_nodes.push_back(joint_node{i, graph[i]});
            }
        }
    };
    void construct_possible_keys(){

        return ;
    };

};
int main()
{
    Key_Blueprint Cinderella;
    Cinderella.build_key_blueprint();
    int m;
    cin >> m;
    vector<int> Drizella(m, 0);
    for(int i = 0; i < m; i++) cin >> Drizella[i];
    if(Cinderella.compare_with_keys(Drizella)){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
    return 0;
}
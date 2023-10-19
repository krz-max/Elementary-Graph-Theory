#include <bits/stdc++.h>

using namespace std;

template <class T>
void print_iterator(T iterable)
{
    for (auto it : iterable)
    {
        cout << it << " ";
    }
    cout << endl;
}

struct node
{
    node(){};
    int degree;
    int visited;
    vector<int> joint_branch_length;
    vector<int> edges;
};

class Key_Blueprint
{
public:
    Key_Blueprint(){};
    void build_key_blueprint()
    {
        cin >> num_of_nodes;
        nodes = vector<node>(num_of_nodes);
        for (int i = 0; i < num_of_nodes - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            nodes[u].degree++;
            nodes[u].edges.push_back(v);
            nodes[v].degree++;
            nodes[v].edges.push_back(u);
        }
        remove_leaves();
        // statistics();
    };
    // a joint node has to be reeached by leaf nodes two times for it to be boundary joint node(i.e. it has two branches that ends in leaf node).
    // we remove leaves, update the times the nodes were visited in the traversal.
    // If a node is visited:
    // 1. It's a middle node, which has degree 2. Just push it into the queue and iterate its neighbor in the next cycle.
    // 2. It's a joint in the path(degree=3). Label it to show that it was visited, and that it becomes a "candidate" of boundary joint node.
    void remove_leaves()
    {
        queue<int> leaves;
        vector<int> length(num_of_nodes, 0);
        for (int i = 0; i < num_of_nodes; i++)
        {
            if (nodes[i].degree == 1)
            {
                leaves.push(i);
                nodes[i].visited = 2;
                nodes[i].joint_branch_length.push_back(0);
            }
        }

        while (!leaves.empty())
        {
            int cur_node = leaves.front();
            leaves.pop();
            for (auto neighbor : nodes[cur_node].edges)
            {
                if (nodes[neighbor].visited == 0)
                {
                    nodes[neighbor].visited = 1;
                    if (nodes[neighbor].degree == 2)
                    {
                        leaves.push(neighbor);
                        nodes[neighbor].visited = 2;
                    }
                    nodes[neighbor].joint_branch_length.push_back(nodes[cur_node].joint_branch_length[0] + 1);
                }
                else if (nodes[neighbor].visited == 1 && nodes[neighbor].degree == 3)
                {
                    joint_nodes_idx.push_back(neighbor);
                    nodes[neighbor].joint_branch_length = {nodes[neighbor].joint_branch_length[0], nodes[cur_node].joint_branch_length[0] + 1};
                    nodes[neighbor].visited = 2;
                }
            }
        }
        leaves.push(joint_nodes_idx[0]);
        while (!leaves.empty())
        {
            int cur_node = leaves.front();
            leaves.pop();
            for (auto neighbor : nodes[cur_node].edges)
            {
                if (nodes[neighbor].visited != 2)
                {
                    leaves.push(neighbor);
                    if (nodes[neighbor].degree == 3)
                    {
                        joint_nodes_idx.push_back(neighbor);
                    }
                    nodes[neighbor].visited = 2;
                }
            }
        }
        return;
    };
    bool compare_with_keys(const vector<int> &another_key)
    {
        if (another_key.size() != joint_nodes_idx.size())
            return false;
        int n = another_key.size();
        if ((another_key[0] == nodes[joint_nodes_idx[0]].joint_branch_length[0] || another_key[0] == nodes[joint_nodes_idx[0]].joint_branch_length[1]) && (another_key[n - 1] == nodes[joint_nodes_idx[1]].joint_branch_length[0] || another_key[n - 1] == nodes[joint_nodes_idx[1]].joint_branch_length[1]))
        {
            for (int i = 1; i < n - 1; i++)
            {
                if (another_key[i] != nodes[joint_nodes_idx[i + 1]].joint_branch_length[0])
                    return false;
            }
            return true;
        }
        else if ((another_key[n - 1] == nodes[joint_nodes_idx[0]].joint_branch_length[0] || another_key[n - 1] == nodes[joint_nodes_idx[0]].joint_branch_length[1]) && (another_key[0] == nodes[joint_nodes_idx[1]].joint_branch_length[0] || another_key[0] == nodes[joint_nodes_idx[1]].joint_branch_length[1]))
        {
            for (int i = 1; i < n - 1; i++)
            {
                if (another_key[n - 1 - i] != nodes[joint_nodes_idx[i + 1]].joint_branch_length[0])
                    return false;
            }
            return true;
        }
        return false;
    }
    void statistics()
    {
        cout << "Boundary Index: " << joint_nodes_idx[0] << ", " << joint_nodes_idx[1] << endl;
        for (int i = 0; i < num_of_nodes; i++)
        {
            auto &cur_node = nodes[i];
            cout << "Node Index: " << i << endl;
            cout << "Node Degree: " << cur_node.degree << endl;
            if (cur_node.degree == 3)
            {
                cout << "Branch Length: ";
                for (auto it : cur_node.joint_branch_length)
                {
                    cout << it << ", ";
                }
                cout << endl;
            }
            cout << "Node Edges: ";
            print_iterator<vector<int>>(cur_node.edges);
            cout << "---------" << endl;
        }
    }

private:
    int num_of_nodes;
    vector<node> nodes; // id->node_info
    vector<int> joint_nodes_idx;
};
int main()
{
    Key_Blueprint Cinderella;
    Cinderella.build_key_blueprint();
    int m;
    cin >> m;
    vector<int> Drizella(m, 0);
    for (int i = 0; i < m; i++)
        cin >> Drizella[i];
    if (Cinderella.compare_with_keys(Drizella))
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
    cout << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    int num_of_heroes;
    int num_of_monsters;
    int num_of_potions;
    vector<list<int>> adj_list;

public:
    Solution()
    {
        // Enter the number of heroes, monsters and potions
        cin >> num_of_heroes >> num_of_monsters >> num_of_potions;
        // Enter the edges
        adj_list.resize(num_of_heroes + num_of_monsters + 1);
        for (int i = 1; i <= num_of_heroes; ++i)
        {
            int power;
            cin >> power;
            for (int j = 0; j < power; j++)
            {
                int monster;
                cin >> monster;
                adj_list[i].push_back(monster);
            }
        }
        // statistics();
    };
    // Print the data
    void statistics()
    {
        cout << "num_of_heroes: " << num_of_heroes << endl;
        cout << "num_of_monsters: " << num_of_monsters << endl;
        cout << "num_of_potions: " << num_of_potions << endl;
        cout << "adj_list: " << endl;
        for (int i = 1; i <= num_of_heroes; ++i)
        {
            cout << i << ": ";
            for (auto &v : adj_list[i])
            {
                cout << v << " ";
            }
            cout << endl;
        }
        return;
    };
    bool dfs_augmenting_path(int u, vector<vector<int>> &matched_heroes, vector<int> &matched_monsters, vector<int> &visited, int target)
    {
        for (auto &v : adj_list[u])
        {
            if (visited[v] == 0)
            {
                visited[v] = 1;
                if (matched_monsters[v] == u)
                    continue;
                if (matched_monsters[v] == -1 || dfs_augmenting_path(matched_monsters[v], matched_heroes, matched_monsters, visited, 1 - target))
                {
                    matched_monsters[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    void matching_heroes_and_monsters()
    {
        vector<vector<int>> matched_heroes(num_of_heroes + 1);
        vector<int> matched_monsters(num_of_monsters + 1, -1);
        int used_potion = 0;
        int max_matching = 0;
        // statistics();
        for (int i = 1; i <= num_of_heroes; ++i)
        {
            vector<int> visited(num_of_monsters + 1, false);
            if (dfs_augmenting_path(i, matched_heroes, matched_monsters, visited, 1))
            {
                max_matching++;
                if (used_potion < num_of_potions)
                {
                    visited.assign(num_of_monsters + 1, false);
                    if (dfs_augmenting_path(i, matched_heroes, matched_monsters, visited, 1))
                    {
                        max_matching++;
                        used_potion++;
                    }
                }
            }
            // for (int i = 1; i <= num_of_monsters; ++i)
            // {
            //     cout << i << ": " << matched_monsters[i] << endl;
            // }
            // cout << "-----------------------------------------------------" << endl;
        }
        // Print matched_flags
        // for (int i = 1; i <= num_of_heroes; ++i)
        // {
        //     cout << i << ": ";
        //     for (size_t j = 0; j < matched_flags[i].size(); ++j)
        //     {
        //         if (matched_flags[i][j] != 0)
        //             cout << matched_flags[i][j] - num_of_heroes << " ";
        //         else
        //             cout << 0 << " ";
        //     }
        //     cout << endl;
        // }
        // for (int i = 1; i <= num_of_monsters; ++i)
        // {
        //     cout << i << ": " << matched_monsters[i] << endl;
        // }
        cout << min(max_matching, num_of_monsters) << endl;
        return;
    }
    void HeroAndMonster()
    {
        matching_heroes_and_monsters();
        return;
    }
};

int main()
{
    Solution solution;
    solution.HeroAndMonster();
    return 0;
}
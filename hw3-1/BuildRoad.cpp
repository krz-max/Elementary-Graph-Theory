#include <bits/stdc++.h>

#define ll long long

using namespace std;

class UnionFind
{
public:
    UnionFind() : parent(0), rank(0){};
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    ll find(ll u)
    {
        if (parent[u] != u) parent[u] = find(parent[u]);
        return parent[u];
    }
    void unionSets(ll u, ll v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
    void setInitialRank(int minimumCostCityIdx)
    {
        this->rank[minimumCostCityIdx] = INT_MAX;
    }

private:
    vector<ll> parent;
    vector<ll> rank;
};

class Solution
{
private:
    int num_of_cities;
    int num_of_special_offers;
    vector<pair<ll, ll>> coins;
    vector<pair<ll, pair<ll, ll>>> specialOffer;
    UnionFind uf;

public:
    /**
     * @brief Construct a new Solution object, this reads from stdin for necessary inputs
     * @return a Solution object
     */
    Solution()
    {
        // Enter the number of queries
        // Enter the number of cities and special offers, this will create a UnionFind object
        cin >> num_of_cities >> num_of_special_offers;
        // Initialize objects
        uf = UnionFind(num_of_cities);
        coins = vector<pair<ll, ll>>(num_of_cities);
        specialOffer = vector<pair<ll, pair<ll, ll>>>(num_of_special_offers);
        // Enter the cost of coins in each city
        for (int i = 0; i < num_of_cities; ++i)
        {
            ll coin;
            cin >> coin;
            coins[i] = {coin, i};
        }
        // Enter the special offers
        for (int i = 0; i < num_of_special_offers; ++i)
        {
            ll start, end, weight;
            cin >> start >> end >> weight;
            specialOffer[i] = {weight, {start - 1, end - 1}};
        }
        // Print the input
        // statistics();
    };
    /**
     * @brief Output the statistics of the input after reading from stdin
     */
    void statistics()
    {
        cout << "Number of cities: " << num_of_cities << endl;
        cout << "Number of special offers: " << num_of_special_offers << endl;
        cout << "Coins: ";
        for (auto i : coins)
        {
            cout << i.first << " ";
        }
        cout << endl;
        cout << "Special offers: ";
        for (auto i : specialOffer)
        {
            cout << i.first << " " << i.second.first << " " << i.second.second << endl;
        }
        cout << endl;
    };
    /**
     * @brief Solve the question
     */
    void BuildRoad()
    {
        // Sort the coins and special offers
        sort(coins.begin(), coins.end());
        sort(specialOffer.begin(), specialOffer.end());
        // Kruskal's algorithm to find the minimum spanning tree
        ll totalCost = 0;
        int selected_edges = 0;
        int selected_offers = 0;
        int selected_city = 1;
        int start_city = uf.find(coins[0].second);
        uf.setInitialRank(start_city);
        while (selected_edges < num_of_cities - 1)
        {
            ll weight1 = coins[selected_city].first;
            ll city1 = coins[selected_city].second;
            ll weight2 = LONG_MAX, city2 = -1, city3 = -1;
            if (selected_offers < specialOffer.size())
            {
                weight2 = specialOffer[selected_offers].first;
                city2 = specialOffer[selected_offers].second.first;
                city3 = specialOffer[selected_offers].second.second;
            }
            if (weight1 + coins[0].first < weight2)
            {
                ll set_city1 = uf.find(city1);
                if (set_city1 != start_city)
                {
                    uf.unionSets(set_city1, start_city);
                    totalCost += weight1 + coins[0].first;
                    ++selected_edges;
                }
                ++selected_city;
            }
            else
            {
                ll set_city2 = uf.find(city2);
                ll set_city3 = uf.find(city3);
                if (set_city2 != set_city3)
                {
                    uf.unionSets(set_city2, set_city3);
                    totalCost += weight2;
                    ++selected_edges;
                }
                ++selected_offers;
            }
        }
        cout << totalCost << endl;
    };
};

int main()
{
    int Q;
    cin >> Q;
    for(int i = 0; i < Q; ++i)
    {
        Solution solution;
        solution.BuildRoad();
    }
    return 0;
}

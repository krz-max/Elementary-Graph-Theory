#include <bits/stdc++.h>

#define ll long long

namespace PlayerName
{
    const int Anya = 1;
    const int Damian = 2;
};

class Solution
{
private:
    int num_of_restaurants;
    int num_of_roads;
    int winning_player;
    std::vector<std::vector<std::pair<ll, ll>>> adjList;

public:
    Solution()
    {
        std::cin >> num_of_restaurants >> num_of_roads >> winning_player;
        adjList.resize(num_of_restaurants + 1);
        for (int i = 0; i < num_of_roads; ++i)
        {
            ll u, v, w;
            std::cin >> u >> v >> w;
            adjList[v - 1].push_back({u - 1, w});
        }
        // statistics();
    };
    // Print the data
    void statistics()
    {
        std::cout << "num_of_restaurants: " << num_of_restaurants << std::endl;
        std::cout << "num_of_roads: " << num_of_roads << std::endl;
        std::cout << "winning_player: " << winning_player << std::endl;
        for (int i = 0; i < num_of_restaurants; ++i)
        {
            std::cout << i << ": ";
            for (auto &[j, k] : adjList[i])
            {
                std::cout << "(" << j << ", " << k << ") ";
            }
            std::cout << std::endl;
        }
        return;
    };
    /**
     * @brief Single destination Dijkstra algorithm
     * @param adjList "Reversed" Adjacency list of the graph
     * @param distance Distance from all nodes to destination
     * @param destination Destination node
     * @return distance is updated to the shortest distance from all nodes to destination
     */
    void single_destination_dijkstra(std::vector<std::vector<std::pair<ll, ll>>> &adjList, std::vector<ll> &distance, int destination)
    {
        distance[destination] = 0;
        std::priority_queue<std::pair<ll, ll>, std::vector<std::pair<ll, ll>>, std::greater<std::pair<ll, ll>>> pq;
        pq.push({0, destination});
        while (!pq.empty())
        {
            ll end_point = pq.top().second;
            pq.pop();
            for (auto &[start_point, weight] : adjList[end_point])
            {
                if (distance[end_point] + weight < distance[start_point])
                {
                    distance[start_point] = distance[end_point] + weight;
                    pq.push({distance[start_point], start_point});
                }
            }
        }
        return;
    }
    void Peanuts_WakuWaku()
    {
        // From the nodes to the destination
        std::vector<ll> distance1(num_of_restaurants, LONG_MAX);
        int destination = 0;
        single_destination_dijkstra(adjList, distance1, destination);
        if (winning_player == PlayerName::Anya)
        {
            for (auto i : distance1)
            {
                if (i != LONG_MAX)
                    std::cout << i << " ";
                else
                    std::cout << -1 << " ";
            }
            std::cout << "\n";
            return;
        }

        // Find the distance from all nodes to restaurant n
        std::vector<ll> distance2(num_of_restaurants, LONG_MAX);
        destination = num_of_restaurants - 1;
        single_destination_dijkstra(adjList, distance2, destination);
        // Update the distance from all nodes to "both" restaurants 1 and n
        for (int i = 0; i < num_of_restaurants; ++i)
        {
            // adj[n] is a pseudo node that represents both restaurants 1 and n
            if (distance1[i] != LONG_MAX && distance2[i] != LONG_MAX)
                adjList[num_of_restaurants].push_back({i, distance1[i] + distance2[i]});
        }

        // Calculate the shortest path from all nodes to "both" restaurants 1 and n
        std::vector<ll> distance3(num_of_restaurants + 1, LONG_MAX);
        destination = num_of_restaurants;
        single_destination_dijkstra(adjList, distance3, destination);
        distance3.pop_back();
        for (auto i : distance3)
        {
            if (i != LONG_MAX)
                std::cout << i << " ";
            else
                std::cout << -1 << " ";
        }
        std::cout << std::endl;
        return;
    };
};

int main()
{
    int t, sub;
    std::cin >> t >> sub;
    for (int i = 0; i < t; i++)
    {
        Solution solution;
        solution.Peanuts_WakuWaku();
    }
    return 0;
}
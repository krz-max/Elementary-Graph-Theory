class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)

        if root_u != root_v:
            if self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1


def min_cost(cities, special_offers):
    edges = [(i, j, cities[i] + cities[j]) for i in range(len(cities)) for j in range(i + 1, len(cities))]
    edges += special_offers

    # Sort edges by cost in ascending order
    edges.sort(key=lambda x: x[2])

    # Initialize Union-Find data structure
    uf = UnionFind(len(cities))

    # Kruskal's algorithm to find the minimum spanning tree
    total_cost = 0
    for edge in edges:
        u, v, cost = edge
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            total_cost += cost

    return total_cost

def main():
    # Q = int(input("Enter the number of queries (Q): "))
    Q = int(input())
    
    for _ in range(Q):
        #n, m = map(int, input("Enter n and m: ").split())
        n, m = map(int, input().split())
        #cities = list(map(int, input("Enter costs of each city: ").split()))
        cities = list(map(int, input().split()))

        special_offers = []
        for _ in range(m):
            # x, y, z = map(int, input("Enter special offer (x y z): ").split())
            x, y, z = map(int, input().split())
            special_offers.append((x - 1, y - 1, z))  # Adjust indices to start from 0

        print(min_cost(cities, special_offers))
        # print(f"Minimum cost for query {_ + 1}: {result}")

if __name__ == "__main__":
    main()

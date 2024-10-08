
import heapq

class OSPFRouter:
    def __init__(self, name):
        self.name = name
        self.neighbors = {}  # {neighbor_name: cost}
        self.routing_table = {}  # {destination: (cost, next_hop)}

    def add_neighbor(self, neighbor, cost):
        self.neighbors[neighbor.name] = cost

    def calculate_shortest_paths(self):
        unvisited = [(0, self.name)]  # (cost, router_name)
        visited = {}
        while unvisited:
            current_cost, current_router = heapq.heappop(unvisited)
            if current_router in visited:
                continue
            visited[current_router] = current_cost
            for neighbor_name, neighbor_cost in network[current_router].neighbors.items():
                if neighbor_name not in visited:
                    total_cost = current_cost + neighbor_cost
                    heapq.heappush(unvisited, (total_cost, neighbor_name))
        self.routing_table = visited

    def display_routing_table(self):
        print(f"Routing table for {self.name}:")
        for dest, cost in self.routing_table.items():
            print(f"  Destination {dest} with cost {cost}")
        print()


# Create network of routers
network = {
    'A': OSPFRouter('A'),
    'B': OSPFRouter('B'),
    'C': OSPFRouter('C'),
    'D': OSPFRouter('D')
}

# Add neighbors and their costs
network['A'].add_neighbor(network['B'], 1)
network['A'].add_neighbor(network['C'], 5)
network['B'].add_neighbor(network['A'], 1)
network['B'].add_neighbor(network['D'], 2)
network['C'].add_neighbor(network['A'], 5)
network['D'].add_neighbor(network['B'], 2)

# Simulate OSPF protocol
for router in network.values():
    router.calculate_shortest_paths()
    router.display_routing_table()

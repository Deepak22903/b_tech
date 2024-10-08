
import time

class RIPRouter:
    def __init__(self, name):
        self.name = name
        self.routing_table = {}  # {destination: (cost, next_hop)}
        self.neighbors = {}  # {neighbor_name: cost}

    def add_neighbor(self, neighbor, cost):
        self.neighbors[neighbor.name] = cost
        self.routing_table[neighbor.name] = (cost, neighbor.name)

    def update_routing_table(self):
        updated = False
        for neighbor_name, cost_to_neighbor in self.neighbors.items():
            neighbor_router = network[neighbor_name]
            for dest, (neighbor_cost, next_hop) in neighbor_router.routing_table.items():
                new_cost = cost_to_neighbor + neighbor_cost
                if dest not in self.routing_table or new_cost < self.routing_table[dest][0]:
                    self.routing_table[dest] = (new_cost, neighbor_name)
                    updated = True
        return updated

    def send_updates(self):
        print(f"Router {self.name} sends updates:")
        for neighbor_name in self.neighbors:
            print(f"  Neighbor {neighbor_name} gets updated info from {self.name}")
        time.sleep(1)  # Simulate delay in sending updates

    def display_routing_table(self):
        print(f"Routing table for {self.name}:")
        for dest, (cost, next_hop) in self.routing_table.items():
            print(f"  {dest} via {next_hop} with cost {cost}")
        print()


# Create network of routers
network = {
    'A': RIPRouter('A'),
    'B': RIPRouter('B'),
    'C': RIPRouter('C'),
    'D': RIPRouter('D')
}

# Add neighbors and their costs
network['A'].add_neighbor(network['B'], 1)
network['A'].add_neighbor(network['C'], 5)
network['B'].add_neighbor(network['A'], 1)
network['B'].add_neighbor(network['D'], 2)
network['C'].add_neighbor(network['A'], 5)
network['D'].add_neighbor(network['B'], 2)

# Simulate RIP protocol
for _ in range(5):  # Run for 5 iterations
    for router in network.values():
        router.update_routing_table()
        router.send_updates()
        router.display_routing_table()

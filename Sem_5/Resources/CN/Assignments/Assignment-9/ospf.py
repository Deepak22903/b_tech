class Router:
    def __init__(self, router_id):
        self.router_id = router_id
        self.routing_table = {}

    def update_routing_table(self, source_router_id, routes):
        for dest, cost in routes.items():
            if dest not in self.routing_table or self.routing_table[dest][0] > cost + self.routing_table[source_router_id][0]:
                self.routing_table[dest] = (cost + self.routing_table[source_router_id][0], source_router_id)

    def print_routing_table(self):
        print(f"Routing Table of Router {self.router_id}:")
        for dest, (cost, next_hop) in self.routing_table.items():
            print(f"Destination: {dest}, Cost: {cost}, Next Hop: Router {next_hop}")

def simulate_ospf():
    # Create routers
    router1 = Router(1)
    router2 = Router(2)
    router3 = Router(3)
    router4 = Router(4)
    router5 = Router(5)
    router6 = Router(6)

    # Set up initial routes
    router1.routing_table = {2: (1, 2), 3: (3, 3)}
    router2.routing_table = {1: (1, 1), 3: (2, 3)}
    router3.routing_table = {4: (3, 1), 2: (2, 2)}
    router4.routing_table = {5: (3, 1), 6: (2, 2)}
    router5.routing_table = {4: (3, 1), 3: (2, 2)}
    router6.routing_table = {5: (3, 1), 1: (2, 2)}

    # Simulate OSPF updates
    router2.update_routing_table(1, {3: 2})  # OSPF uses Dijkstra's algorithm, so all routers immediately get the updated route

    # Print routing tables
    router1.print_routing_table()
    router2.print_routing_table()
    router3.print_routing_table()
    router4.print_routing_table()
    router5.print_routing_table()
    router6.print_routing_table()


# Simulate OSPF
print("\nOSPF:")
simulate_ospf()
graph = {
    "a":["b","c"],
    "b":["a","c","d"],
    "c":["a","b","d","e"],
    "d":["b","c","e","f"],
    "e":["c","d"],
    "f":["d"]
}

def BFS(graph, start):
    queue = []
    queue.append(start)
    visited = set()
    visited.add(start)

    while(len(queue) > 0):
        node = queue.pop(0)

        if node not in visited:
            visited.add(node)
        ##goal = "f"
        ##if node == goal:
            ##return

        for w in graph[node]:
            if w not in visited:
                queue.append(w)
                visited.add(w)
        print(node)

#BFS(graph, "a")

def DFS(graph, start):
    stack = []
    stack.append(start)
    visited = set()
    visited.add(start)

    while(len(stack) > 0):
        node = stack.pop()

        if node not in visited:
            visited.add(node)

        if node == goal:
            return

        for w in graph[node]:
            if w not in visited:
                stack.append(w)
                visited.add(w)
        print(node)

#DFS(graph, "a")




class Graph:
    def __init__(self):
        self.edges = {}
        self.weights = {}

    def neighbors(self, node):
        return self.edges[node]

    def get_cost(self, from_node, to_node):
        return self.weights[(from_node + to_node)]

    a,b,c,d,e,f = range(6)
    Graph1 = [
            {b:2, c:1, d:3, e:9, f:4},
            {c:4, e:4},
            {d:8},
            {e:7},
            {f:5},
            {d:2}
        ]


from queue import PriorityQueue

def ucs(graph, start, goal):
    visited = set()
    queue = PriorityQueue()
    queue.put((0, start))

    while queue:
        cost, node = queue.get()
        if node not in visited:
            visited.add(node)

            if node == goal:
                return

            for i in graph.neighbors(node):
                if i not in visited:
                    total_cost = cost + graph.get_cost(node, i)
                    queue.put((total_cost, i))
        print(node)

ucs(Graph1, "b", "e")

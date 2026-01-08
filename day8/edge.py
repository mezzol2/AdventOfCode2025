import math

class Edge:
    def __init__(self, node1, node2):
        self.node1 = node1
        self.node2 = node2
        self.dist = math.sqrt((node1.x - node2.x)**2+(node1.y - node2.y)**2+(node1.z - node2.z)**2)
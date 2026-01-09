import math
from vertex import Vertex

class Edge:
    def __init__(self, node1:Vertex, node2:Vertex):
        self.node1 = node1
        self.node2 = node2
        self.dist = math.sqrt((node1.x - node2.x)**2+(node1.y - node2.y)**2+(node1.z - node2.z)**2)

    def __eq__(self, other):
        return (self.node1 == other.node1 and self.node2 == other.node2) or (self.node1 == other.node2 and self.node2 == other.node1)
    
    def __hash__(self):
        return hash((self.node1,self.node2))
from vertex import Vertex
from edge import Edge

def main():
    fileName = "test.txt"
    vertex_set = set()
    edge_set = set()

    #read the file and create the set of vertices
    read_file(vertex_set,fileName)

    create_all_edges(vertex_set, edge_set)

    print("hello")


#O(V)
def read_file(vertex_set:set, fileName:str):
    with open(fileName, "r") as file:
        for line in file:
            line = line.strip().split(",")
            #add vertices to the vertex_set
            vertex_set.add( Vertex(int(line[0]),int(line[1]),int(line[2])) )

#O(V^2)
def create_all_edges(vertex_set:set, edge_set:set):
    for v in vertex_set:
        for u in vertex_set:
            if v != u:
                edge = Edge(v,u)
                if edge not in edge_set:
                    edge_set.add(edge)

main()
from vertex import Vertex

def main():
    fileName = "test.txt"
    edge_set = set()
    vertex_set = set()

    #read the file and create the set of vertices
    read_file(vertex_set,fileName)

    for v in vertex_set:
        print(f"{v.x} {v.y} {v.z}")


def read_file(vertex_set:set, fileName:str):
    with open(fileName, "r") as file:
        for line in file:
            line = line.strip().split(",")
            #add vertices to the vertex_set
            vertex_set.add( Vertex(int(line[0]),int(line[1]),int(line[2])) )

main()
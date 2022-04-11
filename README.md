# Shortest-path-using-BFS-on-Graph
This program is based on the adjacency list implementation of a graph. BFS is used to find the shortest path of a given vertex from each vertex.
I have taken the input for the edges in the format: i j (int i space int j).
I am using inputs -1 -1 to quit taking the edges as the input.
The directed or undirected graph is printed accuractely after taking the input for edges.
In case a vertex has no edge connected, the same information will be printed.
It is assumed that the user will enter a correct simple graph, without loops and multiple edges.
The BFS algorithm has been implemented in this program.
Here, three arrays have been used by me to store the information regarding the color, distance from source vertex and the previous vertex for all the vertices labelled 0, 1, 2, ..., N-1.
Also, if any vertex is not reachable from the source vertex, that information has been clearly printed for that vertex.

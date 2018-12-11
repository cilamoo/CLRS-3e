#include <stdio.>
#include "dfs.h"

/*Program Inputs from Figure 22.4 on page 605,
Vertexes: u,v,w,x,y,z,
          0 1 2 3 4 5 
Edges:u->v, u->x, v->y, w->y, w->z, x->v, y->x, z->z,
      0  1  0 3   1 4   2 4   2  5  3  1   4  3  5 5 
int edge_vector[16] = {0, 1, 0, 3, 1, 4, 2, 4, 2, 5, 3, 1, 4, 3, 5, 5};
char vertexes[5] = {'u', 'v', 'w', 'x', 'y', 'z'};
*/

int main(){
    struct Graph *G; 
    int edge_vector[16] = {0, 1, 0, 3, 1, 4, 2, 4, 2, 5, 3, 1, 4, 3, 5, 5};
    char vertexes[6] ={'u', 'v', 'w', 'x', 'y', 'z'};
    G = graph_init(6,8);
    add_edges(G, edge_vector);
    DFS(G);
    printf("path from %c to %c is ", vertexes[0],vertexes[4]);
    print_path(G->Adj,vertexes,0,4);
    printf("\nDFS Done!\n");
    graph_release(G);
    return 0;
}

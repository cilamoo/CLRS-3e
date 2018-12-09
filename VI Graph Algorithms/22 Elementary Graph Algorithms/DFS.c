/*pseudocode
DFS(G)
1 for each vertex u ∈ G.V 
2     u.color = WHITE
3     u.∏ = NIL
4 time = 0 
5 for each vertex u ∈ G.V
6     if u.color = WHITE
7         DFS-VISIT(G,u)

DFS-VISIT(G,u)
1 time = time + 1
2 u.d = time 
3 u.color = GRAY
4 for each v ∈ G.Adj[u]
5     if v.color = WHITE
6         v.∏ = u
7         DFS-VISIT(G,v)
8 u.color = BLACK
9 time = time + 1
10 u.f = time 
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int time = 0; /* global variable */

struct listnode{
    struct vertex *self;
    struct listnode *next;
};

struct vertex {
    int vernum; /*vernum denotes character vertex */ 
    unsigned int color;
    unsigned int parent; /*atrribute u.π */
    int d; 
    int f;
    unsigned int nodenum; /*number of listnodes this vertex has, or edges from this vertex to other */
    struct listnode *head; /*pointer first listnode in list */
};

struct Graph {
    unsigned int vercount; /*  number of vertex */
    unsigned int edgecount; /*number of edge */
    struct listnode *blockmemory; /* block memory for all listnodes */
    struct vertex *Adj; /* pointer to adjacency-list */
};

struct vertex* vertex_init(size_t vnum){
    int i;
    struct vertex *vertex;
    if((vertex = malloc(vnum*sizeof(*vertex))) == NULL)
        return NULL;

    for(i = 0; i < vnum; i++){
        vertex[i].vernum = i;
        vertex[i].color = 1 << 10;  /* WHITE */
        vertex[i].parent = UINT_MAX;
        vertex[i].d = -1;
        vertex[i].f = -1;
        vertex[i].nodenum = 0;
        vertex[i].head = NULL;
    }
    return vertex;       
}

struct Graph* graph_init(size_t vernum, size_t edgenum){
    struct Graph *G;
    if((G = malloc(sizeof(*G))) == NULL)
        return NULL;
    if((G->blockmemory = malloc(edgenum*sizeof(struct listnode))) == NULL )
        return NULL;
    if((G->Adj = vertex_init(vernum)) == NULL)
       return NULL;

    G->vercount = vernum;
    G->edgecount = edgenum;
    return G;
}

void graph_release(struct Graph *G){
    free(G->blockmemory);
    free(G->Adj);
    free(G);
}

/*Program Inputs from Figure 22.4 on page 605,
Vertexes: u,v,w,x,y,z,
          0 1 2 3 4 5 
Edges:u->v, u->x, v->y, w->y, w->z, x->v, y->x, z->z,
      0  1  0 3   1 4   2 4   2  5  3  1   4  3  5 5 
int edge_vector[16] = {0, 1, 0, 3, 1, 4, 2, 4, 2, 5, 3, 1, 4, 3, 5, 5};
char vertexes[5] = {'u', 'v', 'w', 'x', 'y', 'z'};
*/
void add_edges(struct Graph *G, int *ev){
    unsigned int i, j, k;
    struct vertex *Adj;
    struct listnode *bm;
    Adj = G->Adj;
    bm = G->blockmemory;

    for(i = 0; i < G->edgecount; i++){
        j = ev[2*i];
        k = ev[2*i+1];
        bm->next = Adj[j].head;
        Adj[j].head = bm;
        bm->self = &Adj[k];
        bm++; /*get memory from block memory previously allocated, pointer to next listnode */
        Adj[j].nodenum++;
    }
}
void DFS_VISIT(struct Graph *G, struct vertex *u){
    int num;
    time += 1;
    printf("vertex %d is discovered, time is %d, parent is %d \n", u->vernum, time, u->parent);
    struct listnode *head;
    u->d = time;
    u->color = 1<<11; /* GRAY */
    num = u->nodenum;
    head = u->head;
    while(num--){ /* or (head--) != NULL */
        if((head->self->color >> 10) & 1){ /*this vertex has just been discovered */
            head->self->parent = u->vernum;
            DFS_VISIT(G,head->self);
        }
        head--; /*pointer to next listnode */
    }
    u->color = 1 << 12; /* BLACK */
    time += 1;
    u->f = time;
    printf("vertex %d is finished,time is %d, parent is %d\n", u->vernum, time, u->parent );
}

void DFS(struct Graph *G){
    int i;
    struct vertex *u;
    for(i = 0; i < G->vercount; i++){ /*try to discover each vertex*/
        u = &G->Adj[i];
        if((u->color>>10) & 1)
            DFS_VISIT(G,u);
    }

}

/*print path from s to one vertex */
void print_path(struct vertex *Adj, char *c, int start, int dest){
    if(Adj[start].vernum == Adj[dest].vernum)
        printf("%c ", c[start]);
    else if(Adj[dest].parent == UINT_MAX)
        printf("no path from %c to %c exits\n", c[start], c[dest]);
    else
       {
        print_path(Adj, c, start, Adj[dest].parent);
        printf("-> %c ", c[dest]);
       }
}

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

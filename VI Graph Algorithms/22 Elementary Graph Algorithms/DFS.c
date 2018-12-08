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
    int vernum;
    unsigned int color;
    unsigned int parent;
    int d;
    int f;
    unsigned int nodenum;
    struct listnode *head;
};

struct Graph {
    unsigned int vercount;
    unsigned int edgecout;
    struct listnode *blockmemory;
    struct vertex *Adj;
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

void vertex_release(struct vertex *vertex){
    free(vertex);
}

struct Graph* graph_init(size_t vernum, size_t edgenum){
    struct Graph *G;
    if((G = malloc(sizeof(*G))) == NULL)
        return NULL:
    if((G->blockmemory = malloc(edgnum*sizeof(struct listnode))) == NULL )
        return NULL;
    if((G->Adj == vertex_init(vernum)) == NULL)
       return NULL;

    G->vercount = vernum;
    G->edgenum = edgenum;
    return G;
}

void graph_release(struct Graph *G){
    vertex_release(G->blockmemory);
    free(G->Adj);
    free(G);
}
/*Program Inputs from Figure 22.4 on page 605,
Vertexes: u,v,w,x,y,z,
          0 1 2 3 4 5 
Edges:u->v, u->x, v->y, w->y, w->z, x->v, y->x, z->z,
      0  1  0 3   1 4   2 4   2  5  3  1   4  3  5 5 
int edge_vector[16] = {0, 1, 0, 3, 1, 4, 2, 4, 2, 5, 3, 1, 4, 3, 5, 5};
char vertexes[5] ={u, v, w, x, y, z};
*/
void add_edges(struct Graph *G, int *ev){
    unsigned int i, j, k;
    struct vertex *Adj;
    struct listnode *bm;
    Adj = G->Adj;
    bm = G->blockmemory;

    for(i = 0; i < G->edgenum; i++){
        j = ev[2*i];
        k = ev[2*i+1];
        bm->next = Adj[j].head;
        Adj[j].head = bm;
        bm->self = &Adj[k];
        bm++;
        Adj[j].nodenum++;
    }
}
void DFS_VISIT(struct Graph *G, struct vertex *u){
    int num;
    struct listnode *head;
    time += 1;
    u->d = time;
    u->color = 1<<11; /* GRAY */
    num = u->nodenum;
    head = u->head;
    while(num--){ /* or (head--) != NULL */
        if((head->self->color >> 10) & 1){
            head->self->parent = u->vernum;
            DFS_VISIT(G,head->self);
        }
        head--;
    }
    u->color = 1 << 12; /* BLACK */
}

void DFS(struct Graph *G){
    int i;
    struct vertex *u;
    for(i = 0; i < G->vercount; i++){
        u = &G->Adj[i];
        if((u->color>>10) & 1)
            DFS_VISIT(G,u);
    }

}

/*print path from s to one vertex */
void print_path(struct vertex *Adj, char *c, int start, int dest, int limit){
    if(start < 0 || start >= limit || dest < 0 || dest >= limit){
        printf("Wrong Input, Vertexes range from 0 to %d\n", limit-1);
        exit(1);
    }

    if(Adj[start].vernum == Adj[dest].vernum)
        printf("%c ", c[start]);
    else if(Adj[dest].parent == UINT_MAX)
        printf("no path from %c to %c exits\n", c[start], c[dest]);
    else
       {
        print_path(Adj, c, start, Adj[dest].parent, limit);
        printf("%c ", c[dest]);
       }
}

int main(){
    struct Graph *G; 
    int edge_vector[16] = {0, 1, 0, 3, 1, 4, 2, 4, 2, 5, 3, 1, 4, 3, 5, 5};
    char vertexes[5] ={u, v, w, x, y, z};
    G = graph_init(5,8);
    add_edges(G, edge_vector);
    print_path(G->Adj,vertexes,0,3);
    graph_release(G);
    return 0;
}
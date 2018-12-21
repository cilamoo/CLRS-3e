/* BELLMAN-FORD Algorithm, which edge weights may be negative */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Vertex {
    int ver;
    int p;            /* attribute π */
    int d;
}Vertex;

typedef struct Edge{
    int s;    /* start vertex */
    int d;    /* destination vertex */
    int w;    /*weight of edge s->d  */
}Edge;

typedef struct Graph{
    struct Vertex *V;
    struct Edge *E;
    int vernum;
    int edgenum;
}Graph;

Graph* graph_init(size_t vernum, size_t edgenum, int *input){
    Graph *G;
    Vertex *vtmp;
    Edge *etmp;
    size_t  i;

    if((G = (Graph*)malloc(sizeof(*G) + vernum*sizeof(Vertex) + edgenum*sizeof(Edge))) == NULL)
        return NULL;
    
    vtmp = G->V = (Vertex*)G+1;
    etmp = G->E = (Edge*)G->V+vernum;

    G->vernum = (int)vernum;
    G->edgenum = (int)edgenum;
    
    for(i = 0; i < vernum; i++){
        vtmp[i].ver = i;
        vtmp[i].p = INT_MIN; 
        vtmp[i].d = INT_MAX;
    }
    for(i = 0; i < edgenum; i++){
        etmp[i].s = input[3*i];
        etmp[i].d = input[3*i+1];
        etmp[i].w = input[3*i+2];
    }
    
    return G;
}

void graph_release(Graph *G){
    free(G);
}

void relax(Edge *edge, Vertex *ver){
    int u = edge->s;
    int v = edge->d;
    if(ver[v].d > ver[u].d + edge->w){
        ver[v].d = ver[u].d + edge->w;
        ver[v].p = u;
    }
}

int is_true_flase(Graph *G){
    Vertex *V = G->V;
    Edge *E = G->E;
    int i, u, v, w;

    for(i = 0; i < G->edgenum; i++){
        u = E[i].s;
        v = E[i].d;
        w = E[i].w;
        if(V[v].d > V[w].d + w){
            return 0;
        }
    }

    return 1;
}

int BellmanFord(Graph *G, int r){
    Vertex *V;
    Edge *E;
    int i,j,k;

    V = G->V;
    E = G->E;
    V[r].d = 0;
    
    for(i = 0; i < G->vernum-1; i++){
        for(j = 0; j < G->edgenum; j++){
            relax(&E[j],V);
        }
    }

    return is_true_flase(G);
}

void print_path(Vertex *V, int s, int v, char *map){
    if(s == v)
        printf("%c ", map[s]);
    else if(V[v].p == INT_MIN)
        printf("no path from %c to %c exists \n" ,map[s], map[v]);
    else{
        print_path(V,s,V[v].p,map);
        printf(" -> %c",map[v]);
    }
}

int main(){
    char map[5] = {'s','t','x','y','z'};
    int vertex[5] = {0,1,2,3,4};
    int edges[30] ={1,2,5, 1,4,8, 1,3,-4, 2,1,-2, 4,2,-3, 4,3,9, 3,2,7, 3,0,2, 0,1,6, 0,4,7};
    Graph *G;
    int r;

    if((G = Graph_init(5,10,edges)) == NULL){
        printf("Graph_init call failed \n");
        exit(1);
    }

   if((rv = BellmanFord(G, 0)) == 0){
       printf("Encouter a negative weight cycle\n");
       exit(1);
   }

   print_path(G->V,0,4,map);

   graph_release(G);

   return 0;
}
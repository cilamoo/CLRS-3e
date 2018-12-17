/*The algorithms of Kruskal

Pseudocode for disjoint-set forests
MAKE-SET(x)
1 x.p = x
2 x.rank = 0;

UNION(x,y)
1 LINK(FIND-SET(x), FIND-SET(y))

LINK(x,y)
1 if x.rank > y.rank
2     y.p = x
3 else x.p = y
4     if x.rank == y.rank 
5         y.rank = y.rank + 1

FIND-SET(x)
1 if x ≠ x.p
2     x.p = FIND-SET(x.p)
3 return x.p

MST-KRUSKAL(G,w)
1 A = Ø ;
2 for each vertex u ∈ G.V
3     MAKE-SET(u)
4 sort the edges of G.E into nondecreasing order by weight w
5 for each edge (u,v) ∈ G.E, taken in nondecreasing order by weight
6     if FIND-SET(u) ≠ FIND-SET
7         A = A U(u,v)
8         UNION(u,v)
9 return A

*/

#include <stdlib.h>
#include <stdio.h>

typedef struct vertex{
    int ver;
    unsigned int rank;
    struct vertex *p;
}vertex;

typedef struct edge{
    int s;
    int d;
    int weight;
}edge;

void make_set(vertex *x){
    x->p = x;
    x->rank = 0;
}

typedef struct Graph{
    vertex *V;
    edge *E;
    unsigned int vernum;
    unsigned int edgenum;
}Graph;


/* UNION operation*/
void union_opt(vertex *x, vertex *y)
{
    link(find_set(x), find_set(y));
}

void link(vertex *xp, vertex *yp){
    if(xp->rank > yp->rank){
        yp->p = xp;        
    }
    else{
        xp->p = yp;
        if(xp->rank == yp->rank){
            yp->rank += 1;
        }
    }
}

vertex* find_set(vertex *x){
    if(x != x->p)
        x->p = find_set(x->p);
    return x->p;
}


Graph* graph_alloc(size_t vernum, size_t edgenum){
    Graph *G;
    if((G = malloc(sizeof(*G))) == NULL)
        return NULL;
    
    if((G->V = malloc(vernum*sizeof(vertex))) == NULL)
        return NULL;
    
    if((G->E = malloc(edgenum*sizeof(edge))) == NULL)
        return NULL;
    
    G->vernum = (unsigned int)vernum;
    G->edge =  (unsigned int )edgenum;

    return G;
}

void vertex_init(Graph *G){
    unsigned int i;
    vertex *V = G->V;
    for(i = 0; i < G->vernum; i++){
        V[i].ver = i;
        make_set(&G[i]);
    }
}


void edge_init(Graph *G, int *e){
    unsigned int i;
    edge *E = G->E;
    for(i = 0; i < G->edgenum; i++){
        E[i].s = e[3*i];
        E[i].t = e[3*i+1];
        E[i].weight = e[3*i+2];
    }
}

void graph_release(*G){
    free(G->E);
    free(G->V);
    free(G);
}


edge* MST_Kruskal(Graph *G){
    unsigned int i,n;
    int s,t;
    n = G->edgenum;
    edge **SetA, **ptmp;
    edge *sorted_edges[n];
    vertex *V;
    edge *E;

    if((SetA = (edge**)malloc((size_t)n*(sizeof edge*)))) == NULL){
        return NULL;
    }

    ptmp = SetA;
    
    for(i = 0; i < n; i++){
        sorted_edges[i] = &G->E[i];
        SetA[i] = NULL;
    }

    quicksort(&sorted_edges[0],0,n-1);

    E = G->E;
    V = G->V;
   for(i = 0; i < n; i++){
        s = E[i].s;
        t = E[i].t;
       if(find_set(&V[s]) != find_set(&V[t])){
           SetA++ = &E[i];
           union_opt(&V[s], &V[t]);
       }
   }
   
   return ptemp; 
}

void print_MST_Kruskal(edge** A){
    int i = 1;
    printf("MST: ")
    while(A++ != NULL){
        printf("The ith edge is %d -> %d\n", i++, (**A).s,(**A).t);
    }
}

void swap(edge **v1, edge **v2){
    struct edge *tmp;
    tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

int partition(edge **A, int p, int r){
    int x, i, j;
    i = p - 1;
    x = A[r]->weight;
    for(j = p; j < r; j++){
        if(A[j]->weight <= x){
            i += 1;
            swap(&A[i],&A[j]);
        }
    }
    swap(&A[i+1],&A[r]);
    return i + 1;
}

void quicksort(edge **A, int p, int r){
    int q;
    if(p < r){
        q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}

/*Input from Figure 23.4 on page 632 
char vertexes[9] = {'a','b','c','d','e','f','g','h','i'};
int vermap[9] = {0,1,2,3,4,5,6,7,8};
int edges_weight[42] = {0,1,4, 0,7,8, 1,2,8, 1,7,11, 2,3,7, 2,5,4, 2,8,2, 3,4,9, 4,5,10, 3,5,14, 5,6,2, 6,8,6, 6,7,1, 7,8,1 };
*/
int main(){
    char vertexes[9] = {'a','b','c','d','e','f','g','h','i'};
    int vermap[9] = {0,1,2,3,4,5,6,7,8};
    int edges_weight[42] = {0,1,4, 0,7,8, 1,2,8, 1,7,11, 2,3,7, 2,5,4, 2,8,2, 3,4,9, 4,5,10, 3,5,14, 5,6,2, 6,8,6, 6,7,1, 7,8,1 };
    Graph *G;
    edge **SetA, **ptmp;

    if((G = graph_alloc(9,14) == NULL){
        printf("fail to allocate memory \n");
        return -1;
    }
    
    vertex_init(G);
    edge_init(G, edges_weight);
    
    ptmp = SetA = MST_Kruskal(G);
    print_MST_Kruskal(SetA);
    graph_release(G);
    free(ptmp);

    return 0;
}  
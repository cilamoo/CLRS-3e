/* DAG-SHORTEST-PATHS,Shortest paths are always well defined in a dag,
since even if there are negative-weight edges, no negative-weight cycles can exist */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct listnode{
    struct vertex *self;
    struct listnode *next;
    int w;            /* weight of this edge */
};

struct vertex {
    int vernum;     /*vernum denotes character vertex */
    unsigned int color;
    int distance; 
    unsigned int parent;    /*atrribute u.π */
    int d;
    int f;
    struct listnode *head;    /*pointer first listnode in list */
    unsigned int nodenum;     /*number of listnodes this vertex has, or edges from this vertex to other */
};

struct Graph {
    unsigned int vercount;     /*  number of vertex */
    unsigned int edgecount;    /*number of edge */
    struct listnode *blockmemory;    /* block memory for all listnodes */
    struct vertex *Adj;     /* pointer to adjacency-list */
};

static int time = 0;    /* global variable */

struct vertex* vertex_init(size_t vnum){
    int i;
    struct vertex *vertex;
    if((vertex = malloc(vnum*sizeof(*vertex))) == NULL)
        return NULL;

    for(i = 0; i < vnum; i++){
        vertex[i].vernum = i;
        vertex[i].color = 1 << 10;  /* WHITE */
        vertex[i].parent = UINT_MAX;
        vertex[i].distance = 1024;
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

    G->vercount = (unsigned int)vernum;
    G->edgecount = (unsigned int)edgenum;
    return G;
}

void graph_release(struct Graph *G){
    free(G->blockmemory);
    free(G->Adj);
    free(G);
}

void add_edges(struct Graph *G, int *ev){
    unsigned int i, j, k;
    struct vertex *Adj;
    struct listnode *bm;
    Adj = G->Adj;
    bm = G->blockmemory;

    for(i = 0; i < G->edgecount; i++){
        j = ev[3*i];
        k = ev[3*i+1];
        bm->next = Adj[j].head;
        bm->w = ev[3*i+2];
        bm->self = &Adj[k];
        Adj[j].head = bm;
        Adj[j].nodenum++;
        bm++;     /*get memory from block memory previously allocated, pointer to next listnode */
    }
}

void DFS_VISIT(struct Graph *G, struct vertex *u){
    int i;
    time += 1;
    printf("vertex %d is discovered, time is %d, parent is %u \n", u->vernum, time, u->parent);
    struct listnode *head;
    u->d = time;
    u->color = 1<<11;     /* GRAY */
    head = u->head;
    while(head != NULL){
        if((head->self->color >> 10) & 1){ /*this vertex has just been discovered */
            head->self->parent = u->vernum;
            DFS_VISIT(G,head->self);
        }

        head = head->next; /* pointer to next listnode */ 
    }
    time += 1;
    u->f = time;
    u->color = 1 << 12;    /* BLACK */
    printf("vertex %d is finished,time is %d, parent is %u\n", u->vernum, time, u->parent );
}

void DFS(struct Graph *G){
    int i;
    struct vertex *u;
    for(i = 0; i < G->vercount; i++){    /*try to discover each vertex*/
        u = &G->Adj[i];
        if((u->color>>10) & 1)
            DFS_VISIT(G,u);
    }

}

/*quicksort*/
void swap(struct vertex **v1, struct vertex **v2){
    struct vertex *tmp;
    tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

int partition(struct vertex **A, int p, int r){
    int x, i, j;
    i = p - 1;
    x = A[r]->f;
    for(j = p; j < r; j++){
        if(A[j]->f > x){
            i += 1;
            swap(&A[i],&A[j]);
        }
    }
    swap(&A[i+1],&A[r]);
    return i + 1;
}

void quicksort(struct vertex **A, int p, int r){
    int q;
    if(p < r){
        q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}
void print_topo(struct vertex **a, int n){
    int i;
    for(i=0;i<n;i++){
        printf("[%dth vertex:%d parent:%u d:%d f:%d]\n",i, \
              a[i]->vernum, a[i]->parent,a[i]->d,a[i]->f);
    }
}

struct vertex** toposort_array_create(struct vertex *Adj, unsigned int n){
    struct vertex **a;
    unsigned int i;
   
    if((a = (struct vertex**)malloc(n*sizeof(*a))) == NULL){
        return NULL;
    }

    for(i = 0; i < n; i++){
        a[i] = &Adj[i];
    }
    
    quicksort(a,0,n-1);
    print_topo(a,n);
    return a;
}

void toposort_array_release(struct vertex **a){
    free(a);
}

void relax(struct vertex *u, struct vertex *v, int w){
    if(v->distance > u->distance + w){
        v->distance = u->distance + w;
        v->parent = u-> vernum;
    }
}

void dag_shorted_paths(struct Graph *G, int s){
    unsigned int i, n;
    int w;
    struct vertex **sorted_array;
    struct vertex *Adj, *u, *v;
    struct listnode *head;
    
    Adj = G->Adj;
    Adj[s].distance = 0;
    n = G->vercount;
    if((sorted_array = toposort_array_create(Adj,n)) == NULL){
        printf("toposort_array_create call failed\n");
        exit(1);
    }
    
    for(i=0; i < n; i++){
        u = sorted_array[i];
        head = u->head;
        while(head != NULL){
            v = head->self;
            w = head->w;
            relax(u,v,w);
            head = head->next;
        }
    }
    toposort_array_release(sorted_array);
}

void print_path(struct vertex *Adj, int s,  int v, char *map){
    if(Adj[s].vernum == Adj[v].vernum)
        printf("%c ", map[s]);
    else if(Adj[v].parent == UINT_MAX)
        printf("no path from %c to %c exists \n" ,map[s], map[v]);
    else{
        print_path(Adj,s,Adj[v].parent,map);
        printf(" -> %c",map[v]);
    }
}

void print_distance(struct vertex *Adj, char *c,int n){
    int i;
    printf("\ndistance from %c:\n",c[0]);
    for(i=1;i<n;i++){
       printf("to vertex %c is %d\n",c[i],Adj[i].distance);
   }
}
/*Input from figure is not a dag.Although,topological sort is applied to dag,int this example,
 DFS starts at source vertex 0 , topo sort still works */
int main(){
    char map[5] = {'s','t','x','z','y'};
    int vertex[5] = {0,1,2,3,4};
    int edges[30] ={1,2,5, 1,4,8, 1,3,-4, 2,1,-2, 4,2,-3, 4,3,9, 3,2,7, 3,0,2, 0,1,6, 0,4,7};
    int r = 0;
    struct Graph *G;

    if((G = graph_init(5,10)) == NULL){
        printf("Graph_init call failed \n");
        exit(1);
    }

    add_edges(G,edges);
    DFS(G);
    dag_shorted_paths(G,r);
    print_path(G->Adj,0,3,map);
    print_distance(G->Adj,map,5);
    graph_release(G);

    return 0;
}

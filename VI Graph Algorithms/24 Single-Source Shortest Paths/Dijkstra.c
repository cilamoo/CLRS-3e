/*DIJKSTRA, all edge weights are nonnegative.*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct listnode {
    struct Vertex *self;
    struct listnode *next;
    unsigned int weight;                /* all edge weights are nonnegative */
}listnode;

typedef struct Vertex{
    int ver;                     /* use number to denote a vertex, not character */
    int index;                   /*index locates this vetex within min-priority queue */
    int parent;                  /* attribute π*/            
    unsigned int  key;           /* atrribute d*/
    struct listnode *head;       /* pointer to adjacency-list of this vertex */
}Vertex;

typedef struct Graph{
    unsigned int vernum;             /*the number of vertexes*/
    unsigned int edgenum;            /*the number of edges*/
    struct listnode *blockmemory;    /* block memory for all listnodes */
    struct Vertex *Adj;             /* pointer to adjacency-list */
}Graph;

/*min-priority queue*/
int PARENT(int i){
    return i>>1;
} 

int LEFT(int i){
    return i<<1;
}

int RIGHT(int i){
    return (i<<1)+1;
}

void swap(Vertex **v1, Vertex **v2){
    Vertex *tmp;
    tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

typedef struct min_heap{
    struct Vertex **A;            /* pointer to an array storing elements */
    unsigned int heap_size;       
}min_heap;

void min_heapify(Vertex **A, int i, unsigned int heap_size){
    int l, r, smallest;
    l = LEFT(i);
    r = RIGHT(i);

    if(l <= heap_size && A[l-1]->key < A[i-1]->key)
        smallest = l;
    else
        smallest = i;
    
    if(r <= heap_size && A[r-1]->key < A[smallest-1]->key)
        smallest = r;

    if(smallest != i){
        A[smallest-1]->index = i;            /*update index */
        A[i-1]->index = smallest;
        swap(&A[smallest-1],&A[i-1]);
        min_heapify(A,smallest,heap_size);
    }
}

void build_min_heap(Vertex **A, unsigned int length){
    unsigned int heap_size, i;
    heap_size = length;
    
    for(i=length/2; i > 0; i--){
        min_heapify(A,i,heap_size);
    }
}

Vertex* heap_extract_min(min_heap *Q){
    Vertex *min;

    if(Q->heap_size < 1){
        printf("heap underflow\n");
        return NULL;
    }
    
    min = Q->A[0];
    min->index = -1;              /*-1 means that the vertex is not in set Q*/
    Q->A[0] = Q->A[Q->heap_size-1];
    Q->heap_size -= 1;
    min_heapify(Q->A,1,Q->heap_size);

    return min;
}

void heap_decrease_key(Vertex **A, int i, unsigned int key){
    if(key > A[i-1]->key){
        printf("error: new key is bigger than current key\n");
        exit(1);
    }

    int j = i;
    A[j-1]->key = key;
    while(j >1 && A[PARENT(j)-1]->key > A[j-1]->key){
        A[PARENT(j)-1]->index = j;
        A[j-1]->index = PARENT(j);
        swap(&A[PARENT(j)-1],&A[j-1]);
        j = PARENT(j);
    }
}

min_heap* min_heap_alloc(Graph *G, int r){
    size_t i;
    min_heap *p;
    Vertex **A;
    Vertex* Adj = G->Adj;
    size_t size =(size_t)G->vernum;

    if((p = (min_heap*)malloc(sizeof(*p)+size*sizeof(*A))) == NULL){ /*a continuous memory including the\
                                                                         size of struct min_heap and array A */
        return NULL;
    }
    A = p->A =(Vertex**)(p+1);                /* make array A point right address */ 
    p->heap_size = (unsigned int)size;

    for(i = 0; i < size; i++){
        A[i] = &Adj[i];
    }

    Adj[r].key = 0;
    build_min_heap(A, (unsigned int)size);

    return p;
}

void min_heap_free(min_heap *Q){
    free(Q);
}

Vertex* vertex_init(size_t vnum){
    int i;
    Vertex *vertex;
    if((vertex = malloc(vnum*sizeof(*vertex))) == NULL)
        return NULL;

    for(i = 0; i < (int)vnum; i++){
        vertex[i].ver = i;
        vertex[i].index = i+1;
        vertex[i].parent = INT_MAX;
        vertex[i].key = UINT_MAX;
        vertex[i].head = NULL;
    }
    return vertex;       
}

Graph* graph_alloc(size_t vernum, size_t edgenum){
    Graph *G;
    if((G = malloc(sizeof(*G))) == NULL)
        return NULL;

    if((G->blockmemory = malloc((edgenum+1)*sizeof(struct listnode))) == NULL ) /*+1, in case bm is out of bound in function add_edges*/
        return NULL;
    if((G->Adj = vertex_init(vernum)) == NULL)
       return NULL;

    G->vernum = vernum;
    G->edgenum = edgenum;
    return G;
}

void graph_release(Graph *G){
    free(G->blockmemory);
    free(G->Adj);
    free(G);
}

void add_edges(Graph *G, int *ev){
    unsigned int i, j, k, w;
    Vertex *Adj;
    listnode *bm;
    Adj = G->Adj;
    bm = G->blockmemory;

    for(i = 0; i < G->edgenum; i++){
        j = ev[3*i];
        k = ev[3*i+1];
        w = ev[3*i+2];
       
        bm->next = Adj[j].head;
        bm->weight = w;
        bm->self = &Adj[k];

        Adj[j].head = bm;     
        
        bm++;                 /*get memory from block memory previously allocated, pointer to next listnode */   
    }
}

/* Danger:That key equals UINT_MAX is safe in Dijkstra,but in other situation, 
key is easily greater than UINT_MAX */
void relax(Vertex **A, Vertex *u, Vertex *v, int w){
    if(v->key > u->key + w){
       heap_decrease_key(A, v->index, u->key+w);
        v->parent = u-> ver;
    }
}

Vertex** Dijkstra(Graph *G, int r){
    Vertex **spset;                /*shortest-path set*/
    min_heap *Q;
    Vertex *u,*v;
    listnode *head;
    int index;
    unsigned int w;

    if((spset =(Vertex**)malloc((size_t)G->vernum*sizeof(*spset))) == NULL){
        return NULL; 
    }

    if((Q = min_heap_alloc(G,r)) == NULL){
        printf("min_heap_alloc call allocated memory failed\n");
        exit(1);
    }

    index = 0;
    while(Q->heap_size != 0){
        u = heap_extract_min(Q);
        printf("Extracted vertex %d\n",u->ver);
        spset[index++] = u;
        head = u->head;
        while(head != NULL){
            v = head->self;
            w = head->weight;
            relax(Q->A,u,v,w);
            head = head->next;
        }
    }
    
    min_heap_free(Q);

    return spset;
}

void print_shortest_path(Vertex **s, char *c, int r, int n){
    int i;
    int j;
    printf("Shortest-path starts from %c\n",c[r]);
    for(i = 1; i < n; i++){
        j = s[i]->ver;
        printf("distance from %c to %c is %u\n", c[r], c[j], s[i]->key);
    }
}

int main(){
    char map[5] = {'s','t','x','y','z'};
    int edges[30] = {0,1,10, 0,3,5, 1,2,1, 1,3,2, 2,4,4, 3,1,3, 3,2,9, 3,4,2, 4,2,6, 4,0,7};
    Graph *G;
    Vertex **S;
    int r;
    r = 0;

    G = graph_alloc(5,10);
    add_edges(G,edges);
    if((S = Dijkstra(G,r)) == NULL){
        printf("malloc failed on Set S \n");
        exit(1); 
    }
    
    print_shortest_path(S,map,r,5);
    
    free(S);
    graph_release(G);

    return 0;
}

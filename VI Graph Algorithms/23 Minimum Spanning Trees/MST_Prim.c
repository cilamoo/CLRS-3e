/* Prim’s algorithm */

#include <stdlib.h>

typedef struct listnode {
    struct vertex *self;
    struct listnode *next;
    int weight;
}listnode;

typedef struct Vertex{
    int ver;                     /* use number to denote a vertex, not character */
    int index;                   /*index locates this vetex within min-priority queue */
    int parent;                  
    unsigned int  key;           /* the attribute key is the minimum weight of any edge connecting this vertex to a vertex in the tree */
    unsigned int nodenum;             /* the number of edges leaving this vertex */
    struct listnode *head;       /* pointer to adjacency-list of this vertex */
}Vertex;

typedef struct Graph{
    unsigned int vernum;             /*the number of vertexes*/
    unsigned int edgenum;            /*the number of edges*/
    struct listnode *blockmemory;    /* block memory for all listnodes */
    struct Vertex *Adj;             /* pointer to adjacency-list */
}Graph;

typedef struct Edge{
    int s;            /* start vertex */
    int d;            /* destination vertex */
    int weight;     
}Edge;

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

void swap(struct Vertex **v1, struct vertex **v2){
    struct Vertex *tmp;
    tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

typedef struct min_heap{
    struct Vertex **A;            /* pointer to an array storing elements */
    unsigned int heap_size;       
    unsigned int n;               /*size of initial min-heap */
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
    min->index = -1;              /*-1 means that the vertex is not in set Q, use this index for testing in function MST_PRIM */
    Q->A[0] = Q->A[Q->heap_size-1];
    Q->heap_size -= 1;
    min_heapify(Q->A,1,Q->heap_size);

    return min;
}

void heap_decrease_key(Vertex **A, int i, unsigned int key){
    if(key > A[i-1]->key){
        exit(1);
        printf("error: new key is bigger than current key\n");
    }

    int j = i;
    A[j-1]->key = key;
    while(j >1 && A[PARENT(j)-1]->key > A[j-1]->key){
        A[PARENT(j)-1]->index = j;
        A[j-1]->index = PARENT(j);
        j = PARENT(j);
    }
}

min_heap* min_heap_alloc(Graph *G, int i){
    size_t i;
    min_heap *p;
    Vertex **A;
    Vertex* Adj = G->Adj;
    size_t size =(size_t)G->vernum;

    if((p = (min_heap*)malloc(sizeof(*p)+size*sizeof(Vertex*))) == NULL){
        return NULL;
    }
    A = p->A =(Vertex**)(p+1);
    p->heap_size = n = (unsigned int)size;

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
        vertex[i].nodenum = 0;
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

    G->vercount = vernum;
    G->edgecount = edgenum;
    return G;
}

void graph_release(Graph *G){
    free(G->blockmemory);
    free(G->Adj);
    free(G);
}

void add_edges(Graph *G, int *ev){     /*Can be reconstructed for undirected graph, since the path u->v means v->u */
    unsigned int i, j, k, w;
    struct vertex *Adj;
    struct listnode *bm;
    Adj = G->Adj;
    bm = G->blockmemory;

    for(i = 0; i < G->edgecount; i++){
        /*path j->k*/
        j = ev[3*i];
        k = ev[3*i+1];
        w = ev[3*i+2]
        bm->next = Adj[j].head;
        bm->weight = w;
        Adj[j].head = bm;     
        bm->self = &Adj[k];
        bm++;                        /*get memory from block memory previously allocated, pointer to next listnode */   
        Adj[j].nodenum++;
        
        /*path k->j */
        bm->next = Adj[k].head;
        bm->weight = w;
        Adj[k].head = bm;
        bm->self = &Adj[j];
        bm++;
        Adj[k].nodenum++;
        
    }
}

void MST_PRIM(Graph *G, int r){
    min_heap *Q;
    Vertex *u,*v;
    Vertex **A;
    listnode *head;
    unsigned int w;

    Q = min_heap_alloc(G,r);        /* start from vertex 0, r=0 */
    A = Q->A;

    while(Q->heap_size != 0){
        u = heap_extract_min(Q);
        head = u->head;
        while(head != NULL){
            v = head->self;
            w = head->weight;
            if(v->index != -1 && w < v->key){
                v->parent = u->ver;
                heap_decrease_key(A, v->index, w);
            }
            head = head->next;
        }
    } 

    min_heap_free(Q);
}

void print_PRIM(Graph *G, char *pc, int r){
    unsigned int i;
    Vertex *Adj = G->Adj;
    printf("MST-PRIM starts from vertex %c\n",pc[r]);

    for(i = 0; i < G->vernum; i++){
        if(i != r)
            printf("vertex %c's parent is %c\n", pc[Adj[i]->ver], pc[Adj[i].parent]);
    }
    printf("\n");
}

int main(){
    char vertexes[9] = {'a','b','c','d','e','f','g','h','i'};
    int vermap[9] = {0,1,2,3,4,5,6,7,8};
    int edges_weight[42] = {0,1,4, 0,7,8, 1,2,8, 1,7,11, 2,3,7, 2,5,4,\
                            2,8,2, 3,4,9, 4,5,10, 3,5,14, 5,6,2, 6,8,6, 6,7,1, 7,8,7};
    int r = 0;

    Graph *G;
    G = graph_alloc(9,28);
    add_edges(G,adges_weight);
    MST_PRIM(G,r);
    print_PRIM(G,vertexes,r);

    graph_release(G);
    
    return 0;
}
/* pseudocode：
BFS(G,s)
1 for each vertex u ∈ G.V - {s}
2     u.color = WHITE
3     u.d = ∞
4     u.∏ = NIL
5 s.color = GRAY
6 s.d = 0
7 s.∏ = NIL
8 Q = Ø
9 ENQUEUE(Q,s)
10 while Q ≠ Ø 
11     u = DEQUEUE(Q)
12     for each v ∈ Adj[u]
13         if v.color = WHITE
14             v.color = GRAY
15             v.d = u.d + 1 
16             v.∏ = u
17             ENQUEUE(Q,v) 
18     u.color = BLACK

PRINT-PATH(G,s,v)
1 if v == s
2     print s
3 elseif v.∏ == NIL 
4     print “no path from” s “to” v “exists”
5 else PRINT-PATH.G(G,s,v.∏)
6     print v 
*/


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/*adjacency-list representation */ 
/*adjacency-list node*/
struct listnode {
    struct Vertex *self;     /* pointer to vertex */
    struct listnode *next;   /*next listnode */ 
};

struct Vertex{
    int vertex; 
    int parent;          /*atrribute Π*/
    int color;
    int distance;        
    struct listnode *head; 
    unsigned int nodenum;  /* the number of listnode this Vertex has */
};

/*vertexes init*/
struct Vertex* vertex_init(size_t vnum){
    struct Vertex *Adj;
    int i;

    if((Adj = malloc(sizeof(*Adj)*vnum)) == NULL)
        return NULL;
    
    for(i = 0; i < vnum; i++){
        Adj[i].vertex = i;
        Adj[i].parent = INT_MAX;
        Adj[i].color = 1 << 10; /* WHITE */
        Adj[i].distance = INT_MAX;
        Adj[i].head = NULL;
        Adj[i].nodenum = 0;
    }
    printf("Vertexes = %d, vertex_init done, Adj[4].vertex == %d \n", vnum,Adj[4].vertex);
    return Adj;
}

/*add listnode to Adjlist */
void add_list(struct Vertex *Adj, int v1, int v2){
    struct listnode *ln1, *ln2;
    struct Vertex *ver1, *ver2;
    
    ver1 = &Adj[v1];
    ver2 = &Adj[v2];
    /* maybe have memory fragment,should allloc continuous block */
    if((ln1 = malloc(sizeof(struct listnode))) == NULL)
        return;
    
    if((ln2 = malloc(sizeof(struct listnode))) == NULL)
        return;
    
    ln1->self = ver1;
    ln2->self = ver2;

    ln2->next = ver1->head;
    ver1->head = ln2;
    ver1->nodenum++;

    ln1->next = ver2->head;
    ver2->head = ln1;
    ver2->nodenum++;
}

struct Vertex* Adjlist_create(size_t vernum, int *edge, int n){
    struct Vertex *Adj;
    int i;

    Adj = vertex_init(vernum);
    for(i = 0; i < n; i++){
        add_list(Adj,edge[2*i],edge[2*i+1]);
    }
   
    /*debug*/
    {
       int j;
       for(j = 0; j < vernum; j++){
           int num = Adj[j].nodenum;
           printf("Vertex %d have %d edge(s):\n", Adj[j].vertex, num);
           int k;
           struct listnode *ln = Adj[j].head;
           for(k = 0; k < num; k++){
              struct listnode *next = ln->next;
              printf("%d\n",ln->self->vertex);
              ln = next; 
        }
     }
    }
   
    return Adj;
}

void Adjlist_release(struct Vertex *Adj, int vnum){
    int i;
    struct Vertex *ver;
    struct listnode  *delln;
    printf("start freeing Adjlist memory\n");
    for(i = 0; i < vnum; i++){
        ver = &Adj[i];
        delln = ver->head;
        while(delln != NULL){
            ver->head = delln->next;
            free(delln);
            delln = ver->head;
        }
    }
    free(Adj);
    printf("have freed Adjlist memory\n");
}

/* FIFO queue, initially, head = tail = 1 */
struct Queue{
    unsigned int head;
    unsigned int tail;
    unsigned int length;
    struct Vertex **p;
};

struct Queue* queue_create(size_t num){
    struct Queue *queue;

    if((queue = malloc(sizeof(*queue))) == NULL)
        return NULL;
    
    if((queue->p = (struct Vertex**) malloc((num+1)*sizeof(struct Vertex*))) == NULL)
        return NULL;
    
    queue->head = queue->tail = 1;
    queue->length = (unsigned int) num + 1;
    printf("Alloc a queue\n");
    return queue;
}

void queue_release(struct Queue *pq){
    if(pq == NULL) return;
    free(pq->p);
    free(pq);
    printf("release queue\n");
}

void enqueue(struct Queue *pq,  struct Vertex *pv){
    if((pq->head == pq->tail + 1) || (pq->head == 1 && pq->tail == pq->length)){
        printf("queue overflows\n"); 
        exit(1);
    }
    
    pq->p[pq->tail-1] = pv; 
    
    if(pq->tail == pq->length)
        pq->tail = 1;
    else 
        pq->tail += 1;
    printf("add vertex %d to Queue, meanwhile ,head = %d, tail = %d\n", pv->vertex, pq->head, pq->tail);  
}

struct Vertex* dequeue(struct Queue *pq){
    struct Vertex *x;

    if(pq->head == pq->tail){
        printf("queue underflows\n");
        exit(1);
    }
    x = pq->p[pq->head-1];

    if(pq->head == pq->length)
        pq->head = 1;        
    else
        pq->head += 1;
    printf("delete vertex %d from Queue, meanwhile ,head = %d, tail = %d \n",x->vertex, pq->head, pq->tail);   
    return x;
}

void BFS(struct Vertex *Adj, int start, size_t vnum){
    printf("BFS start, start = %d, vnum = %d\n", start,vnum);
    struct Vertex *s;
    s = &Adj[start];
    s->color = 1 << 11;/*GRAY*/
    s->distance = 0;
    struct Queue* Q = queue_create(vnum);
    enqueue(Q,s);
    while(Q->head != Q->tail){
        unsigned int i;
        struct Vertex *u = dequeue(Q);
        struct listnode *ln = u->head;
        for(i = 0; i < u->nodenum; i++){
            struct Vertex *v = ln->self;
            if( (v->color>>10) & 1){
                printf("discover vertex %d's edge  %d\n", u->vertex, v->vertex);
                v->color = 1 << 11;
                v->distance = u->distance + 1; 
                v->parent = u->vertex;
                enqueue(Q,v);
            }
            ln = ln-> next;
        }
        printf("Have discovered all edges of %d\n", u->vertex);
        u->color = 1 << 12;/*BLACK*/
    }
    queue_release(Q);
    printf("BFS done\n");
}

/*print path from s to one vertex */
void print_path(struct Vertex *Adj, char *c, int start, int dest, int limit){
    if(start < 0 || start >= limit || dest < 0 || dest >= limit){
        printf("Wrong Input, Vertexes range from 0 to %d\n", limit-1);
        exit(1);
    }

    if(Adj[start].vertex == Adj[dest].vertex)
        printf("%c ", c[start]);
    else if(Adj[dest].parent == INT_MAX)
        printf("no path from %c to %c exits\n", c[start], c[dest]);
    else
       {
        print_path(Adj, c, start, Adj[dest].parent, limit);
        printf("%c ", c[dest]);
       }
}

/*Program Inputs from figure 22.3 on page 596

vertexes,using character to denote, are:
{'v', 'r', 's', 'w', 'x', 't', 'u', 'y'};
for convenience,
map character vertex to number vertex: 
v -> 0 , r ->1, s -> 2,w ->3, x ->4, t-> 5,u-> 6, y ->7

undirected edges are : 
{v->r}, {r->(v,s)}, {s->(r,w)}, {w->(s,t,x)},{x->(w,t,u,y)},
{t->(w,x,u)},{u->(t,x,y)},{y(x,u)}

that is:              
{'v', 'r'}, 0 1
{'r', 'v','s'}, 1 0 2
{'s','r', 'w'}   2 1 3
{'w', 's', 't', 'x'} 3 2 5 4
{'x', 'w', 't', 'u', 'y'}4 3 5 6 7
{'t', 'w', 'x', 'u'} 5 3 4 6 
{'u', 't', 'x', 'y'} 6 5 4 7
{'y', 'x', 'u'} 7 4 6

using two vertexes denotes 10 edges:
0 1, 1 2, 2 3, 3 4, 3 5,4 5,5 6, 4 6, 4 7, 6 7,
In vertex_vector, two elements constitute an edge starting at index 0, 
such as (0,1),(2,3),(4,5)...
int vertex_vector[20] = {0,1,1,2,2,3,3,4,3,5,4,5,5,6,4,6,4,7,6,7}
*/

int main(){
    struct Vertex *Adjlist;
    int vertex_vector[20] = {0, 1, 1, 2, 2, 3, 3, 4, 3, 5, 4, 5, 5, 6, 4, 6, 4, 7, 6, 7};
    char cver[8] = {'v', 'r', 's', 'w', 'x', 't', 'u', 'y'};
    int nvertex = 8;

    Adjlist = Adjlist_create(nvertex,vertex_vector,10);
    BFS(Adjlist,2,8);
    print_path(Adjlist, cver, 2, 7, 8);
    printf("\n");
    Adjlist_release(Adjlist, nvertex);
    return 0;
}

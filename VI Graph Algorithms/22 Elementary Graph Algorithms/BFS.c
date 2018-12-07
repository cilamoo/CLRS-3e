/*BFS(G,s)
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
*/

/*
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
include <stdlib.h>

/*adjacency-list representation */ 
struct listnode {
    struct Vertex *self;
    struct listnode *next; 
};

struct Vertex{
    int vertex;
    int parent;
    int color;
    int distance;
    struct listnode *head; 
    unsigned int nodenum; 
};


struct Vertex* vertex_init(size_t vnum){
    struct Vertex *Adj;
    int i;

    if((Adj = malloc(vnum*sizeof(*Adj))) == NULL)
        return NULL;
    
    for(i = 0; i < vnum; i++){
        Adj[i]->vertex = i;
        Adj[i]->parent = INT_MAX;
        Adj[i]->color = 1 << 10; /* WHITE */
        Adj[i]->distance = INT_MAX;
        Adj[i]->head = NULL;
        Adj[i]->nodenum = 0;
    }
    return Adj;
}

/*
 edges {v,r}, {r,v,s}, {s,r,w}, {w,s,t,x},{x,w,t,u,y},{t,w,x,u},{u,t,x,y},{y,x,u}
v 0 , r 1, s 2,w 3, x 4, t 5,u 6, y 7,              
char list1[2] ={'v', 'r'}, 0 1
list2[3] = {'r', 'v','s'}, 1 0 2
list3[3] ={'s','r', 'w'}   2 1 3
list4[4] = {'w', 's', 't', 'x'} 3 2 5 4
list5[5] = {'x', 'w', 't', 'u', 'y'}4 3 5 6 7
list6[4] = {'t', 'w', 'x', 'u'} 5 3 4 6 
list7[4] = {'u', 't', 'x', 'y'} 6 5 4 7
list8[3] = {'y', 'x', 'u'} 7 4 6
0 1, 1 2, 2 3, 3 4, 3 5,4 5,5 6, 4 6, 4 7, 6 7,
int vertex_vector[20] = {0,1,1,2,2,3,3,4,3,5,4,5,5,6,4,6,4,7,6,7}
*/

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

struct Vertex* Adjlist_create(size_t vernum, int *edge){
    struct Vertex *Adj;
    int i,edgenum;

    Adj = vertex_init(vernum);
    edgenum = (sizeof(edge)/sizeof(edge[0]))/2;
    for(i = 0; i < edgenum; i++){
        add_list(Adj,edge[i],edge[i+1]);
    }
    return Adj
}

void Adjlist_release(struct Vertex *Adj, int vnum){
    int i;
    struct Vertex *ver;
    struct listnode  *delln;
    for(i = 0; i < vnum; i++){
        ver = &Adj[i]
        delln = ver->head;
        whie(delln != NULL){
            ver->head = delln->next;
            free(delln);
            delln = var->head;
        }
        free(ver);
    }
}

/* FIFO queue, initially, head = tail = 1 */
struct Queue{
    unsigned int head;
    unsigned int tail;
    unsigned int length;
    struct Vertex *p;
};

struct Queue* queue_create(size_t num){
    struct Queue *queue;

    if((queue = malloc(sizeof(*queue))) == NULL)
        return NULL;
    
    if((queue->p =  malloc((num+1)*sizeof(struct Vertex*))) == NULL)
        return NULL;
    
    queue->head = queue->tail = 1;
    queue->length = (unsigned int) num + 1;
    
    return queue;
}

void queue_release(struct Queue *pq){
    if(pq == NULL) return;
    free(pq->p);
    free(pq);
}

void enqueue(struct Queue *pq,  struct Vertex *pv){
    if((pq->head == pq->tail + 1) || (pq->head==1 && pq->tail==pq->length)){
        printf("queue overflows\n"); 
        exit(1);
    }
    
    pq -> p[pq->tail-1] = pv; 
    
    if(pq->tail == pq->length)
        pq->tail = 1;
    else 
        pq->tail += 1;
}

struct Vertex* dequeue(struct Queue *pq){
    struct Vertex *x;

    if(pq->head == pq->tail){
        printf("queue underflows\n")
        exit(1);
    }
    x = pq->p[p->head-1];

    if(pq->head = pq->length)
        pq->head = 1;        
    else
        pq->head += 1;

    return x;
}

void BFS(struct Vertex *Adj, int start, size_t vnum){
    struct Vertex *s;
    s = &Vertex[start];
    s->color = 1 << 11;
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
                v->color = 1 << 11;
                v->distance = u->distance + 1 
                v.parent = u->vertex;
                enqueue(Q,v)
            }
            ln = ln-> next;
        }
        u->color = 1 << 12;
    }
    queue_release(Q);
}

void print_path(struct Vertex *Adj, char *c, int start, int dest, int limit){
    if(start < 0 || start >= limit || dest < 0 || dest >= limit){
        printf("Wrong Input, Vertexes range from 0 to %d\n", limit-1);
        exit(1);
    }

    if(Adj[start].vertex == Adj[dest].vertex)
        printf("%c ", c[start]);
    elseif(Adj[dest]->parent == INT_MAX)
        printf("no path from %c to %c exits\n", c[start], c[dest]);
    else
        print_path(Adj, start, Adj[dest]->parent);
        printf("%c ", c[dest]);
}

int main(){
    struct Vertex *Adjlist;
    int vertex_vector[20] = {0, 1, 1, 2, 2, 3, 3, 4, 3, 5, 4, 5, 5, 6, 4, 6, 4, 7, 6, 7};
    char cver[8] = {'v', 'r', 's', 'w', 'x', 't', 'u', 'y'};
    int nvertex = 8;

    Adjlist = Adjlist_create(nvertex,vertex_vector);
    BFS(Adjlist,2,8);
    print_path(Adjlist, cver, 2, 7, 8);
    printf("\n");
    Adjlist_release(Adjlist, nvertex);
    return 0;
}
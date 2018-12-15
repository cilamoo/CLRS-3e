/*Depth-first search pseudocode
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
#include "dfs.h"


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

struct Graph* tg_graph_init(struct Graph *G){  /* the transpose of G*/
    struct Graph *TG;
    unsigned int i;
    TG = graph_init((size_t)G->vercount, (size_t)G->edgecount);
    for(i = 0; i < G->vercount; i++){
        TG->Adj[i].f = G->Adj[i].f; /* the transpose of G stores finishing times computed first DFS call*/
    }
    return TG;
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
        j = ev[2*i];
        k = ev[2*i+1];
        bm->next = Adj[j].head;
        Adj[j].head = bm;
        bm->self = &Adj[k];
        bm++;     /*get memory from block memory previously allocated, pointer to next listnode */
        Adj[j].nodenum++;
    }
}

void DFS_VISIT(struct Graph *G, struct vertex *u){
    int i,num;
    time += 1;
    printf("vertex %d is discovered, time is %d, parent is %d \n", u->vernum, time, u->parent);
    struct listnode *head;
    u->d = time;
    u->color = 1<<11;     /* GRAY */
    num = u->nodenum;
    head = u->head;
    while(num--){ /* or (head--) != NULL */
        if((head->self->color >> 10) & 1){ /*this vertex has just been discovered */
            head->self->parent = u->vernum;
            DFS_VISIT(G,head->self);
        }

       if(num != 0){ 
          head = head->next;
       } /* pointer to next listnode */ 
    }
    time += 1;
    u->f = time;
    u->color = 1 << 12;    /* BLACK */
    printf("vertex %d is finished,time is %d, parent is %d\n", u->vernum, time, u->parent );
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

void sccDFS_VISIT(struct Graph *G, struct SCC *SCC, struct vertex *u){
    int i,num;
    time += 1;
    printf("vertex %d is discovered, time is %d, parent is %d \n", u->vernum, time, u->parent);
    struct listnode *head;

    SCC->scca[SCC->index++] = u->vernum ; /*discovery a vertex of SCC*/
    SCC->vercount++;                 /* vertex count, SCC->vercount == SCC->index */
    
    u->d = time;
    u->color = 1<<11;     /* GRAY */
    num = u->nodenum;
    head = u->head;
    while(num--){ /* or (head--) != NULL */
        if((head->self->color >> 10) & 1){ /*this vertex has just been discovered */
            head->self->parent = u->vernum;
            sccDFS_VISIT(G,SCC,head->self);
        }

       if(num != 0){ 
          head = head->next;
       } /* pointer to next listnode */ 
    }
    time += 1;
    u->f = time;
    u->color = 1 << 12;    /* BLACK */
    printf("vertex %d is finished,time is %d, parent is %d\n", u->vernum, time, u->parent );
}

/*Alarm: make sure each vertex in TG belongs to one SCC, otherwise programm must be coded by 
the definition of SCC. That is, function sccDFS can be applied just for Figure 22.9. */
struct SCClist* sccDFS(struct Graph *TG, struct vertex **vertex){
    int i;
    struct SCClist *SCClist;
    struct SCC *SCC;
    struct vertex *u;
    
    time = 0;       /* reset time */
    if((SCClist = malloc(sizeof(*SCClist))) == NULL)
        return NULL;
    SCClist->head = NULL;

    i = TG->vercount;
    while(i--){
       u = &TG->Adj[vertex[i]->vernum];
        if((u->color>>10) & 1){
            if((SCC = malloc(sizeof(*SCC))) == NULL){ /* Alarm */ 
               return NULL;
            }

            SCC->next = SCClist->head;
            SCClist->head = SCC;
            SCC->vercount = 0;
            SCC->index = 0;
           {int i;
            for(i = 0;i < 8;i++){
               SCC->scca[i] = -1;
            }
           }
            SCClist->scccount++;
           sccDFS_VISIT(TG,SCC,u);
        }

    }
    return SCClist;
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

void print_graph(struct Graph *G){
      int i,j;
      struct vertex *v = G->Adj;
      struct listnode *head;
      for(i = 0; i < G->vercount; i++){
          head = v[i].head;
          printf("vertex %d has %d edge(s):",v[i].vernum,v[i].nodenum);
          for(j = 0;j < v[i].nodenum; j++){
                printf("%d ", head->self->vernum);
                head = head->next;
            }
            printf("\n");
        }
 }

void print_paren_structure(struct Graph *G){
    int i;
    struct vertex *Adj = G->Adj;
    printf("parenthesis structure:\n");
    for(i = 0; i < G->vercount; i++){
          printf("vertex %d  (d,f)->(%d,%d)\n", Adj[i].vernum, Adj[i].d, Adj[i].f);
    }
}

void print_SCC(struct SCClist *SCClist, char *vermap){
    unsigned int order = 1;
    struct SCC *head = SCClist->head;
    printf("STRONGLY CONNECTED COMPONENTS: \n");
    while(head != NULL){
        printf(" The %dth SCC: ", order++);
        int idx;
        for(idx = 0; idx < head->vercount; idx ++){
            printf(" %c ", vermap[ (head->scca[idx]) ]);
        }
        printf("\n");
        head = head->next;
    }
   printf("\n");
}

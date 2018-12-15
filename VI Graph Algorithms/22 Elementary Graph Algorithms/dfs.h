/*Depth-first search */

#ifndef DFS_H
#define DFS_H

#include <stdio.h>

struct listnode{
    struct vertex *self;
    struct listnode *next;
};

struct vertex {
    int vernum;     /*vernum denotes character vertex */
    unsigned int color;
    unsigned int parent;    /*atrribute u.π */
    int d;
    int f;
    unsigned int nodenum;     /*number of listnodes this vertex has, or edges from this vertex to other */
    struct listnode *head;    /*pointer first listnode in list */
};

struct Graph {
    unsigned int vercount;     /*  number of vertex */
    unsigned int edgecount;    /*number of edge */
    struct listnode *blockmemory;    /* block memory for all listnodes */
    struct vertex *Adj;     /* pointer to adjacency-list */
};

/* Strongly connected components struct */
struct SCC{
    int scca[8];                  /* an array storing vertex */
    struct SCC *next;     
    unsigned int vercount;     /* the number of vertexes */
    unsigned int index;
};

struct SCClist{
    struct SCC *head;
    unsigned int scccount;
};

/* SCC Graph */
struct GraphSCC{
    struct SCC *scc;         /* pointer to a SCC struct */
    unsigned int sccnum;     /*the number of Strongly connected components */
};

struct vertex* vertex_init(size_t vnum);

struct Graph* graph_init(size_t vernum, size_t edgenum);

void graph_release(struct Graph *G);

void add_edges(struct Graph *G, int *ev);

struct Graph* tg_graph_init(struct Graph *G);

void DFS_VISIT(struct Graph *G, struct vertex *u);

void DFS(struct Graph *G);

struct SCClist* sccDFS(struct Graph *TG, struct vertex **vertex);

void print_SCC(struct SCClist *SCClist, char *vermap);

void sccDFS_VISIT(struct Graph *G, struct SCC *SCC, struct vertex *u);

void print_path(struct vertex *Adj, char *c, int start, int dest);

void print_graph(struct Graph *G);

void print_paren_structure(struct Graph *G);

#endif

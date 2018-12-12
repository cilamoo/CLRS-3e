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


struct vertex* vertex_init(size_t vnum);

struct Graph* graph_init(size_t vernum, size_t edgenum);

void graph_release(struct Graph *G);

void add_edges(struct Graph *G, int *ev);

void DFS_VISIT(struct Graph *G, struct vertex *u);

void DFS(struct Graph *G);

void print_path(struct vertex *Adj, char *c, int start, int dest);

void print_graph(struct Graph *G);

void print_paren_structure(struct Graph *G);

#endif

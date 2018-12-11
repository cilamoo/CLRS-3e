/*Depth-first search */

#include <stdio.h>

struct listnode;

struct vertex;

struct Graph;

struct vertex* vertex_init(size_t vnum);

struct Graph* graph_init(size_t vernum, size_t edgenum);

void graph_release(struct Graph *G);

void add_edges(struct Graph *G, int *ev);

void DFS_VISIT(struct Graph *G, struct vertex *u);

void DFS(struct Graph *G);

void print_path(struct vertex *Adj, char *c, int start, int dest);



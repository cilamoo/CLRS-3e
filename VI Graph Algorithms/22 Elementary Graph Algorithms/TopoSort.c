/* Topological sort for figure 22.7 on page 613.*/

#include "dfs.h"
#include <stdlib.h>
#include "quicksort.h"

/*linked list, store sorted vertexes by atrribute f */
struct list{
    struct listnode *head;
};

void list_insert(struct list *L, struct listnode *v){
    v->next = L->head;
    L->head = v;
}

/* output topological sort */
void print_toposort(struct list *L, char **input){
    struct listnode *head;
    head = L->head;
    printf("Topological Sort: ");
    while(head != NULL){
        printf("[%s %d]->", input[head->self->vernum], head->self->f);
        head = head->next;
    }
    printf("Finished\n");
}

/*Inputs from figure 22.7
char *vertexes[9] = {"shirt", "tie", "jacket", "belt", "pants", "shoes","socks","undershorts","watch" };
int map[9] = {0,1,2,3,4,5,6,7,8};
int edge_vector[20] = {0,1,1,2,0,3,3,2,4,3,4,5,6,5,7,5,7,4,8,8};
*/

/*Maybe need randomization technique for graph search , or after being searched, quicksort should excute randomly*/
int main(){
    int i; 
    struct list *list;
    struct listnode *block, *freeptr;
    struct vertex* A[9];
    struct Graph *G; 
    char* vertexes[9] = {"shirt", "tie", "jacket", "belt", "pants", "shoes","socks","undershorts","watch" };;
    int edge_vector[20] = { 0,1, 0,3, 1,2, 3,2, 4,3, 4,5, 6,5, 7,5, 7,4,   8,8};
    if((list = malloc(sizeof(*list))) == NULL){
        printf("malloc call failed when allocated memory for list \n");
        return -1;    
    }
    
    if(( block = malloc(9*sizeof(*block))) == NULL){
        printf("malloc call failed when allocated memory for listnode \n");
        return -1;
    }

    freeptr = block;
    list->head = NULL;


    if((G = graph_init(9,10)) == NULL){
        printf("malloc call failed in function graph_init\n");
        return -1;
    }

    add_edges(G, edge_vector);
   
    print_graph(G);   
    DFS(G);
    print_paren_structure(G);
    
    for(i = 0; i < 9; i++)
    {
        A[i] = &G->Adj[i];
    }
    
    quicksort(&A[0],0,8);
    
    for(i = 0; i < 9; i++){
        struct listnode *tmp = block++; /* get memory address from block memory */
        tmp->next = NULL;
        tmp->self = A[i];
        list_insert(list, tmp);
    }

    print_toposort(list, vertexes);
    free(freeptr);
    free(list);
    graph_release(G);
    
    return 0;
}


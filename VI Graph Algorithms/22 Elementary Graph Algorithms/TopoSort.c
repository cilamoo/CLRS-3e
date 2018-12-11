/* Topological sort for figure 22.7 on page 613.*/
#include "dfs.h"

/* quicksort algorithm, sorts graph vertexes after been discovered by atrribute f */
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
    for(j = p; p < r; p++){
        if(A[j]->f < x){
            i = i + 1;
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
    struct list *head;
    head = L->head;
    while(head != NULL){
        printf("[%s %d]->", input[head->self->vernum], head->self->f,);
        head = head->next;
    }
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
    int edge_vector[20] = {0,1,1,2,0,3,3,2,4,3,4,5,6,5,7,5,7,4,8,8};
    char* vertexes[9] = {"shirt", "tie", "jacket", "belt", "pants", "shoes","socks","undershorts","watch" };;
    
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

    DFS(G);
    
    for(i = 0; i < 9; i++)
    {
        A[i] = &G->Adj[i];
    }

    qucksort(&A,0,8);
    
    for(i = 0; i < 9; i++){
        struct listnode *tmp = block++; /* get memory address from block memory */
        tmp->next = NULL;
        tmp->self = A[i];
        list_insert(list, tmp);
    }

    print_toposort(L, vertexes);
    free(freeptr);
    free(list);
    graph_release(G);

    return 0;
}


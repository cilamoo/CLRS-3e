/*SCC — Strongly connected components*/

#include "dfs.h"
#include "quicksort.h"
#include <stdlib.h>

/*Input from figure 22.9 on page 616:
char vertexes[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
int edge_vector[14] = {0,1, 1,2, 2,3, 3,2, 4,5, 5,6, 6,5, 6,7, 7,7, 4,0, 1,4, 1,5, 2,6, 3,7};
int ver_map[8] = {0,1,2,3,4,5,6,7};
*/

int main(){
    char vertexes[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int edge_vector[28] = {0,1, 1,2, 2,3, 3,2, 4,5, 5,6, 6,5, 6,7, 7,7, 4,0, 1,4, 1,5, 2,6, 3,7};
    int reverse_edge_vector[28];
    struct Graph *G, *TG;
    struct SCClist *SCClist;
    struct vertex* A[9];       /*an array storing pointer to vertex u by finishing times u.f */

    {/* reverse each edge*/
     int j;
    for(j = 0; j < 14; j++){
        reverse_edge_vector[2*j] = edge_vector[2*j+1];
        reverse_edge_vector[2*j+1] = edge_vector[2*j];        
    }
    }

    G = graph_init(8,14);
    add_edges(G, edge_vector);
    printf("==== 1st DFS ==== \n");
    DFS(G);                  /* compute finishing times u.f for each vertex u */

    {/*use quicksort to sort vertex by finishing times */
    int j;
    for(j = 0; j < 8; j++){
        A[j] = &G->Adj[j];
    }
    
    quicksort(&A[0], 0, 7);
    }

    TG = tg_graph_init(G);                   /* the transpose of G*/
    add_edges(TG, reverse_edge_vector);      /*add reverse edges */
    printf("===== 2nd DFS ====\n");
    SCClist = sccDFS(TG, &A[0]);                      /* consider the vertices in order of decreasing u.f */
    if(SCClist == NULL){
       printf("sccDFS failed\n");
       return -1;
   }
   
   print_SCC(SCClist, vertexes);
   {    
    struct SCC *next;
    struct SCC *head = SCClist->head;
    while(head != NULL){
        next = head->next;
        free(head);
        head = next;
    }
    free(SCClist);
   }
    
    graph_release(G);
    graph_release(TG);
    return 0;
}

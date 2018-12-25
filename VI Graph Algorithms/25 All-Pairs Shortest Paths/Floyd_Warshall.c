/* FLOYD-WARSHALL(W) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int dim;      /*matrix dimension*/
#define INFT 9999
#define  NIL  -128

int min_weight(int x, int y){
    return (x < y)? x : y;
}

void result* Floyd_Warshall(int *W,int *P, struct result *r){
    int i,j,k,x,y;
    struct result *r;
    int *next_matrix, *next_path;
    int *prev_matrix = W;      /* have less intermediate vertex, that is , k is small */
    int *prev_path = P;

    for(k = 0; k < N; k++){
        next_matrix = prev_matrix + N*N;
        next_path = prev_path + N*N;

        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                x = prev_matrix[i*N+j];
                y = prev_matrix[i*N+k] + prev_matrix[k*N+j]
                next_matrix[i*N+j] = min(x, y);
                
                if( x <= y){
                    next_path[i*N+j] = prev_path[i*N+j];
                }
                else{
                    next_path[i*N+j] = prev_path[k*N+j];
                }
            }
        }
        prev_matrix = next_matrix;
        prev_path = next_path;
    }
    r->sp = next_matrix;
    r->pp = prev_matrix;
}

struct result{
        int *sp;    /*pointer to shortest path matrix */
        int *pp;     /* pointer to predecessor matrix */
};

void print_result(struct reulst *pr){
    int i,j;
    int *sp;
    int *pp;

    sp = pr->sp;
    pp = pr->sp;

    printf("Matrix Output:\n");
    for(i = 0; i < N; i++){
        for(j=0; j < N;j++){
         printf("%2d ",sp[i*N+j]);
    }
     printf("\n");
    }

     printf("Path Matrx Output:\n");
    for(i = 0; i < N; i++){
        for(j=0; j < N;j++){
         printf("%2d ",pp[i*N+j]);
    }
     printf("\n");
    }
}

int main(){
    int *W,*r,*P;
    struct result r;
    
    r->sp = NULL;
    r->pp = NULL;

    int input[25] = {0,3,8,INFT,-4, INFT,0,INFT,1,7, INFT,4,0,INFT,INFT,\
             2,INFT,-5,0,INFT, INFT,INFT,INFT,6,0};               /* Graph, Input Matrix*/
    int parent[25] = {NIL,1,1,NIL,1, NIL,NIL,NIL,2,2, NIL,3,NIL,NIL,NIL,\
                       4,NIL,4,NIL,NIL, NIL,NIL,NIL,5,NIL};
    N = 5;
    
    int size = (N+1)*N*N*sizeof(int);
    if((W = malloc((size_t)size)) == NULL)
    {
        printf("W's memory alloc failed\n");
        exit(1);
    }

    if((P = malloc((size_t)size)) == NULL)    /* predecessor matrix */
    {
        printf("P's memory alloc failed\n");
        return NULL;
    }

    memcpy(W,input,(size_t)N*N*sizeof(int));
    memcpy(P,parent,(size_t)N*N*sizeof(int));

    Floyd_Warshall(W,P,&r);
    print_result(&r);

    free(W);
    free(P);

    return 0;
}
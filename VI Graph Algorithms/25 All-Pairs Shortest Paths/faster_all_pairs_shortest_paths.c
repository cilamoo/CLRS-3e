/* FASTER-ALL-PAIRS-SHORTEST-PATHS(W)
  gcc -lm <file.c>  */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int N;
#define INFT 9999

/* pre alloc memory for all matrixes */
int* matrix_prealloc(int n){
    int products_num = ceil(log10(n-1)/log10(2)); /* number of matrix products */
    int  num = products_num + 1;        /* have num matrixes */
    int *pmatrix;
    if((pmatrix = calloc((size_t)num, (size_t)(n*n*sizeof(int)))) == NULL)
        return NULL;
    return pmatrix;
}

int min_weight(int x, int y){
    return (x < y)? x : y;
}

int* extend_shortest_paths(int *L){
    int i,j,k,idx;
    int *eL = L + N*N;    /* extend to next matrix */
    
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
        idx = i*N+j;
        eL[idx] = INFT;
        for(k = 0; k < N; k++){
            eL[idx] = min_weight(eL[idx],L[i*N+k] + L[k*N+j]);
        }
        }
    }
    
    return eL;
}

int* faster_all_pairs_shortest_paths(int *W){
    int m = 1;
    int *R = W ;      /* result */
    
    while(m < N-1){
        R = extend_shortest_paths(R);
        m *= 2;
    }
    return R;
}

void print_result(int *r){
    int i,j;
    printf("Matrix Output:\n");
    for(i = 0; i < N; i++){
        for(j=0; j < N;j++){
         printf("%2d ",r[i*N+j]);
     }
     printf("\n");
    }
}

int main(){
    int *W, *free_pointer, *result;
    int i,j;

    N = 5;
    if((W = matrix_prealloc(N)) == NULL){
        printf("matrix_prealloc call failed"); 
        exit(1);
    }

    free_pointer = W;

    int input[25] = {0,3,8,INFT,-4, INFT,0,INFT,1,7, INFT,4,0,INFT,INFT,\
             2,INFT,-5,0,INFT, INFT,INFT,INFT,6,0};               /* Graph, Input Matrix*/
    memcpy(W,input,sizeof(input)); 
    result = faster_all_pairs_shortest_paths(W);
    print_result(result);

    free(free_pointer);
}

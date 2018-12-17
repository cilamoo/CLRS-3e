/* quicksort algorithm, sorts graph vertexes by atrribute f */
#include "quicksort.h"
#include "dfs.h"

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
    for(j = p; j < r; j++){
        if(A[j]->f <= x){
            i += 1;
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

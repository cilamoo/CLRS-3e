#include <stdio.h> 

void swap(int *s1, int *s2){
    int tmp;
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

int partition(int *A, int p, int r){
    int x, i, j;
    x = A[r];
    i = p - 1;
    for(j = p; j < r; j++){
        if(A[j] < x){
            i += 1;
            swap(&A[i],&A[j]);
        }
    }
    swap(&A[i+1], &A[r)；
    return i + 1;
    
}

void quicksort(int *A, int p, int r){
    int q;
    if(p < r){
        q = partition(A,p,r);
        quicksort(A,p,q-1);
        quicksort(A,q+1,r);
    }
}

int main(){
    int i;
    int A[12] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    quicksort(A,0,11);
    i = 12;
    while(i--){
        printf("%d ", A[i]);
    }
    printf("\n")
    return 0;
}
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

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
    swap(&A[i+1], &A[r]);
    return i + 1;
    
}
int randomized_partition(int *A, int p, int r){
    int i = -1;
     while(i < p){
          i = rand()%(r + 1);
    }
    printf("random index is %d\n", i);
    swap(&A[i],&A[r]);
    return  partition(A,p,r);
}

void randomized_quicksort(int *A, int p, int r){
    int q;
    if(p < r){
        q = randomized_partition(A,p,r);
        randomized_quicksort(A,p,q-1);
        randomized_quicksort(A,q+1,r);
    }
}

int main(){
    int i;
    int A[12] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    
    srand((int)time(0));

    printf("Input: ");
    for(i = 0; i < 12; i++){
        printf("%d ", A[i]);
    }
    randomized_quicksort(A,0,11);
    printf(" Output: ");
    for(i = 0; i < 12; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}

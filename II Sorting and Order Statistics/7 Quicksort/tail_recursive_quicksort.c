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
    swap(&A[i+1], &A[r]);
    return i + 1;
    
}

//并没有尾递归
void tail_recursive_quicksort(int *A, int p, int r){
    int q;
    while(p < r){
        q = partition(A,p,r);
        tail_recursive_quicksort(A,p,q-1);
        p = q + 1;
    }
}

int main(){
    int i;
    int A[12] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    printf("Input: ");
    for(i = 0; i < 12; i++){
        printf("%d ", A[i]);
    }
    tail_recursive_quicksort(A,0,11);
    printf(" Output: ");
    for(i = 0; i < 12; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}

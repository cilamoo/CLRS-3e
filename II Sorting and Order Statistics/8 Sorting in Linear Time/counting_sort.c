#include <stdio.h>

void counting_sort(int *A, int *B, int n, int k){
    int C[k+1];
    int i,j;
    
    for(i = 0; i <= k; i++){
        C[i] = 0;
    }

    for(i = 0; i < n; i++){
        C[A[i]] += 1;
    }

    for(i = 1; i <= k; i++){
        C[i] += C[i-1];
    }

    for(j = n-1; j >= 0; j--){
        B[C[A[j]]-1] = A[j];
        C[A[j]] -= 1;
    }

}

int main(){
    int i;
    int B[8];
    int A[8] = {2,5,3,0,2,3,0,3};
    int k = 5;
    int n = 8;
    
    counting_sort(A,B,n,k);
    for(i = 0; i < n; i++)
        printf("%d ", B[i]);
    
    return 0;
}

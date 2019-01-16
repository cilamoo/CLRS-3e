#include <stdio.h>

void merge(int *A, int p, int q, int r){
    int n1,n2,i,j,k;
    n1 = q - p + 1;
    n2 = r - q;

    int L[n1+1],R[n2+1];
    
    for(i = 0; i < n1; i++){
        L[i] = A[p-1+i];
    }

    for(j = 0; j < n2; j++){
        R[j] = A[q+j];
    }
    
    L[n1] = 999;
    R[n2] = 999;

    i = 1;
    j = 1;
    for(k = p; k <= r; k++){
        if(L[i-1] <= R[j-1]){
            A[k-1] = L[i-1];
            i += 1;
        }
        else{
            A[k-1] = R[j-1];
            j += 1;
        }
    }
}

void merge_sort(int *A, int p, int r){
    int q;
    if(p < r){
        q = (p+r)/2;
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
}

void print_array(int *A, int num){
    int i;
    for(i = 0; i < num; i++){
        printf("%d ", A[i]);
    }
}

int main(){
    int A[8] = {5,2,4,7,1,3,2,6};
    int length = 8;
    printf("Before sorting:\n");
    print_array(A,length);

    merge_sort(A,1,length);

    printf("\nAfter sorting:\n");
    print_array(A,length);
    printf("\n");
    return 0;
}

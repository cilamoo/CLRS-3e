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
    printf("radom index is %d\n", i);
    swap(&A[i],&A[r]);
    return  partition(A,p,r);
}

int randomized_select(int *A, int p, int r, int i){
    int k,q;
    if(p == r)
        return A[p];
    
    q = randomized_partition(A,p,r);
    k = q - p + 1;
    if(k == i)
        return A[k-1];
    else if(i < k)
        return randomized_select(A,p,q-1,i);
    else
        return randomized_select(A,p,q+1,k-i);
}


int main(){
    int r;
    int i = 5;
    int A[8] = {4,6,3,8,2,7,1,5};
    srand((int)time(0));
    r = randomized_select(A,0,7,i);
    printf("the %dth smallest number is %d\n", i, r);
    return 0;
}
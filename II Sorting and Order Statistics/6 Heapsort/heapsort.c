/*heapsort*/
#include <stdio.h>

int PARENT(int i){
    return i>>1;
} 

int LEFT(int i){
    return i<<1;
}

int RIGHT(int i){
    return (i<<1)+1;
}

void swap(int *A, int largest, int i){
    int tmp;
    tmp = A[i-1];
    A[i-1] = A[largest-1];
    A[largest-1] = tmp;
}

void max_heapify(int *A, int i, int heap_size){
    int l, r, largest;
    l = LEFT(i);
    r = RIGHT(i);
    if(l <= heap_size && A[l-1] > A[i-1])
        largest = l;
    else
        largest = i;
    
    if(r <= heap_size && A[r-1] > A[largest-1])
        largest = r;
    
    if(largest != i){
        swap(A,largest,i);
        max_heapify(A,largest,heap_size);
    }
}

void min_heapify(int *A, int i, int heap_size){
    int l, r, smallest;
    l = LEFT(i);
    r = RIGHT(i);

    if(l <= heap_size && A[l-1] < A[i-1])
        smallest = l;
    else
        smallest = i;
    
    if(r <= heap_size && A[r-1] < A[smallest-1])
        smallest = r;

    if(smallest != i){
        swap(A,smallest,i);
        min_heapify(A,smallest,heap_size);
    }
}

void build_max_heap(int *A, int length){
    int heap_size, i;
    heap_size = length;
    //the elements in the subarray A[(⌊n/2⌋+1)...n] are all leaves of the tree.
    for(i=length/2; i > 0; i--){
        max_heapify(A,i,heap_size);
    }
}

void build_min_heap(int *A, int length){
    int heap_size, i;
    heap_size = length;
    
    for(i=length/2; i > 0; i--){
        min_heapify(A,i,heap_size);
    }
}

void max_heapsort(int *A, int length){
    int heap_size,i;
    build_max_heap(A, length);
    heap_size =  length;
    for(i=length; i > 1; i--){
        swap(A,i,1);
        heap_size -= 1;
        max_heapify(A,1,heap_size);
    }
}

void min_heapsort(int *A, int length){
    int heap_size,i;
    build_min_heap(A, length);
    heap_size =  length;
    for(i=length; i > 1; i--){
        swap(A,i,1);
        heap_size -= 1;
        min_heapify(A,1,heap_size);
    }
}

int main(){
    int i;
    int A[10] = {4 ,1, 3, 2, 16, 9, 10, 14, 8, 7};
    int A2[10] = {4 ,1, 3, 2, 16, 9, 10, 14, 8, 7};
    max_heapsort(A,10);
    min_heapsort(A2,10);
    printf("MAX-HEAP: ");
    for(i = 0; i < 10; i++){
        printf("%d ", A[i]);
    }
    
    printf("\nMIN-HEAP: ");
    for(i = 0; i < 10; i++){
        printf("%d ", A2[i]);
    }
    printf("\n");    
    return 0;
}

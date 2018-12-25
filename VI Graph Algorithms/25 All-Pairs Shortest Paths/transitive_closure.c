/* TRANSITIVE-CLOSURE(G),
TODO：implement table search to determine  whether an edge belongs to Graph G*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int N;

int* transitive_closure(int *T){
    int i,j,k,x,y,z;
    int *T_next;
    int *T_prev = T;

    for(k = 0; k < N; k++){
        T_next = T_prev + N*N;
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                x = T_prev[i*N+j];
                y = T_prev[i*N+k];
                z = T_prev[k*N+j];
                
                T_next[i*N+j] = x || (y && z);
            }
        }
        T_prev = T_next;
    }

    return T_next;
}

void print_result(int *r){
    int i,j;
    printf("Output Transitive Closure\n");
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            printf("%2d ",r[i*N+j]);
        }
        printf("\n");
    }
}

int main(){
    int *T,*r;
    int size;
    N = 4;

    int input[16] = {1,0,0,0, 0,1,1,1, 0,1,1,0, 1,0,1,1}; /*can use char input[16] to\
                        substitute int input[16],however, the best method is a 16-bit number*/
    size = (N+1)*N*N;
    if((T = malloc((size_t)size*sizeof(int))) == NULL){
        printf("malloc failed\n");
        exit(1);
    }
    memcpy(T,input,sizeof(input));
    r = transitive_closure(T);
    print_result(r);
    free(T);
    return 0;
}


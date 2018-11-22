/**
 * An iterative greedy algorithm
 * 
 * It is usually a straightforward task to transform a tail-recursive procedure
 * to an iterative form; in fact, some compilers for certain programming languages
 * perform this task automatically.
 * 
 * GREEDY-ACTIVITY-SELECTOR(s,f)
 * 1 n = s.length 
 * 2 A = {a1}
 * 3 k = 1 
 * 4 for m = 2 to n
 * 5     if s[m] ≥ f[k]
 * 6         A = A U {am}
 * 7         k = m 
 * 8 return A 
 * 
 * Running time is Θ(n), assuming that the activities were already sorted initially by 
 * their finish times.
*/

#include <stdio.h> 

int* greedy_activity_selector(int *,int *);
void print_result_set(int *,int *, int *);
int set[11] = {0,0,0,0,0,0,0,0,0,0,0};

int main(){
    int *pset;
    int s[11] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int f[11] = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    pset = greedy_activity_selector(s,f);
    print_result_set(pset, s, f);
    return 0;
}

int* greedy_activity_selector(int *s, int *f){
    static int index = 0;
    int k, n, m;
    k = 1;
    n = 11;
    set[index++] = 1;
    for(m = 2; m <= n; m++){
        if(s[m-1] >= f[k-1]){
            set[index++] = m;
            k = m;
        }
    }
    return set;
}

void print_result_set(int *pset, int *ps, int *pf){
    int i;
    printf("Activity set is:\n");
    for(i = 0; i < 11; i++){
        if(pset[i] !=0 ){
           int idx = pset[i];
           printf("a%d start:%d, finish:%d\n",idx, ps[idx-1], pf[idx-1]);
        }
    }
}

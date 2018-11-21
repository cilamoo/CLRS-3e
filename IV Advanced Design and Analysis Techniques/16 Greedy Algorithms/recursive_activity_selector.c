/**
 * A greedy algorithm always makes the choice that looks best at the moment. 
 * That is, it makes a locally optimal choice in the hope that this choice 
 * will lead to a globally optimal solution. 
 * 
 * Greedy algorithms do not always yield optimal solutions, but for many problems 
 * they do. 
 * 
 * assume that the n input activities are already ordered by monotonically 
 * increasing finish time, according to equation (16.1). If not, we can sort
 * them into this order in O(nlgn) time, breaking ties arbitrarily. In order 
 * to start, we add the fictitious activity a0 with f0 = 0, so that subproblem
 *  S0 is the entire set of activities S. The initial call, which solves the entire
 *  problem, is RECURSIVE-ACTIVITY-SELECTOR(s,f,0,n)
 * 
 * input:
 *      i 1 2 3 4 5 6 7 8  9 10 11
 *    si 1 3 0 5 3 5 6  8  8  2 12
 *    fi 4 5 6 7 9 9 10 11 12 14 16
 * 
 * RECURSIVE-ACTIVITY-SELECTOR(s,f,k,n)
 * 1 m = k + 1 
 * 2 while m ≤ n and s[m] < f[k]
 * 3     m = m + 1 
 * 4 if m ≤ n 
 * 5     return {am} + RECURSIVE-ACTIVITY-SELECTOR(s,f,m,n)
 * 6 else return Ø
 * 
 * RECURSIVE-ACTIVITY-SELECTOR(s,f,0,n) is Θ(n)
*/

#include <stdio.h>
 
 int recursive_activity_selector(int *, int *, int , int);
 void print_result_set(int *,int *, int *);
 int set[11] = {0,0,0,0,0,0,0,0,0,0,0};

 int main(){
    int i;
    int s[11] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int f[12] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    recursive_activity_selector(s, f, 0, 11);
    print_result_set(set, s, f);
    return 0;
 }

 int recursive_activity_selector(int *s, int *f, int k, int n){
    int m;
    static int index = 0;
    
    m = k + 1;
    while(m <= n && s[m-1] < f[k])
        m = m + 1;
    
    if(m <= n){
        set[index++] = m;
        return recursive_activity_selector(s, f, m, n);
    }
    else{
        return 0;
    }
 }

 void print_result_set(int *pset, int *ps, int *pf){
     int i;
     printf("Activity set is:\n");
     for(i = 0; i < 11; i++){
        if(pset[i] !=0 ){
           int idx = pset[i];
           printf("a%d start:%d, finish:%d\n",idx, ps[idx-1], pf[idx]);
        }
     }
 }

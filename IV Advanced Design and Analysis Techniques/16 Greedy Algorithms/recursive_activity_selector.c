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
 * /
 
 int* recursive_activity_selector(int *, int *, int , int);
 void print_result_set(int *,int *, int *);

 int main(){
    int i;
    int s[11] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int f[12] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    int *pset;
    pset = recursive_activity_selector(s, f, 0, 11);
    print_result_set(pset, s, f);
    return 0;
 }

 int* recursive_activity_selector(int *ps, int *pf, int k, int n){
    int i,m;
    static int set[11];
    static int index = 0;
    for(i = 0; i < 11; i++)
        set[i] = 0;
    
    m = k + 1;
    while(m <= n && s[m-1] < f[k])
        m = m + 1;
    
    if(m <= n){
        set[index++] = m;
        return recursive_activity_selector(ps, pf, m, n);
    }
    else{
        return 0;
    }
    
    return &set;
 }

 void print_result_set(int *pset, int *ps; int *pf){
     int i;
     printf("activity set is:\n");
     for(i = 0; i <= 11; i++){
        if(pset[i] !=0 ){
            printf("A%d start %d finish %d\n",pset[i],ps[m-1],pf[m]);
        }
     }
 }

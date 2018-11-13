/**
 * 1.length i | 1 2 3 4 5 6 7 8 9 10
 *  price pi  |1 5 8 9 10 17 17 20 24 30
 * 
 * 2.optimal substructure: optimal solutions to a problem incorporate optimal solutions to related subproblems
 * 
 * 3.Using dynamic programming for optimal rod cutting
 *    1.time-memory trade-off:uses additional memory to save computation time
 *    2.A dynamic-programming approach runs in polynomial time when the number of distinct subproblems
 *      involved is polynomial in the input size and we can solve each such subproblem in polynomial time.
 * 
 * 4.top-down with memoization
 *    1.save the result of each subproblem (usually in an array or hash table).
 *    2.pseudocode:
 *         CUT-ROD(p,n)——Recursive top-down implementation
 *         1 if n == 0 
 *         2     return 0
 *         3 q = -∞ 
 *         4 for i = 1 to n 
 *         5     q = max(q,p[i] + CUT-ROD(p,n - i))
 *         6 return q 
 *          
 *         MEMOIZED-CUT-ROD(p,n)
 *         1 let r[0..n] be a new array
 *         2 for i = 0 to n
 *         3     r[i] = -∞ 
 *         4 return MEMOIZED-CUT-ROD-AUX(p,n,r)
 *         
 *         MEMOIZED-CUT-ROD-AUX(p,n,r)
 *         1 if r[n] ≥ 0 
 *         2     return r[n]
 *         3 if n == 0
 *         4    q == 0
 *         5 else q = -∞
 *         6     for i = 1 to n 
 *         7         q = max(q,p[i] + MEMOIZED-CUT-ROD-AUX(p,n-i,r))
 *         8 r[n] = q
 *         9 return q 
 *          
 *      3.The procedure MEMOIZED-CUT-ROD-AUX is just the memoized version of our 
 *          previous procedure, CUT-ROD. It first checks in line 1 to see whether the 
 *          desired value is already known and, if it is, then line 2 returns it. Otherwise,
 *          lines 3–7 compute the desired value q in the usual manner, line 8 saves it in r[n], and line 9 returns it.
 * 
 * 5.bottom-up method 
 *    1.sort the subproblems by size and solve them in size order, smallest first
 *    2.pseudocode 
 *          BOTTOM-UP-CUT-ROD(p,n)
 *          1 let r[0..n] be new array
 *          2 r[0] = 0
 *          3 for j = 1 to n 
 *          4     q = -∞
 *          5     for i = 1 to j
 *          6         q = max(q,p[i]+r[j - i])
 *          7     r[j] = q
 *          8 return r[n]
 *    .Runing time of top-down with memoization and bottom-up method :
 *       The bottom-up and top-down versions have the same asymptotic running time. 
 *       The running time of procedure BOTTOM-UP-CUT-ROD is Θ(n^2), due to its doubly-nested loop structure.
 *       BOTTOM-UP-CUT-ROD(p,n)—— The number of iterations of its inner for loop, in lines 5–6, forms an arithmetic series.
 *       MEMOIZED-CUT-ROD —— The total number of iterations of this for loop, over all recursive calls of MEMOIZED-CUT-ROD, 
 *       forms an arithmetic series,
 *       
 * 6.These two approaches yield algorithms with the same asymptotic running time,except in unusual 
 * circumstances where the top-down approach does not actually recurse to examine all possible subproblems. 
 * The bottom-up approach often has much better constant factors, since it has less overhead for procedure calls
 * 
 * 7.Subproblem graphs
 * The size of the subproblem graph G D .V;E/ can help us determine the running time of the dynamic programming algorithm. 
 * Since we solve each subproblem just once, the running time is the sum of the times needed to solve each subproblem.Typically, 
 * the time to compute the solution to a subproblem is proportional to the degree (number of outgoing edges) of the corresponding 
 * vertex in the subproblem graph, and the number of subproblems is equal to the number of vertices in the subproblem graph. 
 * In this common case, the running time of dynamic programming is linear in the number of vertices and edges.
 * 
 * 8.Reconstructing a solution
 *     EXTENDED-BOTTOM-UP-CUT-ROD(p,n)
 *     1 let r[0..n] and s[0..n] be new arrays
 *     2 r[0] = 0 
 *     3 for j = i to n
 *     4     q = -∞
 *     5     for i = 1 to j 
 *     6         if q < p[i] + r[j - i]
 *     7            q = p[i] + r[j - i]
 *     8            s[j] = i 
 *     9     r[j] = q 
 *     10 return r and s 
 *     s[j] in line 8 to hold the optimal size i of the first piece to cut off when solving a subproblem of size j 
 * 
 *     PRINT-CUT-ROD-SOLUTION(p,n)
 *     1 (r,s) = EXTENDED-BOTTOM-UP-CUT-ROD(p,n)
 *     2 while n > 0 
 *     3     print s[n]
 *     4     n = n -s[n]
 * 
*/

#include <limits.h>
#include <stdio.h> 

#define max(a,b) ((a) > (b) ? (a) : (b))

int cut_rod(int *p, int n);
int memoized_cut_rod(int *p, int n);
int memoized_cut_rod_aux(int *p, int n; int *r);
int bottom_up_cut_rod(int *p, int n);

int main(){
    int cost_cut_rod, cost_top_down, cost_bottom_up;
    int price[4] ={1, 5, 8, 9};
    int length = 4;
   
    cost_cut_rod = cut(price,length);
    cost_top_down = memoized_cut_rod(price, length);
    cost_bottom_up = bottom_up_cut_rod(price, length);
    
    printf("solution value of recursive calls: %d\n", cost_cut_rod);
    printf("memoized_cut_rod : %d\n",cost_top_down);
    printf("bottom_up_cut_rod: %d\n",cost_bottom_up);
    print_cut_rod_solution(price, length);
    
    return 0;
}

int cut_rod(int *p, int n){
    int i;
    if (n == 0)
        return 0;
    int q = INT_MIN;
    for( i = 1; i <= n; i++){
        q = max(q,p[i] + cut_rod(p, n-i));
    }
    return q;
}

int memoized_cut_rod(int *p, int n){
    int r[n+1];
    int i;
    for( i = 0;i <= n; i++){
        r[i] = INT_MIN;
    }
    return memoized_cut_rod_aux(p, n, r);
}

int memoized_cut_rod_aux(int *p, int n; int *r){
    int i, q;
    if(r[n] >= 0)
        return r[n];
    if(n == 0)
        q = 0;
    else 
        q = INT_MIN;
        for(i = 1 ; i <= n; i++)
            q = max(q,p[i] + memoized_cut_rod_aux(p,n-i,r);
    r[n] = q;
    return q;
}

int bottom_up_cut_rod(int *p, int n){
    int i, j, q;
    int r[n+1];
    r[0] = 0;
    for(j =1; j <=n; j++){
        q = INT_MIN;
        for(i = 1; i <= j; i++){
            q = max(q, p[i] + r[j - i]);
        }
        r[j] = q;
    }
    return r[n];
}

static int se[n+1];
static int re[n+1];
void extend_bottom_up_cut_rod(int *p, int n){
    int i, j, q;
    re[0] = 0;
    for(j = 1; j <= n; j++){
        q = INT_MIN;
        for(i = 1; i <= j; i++){
            if(q < p[i] + re[ j -i])
                q = p[i] + re[ j -i];
                se[j] = i;
        }
        re[j] = q;
    }
}


void print_cut_rod_solution(int *p, int n){
    extend_bottom_up_cut_rod(p, n);
    while(n > 0)
        printf("The first piece to cut off is %d when solving subproblem of size %d\n", se[n],n);
        n -= se[n];
}


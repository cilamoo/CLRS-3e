/**
 * 1.Memoization
 * Each subsequent time that we encounter this subproblem, we simply look up the
 * value stored in the table and return it.
 * //用散列表作备忘录
 *  Another, more general,approach is to memoize by using hashing with the
 *  subproblem parameters as keys.
 * 
 * MEMOIZED-MATRIX-CHAIN(p)
 * 1 n = p.length - 1
 * 2 let m[1..n, 1..n] be new array
 * 3 for i = 1 to n
 * 4     for j = 1 to n 
 * 5         m[i, j] = ∞
 * 6 return LOOKUP-CHAIN(m,p,1,n)
 * 
 * LOOKUP-CHAIN(m,p,i,j)
 * 1 if m[i,j] < ∞ 
 * 2    return m[i,j]
 * 3 if i == j
 * 4     m[i,j] = 0
 * 5 else for k = i to j - 1 
 * 6        q = LOOKUP-CHAIN(m,p,i,k)
 *               + LOOKUP-CHAIN(m,p,k+1,j)
 * 7            + pi-1 * pk * pj //i-1,k and j are subscripts
 * 8        if q < m[i,j]
 * 9            m[i,j] = q 
 * 10 return m[i,j]
 * //自顶向下：一些子问题没有被解决时，使用该方法
 * //自底向上：解决所有子问题，没有递归压力，
 * In general practice, if all subproblems must be solved at least once, a bottom-up
 * dynamic-programming algorithm usually outperforms the corresponding top-down
 * memoized algorithm by a constant factor, because the bottom-up algorithm has no
 * overhead for recursion and less overhead for maintaining the table. Moreover, for
 * some problems we can exploit the regular pattern of table accesses in the dynamic programming
 * algorithm to reduce time or space requirements even further. Alternatively,
 * if some subproblems in the subproblem space need not be solved at all,
 * the memoized solution has the advantage of solving only those subproblems that
 * are definitely required.
*/

#include <stdio.h>
#include <limits.h>

int memoized_matrix_chain(int *p);
int lookup_chain(int m[6][6], int p[7], int i, int j);

int main(){
    int optvalue;
    int p[7] = {30, 35, 15, 5, 10, 20, 25};
    optvalue = memoized_matrix_chain(p);
    printf("value of optimal solution is %d\n", optvalue);
    return 0;
}

int memoized_matrix_chain(int *p){
    int i, j;
    int n = 6;
    int m[6][6];
    for(i = 0; i<= 5; i++)
        for(j = 0; j <= 5;j++)
            m[i][j] = INT_MAX;
    return lookup_chain(m, p, 1, n);
}

int lookup_chain(int m[6][6], int p[7], int i, int j ){
    if(m[i-1][j-1] < INT_MAX)
        return m[i-1][j-1];
    
    if(i == j)
        m[i-1][j-1] = 0;
    else 
    {
        int k;
        for(k = i;k <= j - 1 ; k++){
            int q;
            q = lookup_chain(m, p, i, k) + lookup_chain(m,p,k+1,j) + p[i-1]*p[k]*p[j];
            if(q < m[i-1][j-1])
                m[i-1][j-1] = q;
        }
    }
    return m[i-1][j-1];
}

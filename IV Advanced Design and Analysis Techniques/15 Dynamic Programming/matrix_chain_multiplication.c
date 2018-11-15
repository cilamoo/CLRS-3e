/**
 * 1. A product of matrices is fully parenthesized if it is either a 
 * single matrix or the product of two fully parenthesized matrix 
 * products, surrounded by parentheses.
 * 
 * 2.MATRIX-MULTIPLY(A,B)
 *   1 if A.columns ≠ B.rows
 *   2     error "incompatible dimensions"
 *   3 else let C be a new A.rows × B.columns matrix
 *   4     for i = 1 to A.rows
 *   5         for j = 1 to B.columns
 *   6             C[i][j] = 0
 *   7             for k = 1 to A.columns
 *   8                C[i][j] = C[i][j] + A[i][k]*B[k][j]
 *   9     return C 
 *   
 * If A is a p×q matrix and B is a q×r matrix, the resulting matrix C 
 * is a p×r matrix. The time to compute C is dominated by the number 
 * of scalar multiplications in line 8, which is pqr.
 * 
 * 3.Applying dynamic programming
 * >>> Step 1: The structure of an optimal parenthesization
 *   For our first step in the dynamic-programming paradigm, we find
 *   the optimal substructure and then use it to construct an optimal 
 *   solution to the problem from optimal solutions to subproblems.
 *  
 * >>>Step 2: A recursive solution
 *             |—— 0                                         if i = j,
 *    m[i,j] = |
 *             |——— min{m[i,k] + m[k+1,j] + p   p  p }       if i < j,
 *                  i≤k<j                    i-1 k  j (these are subscripts)
 *                
 * >>> Step 3: Computing the optimal costs
 *  A recursive algorithm may encounter each subproblem many times in different
 *  branches of its recursion tree. This property of overlapping subproblems is the 
 *  second hallmark of when dynamic programming applies (the first hallmark being 
 *  optimal substructure).
 * 
 *  matrix     A1    A2    A3    A4    A5    A6
 * dimension 30×35 35×15  15×5  5×10 10×20  20×25
 * 
 *  MATRIX-CHAIN-ORDER(p) ———— bottom-up approach
 *  1 n = p.length - 1 
 *  2 let m[1..n, 1..n] and s[1..n-1, 2..n] be new tables
 *  3 for i = 1 to n 
 *  4     m[i,i] = 0 
 *  5 for l = 2 to n 
 *  6     for i = 1 to n - l + 1 
 *  7         j = i + l - 1
 *  8         m[i,j] = ∞
 *  9         for k = i to j - 1 
 *  10            q = m[i,k] + m[k+1,j] +p    p  p   p
 *                                           i-1  k   j (subscript)
 *  11            if q < m[i, j]
 *  12               m[i,j] = q
 *  13               s[i,j] = k 
 *  14 return m and s 
 *  
 * The algorithm first computes m[i,i] = 0 for i = 1，2...,n (the minimum costs
 *  for chains of length 1) in lines 3–4. It then uses recurrence  to compute 
 * m[i,i+1] for i = 1,2,...,n-1 (the minimum costs for chains of length l = 2) 
 * during the first execution of the for loop in lines 5–13. The second time through the
 * loop, it computes m[i,i+2] for i = 1,2,...,n-2 (the minimum costs for chains of 
 * length l = 3), and so forth. At each step, the m[i,j] cost computed in lines 10–13 
 * depends only on table entries m[i,k] and m[k+1,j] already computed.
 * 
 * A simple inspection of the nested loop structure of MATRIX-CHAIN-ORDER 
 * yields a running time of O(n^3) for the algorithm. The loops are nested three deep, 
 * and each loop index (l,i,and k) takes on at most n-1 values. 
 * 
 * The algorithm requires Θ(n^2) space to store the m and s tables.
 * 
 * >>> Step 4: Constructing an optimal solution
 *  PRINT-OPTIMAL-PARENS(s,i,j)
 *  1 if i == j
 *  2     print "A"
 *                 i
 *  3 else print"("
 *  4     PRINT-OPTIMAL-PARENS(s,i,s[i,j])
 *  5     PRINT-OPTIMAL-PARENS(s,s[i,j]+1,j)
 *  6     print")"
 *  
*/ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/*preallocation ,consume 4MB memory space */
struct multi_split{
    int m[1024][1024];
    int s[1024][1024];
};

/*Prototype,second argument is the length of array which first argument is pointing to*/
struct multi_split* matrix_chain_order(int *, int );

void print_subproblem_optimal_value(int m[1024][1024],int length);
void print_optimal_parens(int s[1024][1024], int i, int j);
void print_split_value(int s[1024][1024],int length);

int main(){
    /* can reconstruct a interface function to handle command line arguments,
       such as matrix dimension,and so on */ 
    int p[7] = {30, 35, 15, 5, 10, 20, 25};
    int length =  sizeof p /sizeof (p[0]) - 1;
    if(length > 1023)
    {
        printf("We should enlarge dimension of array m and s in struct multi_split\n");
        exit(1);
    }

    struct multi_split *optvalue = matrix_chain_order(p, length);
    printf("The minimum number of scalar multiplications " 
     "to multiply the 6 matrices is m[1][6] = %d\n\n", optvalue -> m[1][6]);
    print_subproblem_optimal_value(optvalue -> m,length);
    print_split_value(optvalue -> s,length);
    print_optimal_parens(optvalue -> s, 1, length);
    printf("\n");
    return 0;
}

struct multi_split* matrix_chain_order(int *p, int length){
    int i, l;
    int n = length;
    static struct multi_split  ms;

    if(n > 1023)
    {
        printf("We should enlarge dimension of array m and s in struct multi_split\n");
        exit(1);
    }

    /* initialize two large enough arrays */
    for(i = 0;i < 1024; i++){
        int j;
        for(j = 0; j < 1024; j++){
            ms.m[i][j] = 0;
            ms.s[i][j] = 0;
        }
    }
    
    for(l = 2;l <= n; l++){
        int i;
        for(i = 1; i <= n - l +1; i++){
            int k;
            int j = i + l - 1;
            ms.m[i][j] = INT_MAX;
            for(k = i; k < j; k++){
                int q;
                q = ms.m[i][k] + ms.m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < ms.m[i][j]){
                   ms.m[i][j] = q;
                   ms.s[i][j] = k;
                 } 
            }
        }
    }
    return &ms;
}

void print_subproblem_optimal_value(int m[1024][1024],int length){
     int i, j;
     printf("Each subproblem's optimal value is:\n");
     for(i = 1; i <= length; i++){
        for(j = 1; j <= length; j++){
        if(m[i][j] != 0)
           printf(" [%d][%d] = %d ", i, j, m[i][j]);
        }
    }
   printf("\n\n");
}

void print_split_value(int s[1024][1024],int length){
     int i,j;
     printf("Each subproblem's split value:\n");
     for(i = 1; i <= length - 1; i++){
        for(j = 2; j <= length; j++){
           if(s[i][j] != 0)
             printf(" [%d][%d] = %d ", i, j, s[i][j]);
        }
    }
   printf("\n\n");

}

void print_optimal_parens(int s[1024][1024],int i, int j){
    if( i == j){
        printf("A%d", i);
      }
    else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j]+1, j);
        printf(")");
       }
}

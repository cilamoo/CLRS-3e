/**
 * 15.5 Optimal binary search trees
 *
 * Words appear with different frequencies, however, and a frequently 
 * used word such as the may appear far from the root while a rarely 
 * used word suchas machicolation appears near the root.
 * 
 * optimal binary search tree: organize a binary search tree so as to minimize 
 * the number of nodes visited in all searches
 * 
 * assume that the actual cost of a search equals the number of nodes examined,
 * i.e., the depth of the node found by the search in T, plus 1.(see 15.11)
 * 
 * an optimal binary search tree is not necessarily a tree whose overall height 
 * is smallest. Nor can we necessarily construct an optimal binary search tree 
 * by always putting the key with the greatest probability at the root.
 * 
 * Step 1: The structure of an optimal binary search tree
 * optimal substructure: if an optimal binary search tree T has a subtree T'
 * containing keys ki,...,kj , then this subtree T' must be optimal as well 
 * for the subproblem with keys ki,...,kj and dummy keys di-1,...,dj.
 * 
 * Step 2: A recursive solution
 *         |—— qi-1                                  if j = i-1
 * e[i,j]= |
 *         |—— min{ e[i,r-1] + e[r+1,j] + w[i,j] }   if i ≤ j 
 *              i≤r≤j
 * 
 * Step 3: Computing the expected search cost of an optimal binary search tree
 *  OPTIMAL-BST(p,q,n)
 *  1 let e[1..n+1, 0..n], w[1..n+1, 0..n] and root[1..n,1..n] be new tables
 *  2 for i = 1 to n + 1
 *  3     e[i,i-1] = qi-1
 *  4     w[i,i-1] = qi-1
 *  5 for l = 1 to n
 *  6     for i = n - l + 1 
 *  7         for j = i + l - 1 
 *  8             e[i,j] = ∞ 
 *  9             w[i,j] = w[i,j-1] + pj + qj
 *  10            for r = i to j 
 *  11                t = e[i,r-1] + e[r+1,j] + w[i,j]
 *  12                if t < e[i,j]
 *  13                    e[i,j] = t 
 *  14                    root[i,j] = r 
 *  15 return e and root 
 * 
 * The OPTIMAL-BST procedure takes Θ(n^3)
  * */

#include <stdio.h> 
#include <limits.h> 

struct er{
    double e[7][6];
    unsigned int root [6][6];
};

struct er* optimal_bst(double *p, double *q, int n);
void print_result(struct er *pr);

int main(){
    double p[5] = {0.15, 0.10, 0.05, 0.10, 0.20};
    double q[6] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    struct er *per;
    int n = 5;
    per = optimal_bst(p, q, n);
    print_result(per);
    return 0;
}

struct er* optimal_bst(double *p, double *q, int n){
    int i, j, l, r;
    static struct er er_data;
    double w[7][6];
    for(i = 0; i < 7;i++){
        for(j = 0;j < 6; j++){
            er_data.e[i][j] = 0.0;
            w[i][j] = 0.0;
        }
    }
    
    for(i = 0; i < 6; i++)
        for(j = 0; j < 6;j++)
            er_data.root[i][j] = 0;

    for(i = 1;i <= 6; i++){
        er_data.e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }
 
    for(l = 1; l <= 5; l ++){
        int n2 = n - l + 1;
        for(i = 1; i <= n2; i ++ ){
            j = i + l - 1;
            er_data.e[i][j] = (double)INT_MAX;
            w[i][j] = w[i][j-1] + p[j-1] + q[j];
            printf("w[%d][%d] = %g ", i, j, w[i][j]);
            printf("\n");

            for(r = i; r <= j; r++){
                double t;
                t = er_data.e[i][r-1] + er_data.e[r+1][j] + w[i][j];
                if(t < er_data.e[i][j] ){
                    er_data.e[i][j] = t;
                    er_data.root[i][j] = r;
                }
            }
        }
    }
    return &er_data;
}

void print_result(struct er *pr){
    printf("\n");
    int i,j;
    for(i = 1;i <= 6; i++){
        for(j = 0; j <= 5; j++)
            printf("e[%d][%d] = %g ", i, j, pr -> e[i][j]);
    }
    printf("\n\n");

    for(i = 1; i <= 5; i++){
        for(j = 1; j <= 5; j++)
            printf("root[%d][%d] = %d ",i,j, pr -> root[i][j]);
   }
    printf("\n");
}

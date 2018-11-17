/**
 * 15.4 Longest common subsequence
 * 1.
 * Step 1: Characterizing a longest common subsequence
 * The way that Theorem 15.1 characterizes longest common subsequences tells 
 * us that an LCS of two sequences contains within it an LCS of prefixes of the two
 * sequences. Thus, the LCS problem has an optimal-substructure property
 * 
 * Step 2: A recursive solution
 *           |—— 0                        if i = 0 or j = 0
 *  c[i,j] = |—— c[i-1,j-1]+1             if i,j > 0 and xi = yj 
 *           |—— max(c[i,j-1],c[i-1,j])   if i,j > 0 and xi ≠ yj //i,j are subscript
 * 
 * Step 3: Computing the length of an LCS
 * computes the entries in row-major order
 * 
 * LCS-LENGTH(X,Y)
 * 1 m = X.length 
 * 2 n = Y.length
 * 3 let c[0..m,0,.n] and b[1..m,1..n] be new arrays 
 * 4 for i = 1 to m
 * 5     c[i,0] = 0 
 * 6 for j = 0 to n 
 * 7     c[0,n] = 0 
 * 8 for i = 1 to m
 * 9     for j = 1 to n 
 * 10        if xi = yj
 * 11            c[i,j] = c[i-1,j-1] + 1
 * 12            b[i,j] = "↖"
 * 13        elseif c[i-1,j] ≥ c[i,j-1]
 * 14            c[i,j] = c[i-1,j]
 * 15            b[i,j] = "↑"
 * 16        else c[i,j] = c[i,j-1]
 * 17             b[i,j] = "←"
 * 18 return c and b 
 * 
 * The running time of the procedure is θ(mn), since each table entry takes θ(1) time to compute.
 * 
 * Step 4: Constructing an LCS
 *  PRINT-LCS(b,X,i,j)
 *  1 if x = 0 or y = 0
 *  2     return 
 *  3 if b[i,j] == b[i,j] = "↖"
 *  4     PRINT-LCS(b,X,i-1,j-1)
 *  5     print xi
 *  6 elseif b[i,j] == "↑"
 *  7     PRINT-LCS(b,X,i-1,j)
 *  8 else PRINT-LCS(b,X,i,j-1)
 *  The procedure takes time O(m+n), since it decrements at least one of i and j in each recursive call
 * 
 * 2.
 *  Some changes can simplify the code and improve constant factors but otherwise yield no asymptotic 
 * improvement in performance.Others can yield substantial asymptotic savings in time and space.
*/       

#include <stdio.h> 

char X[7] = {'A','B','C','B','D','A','B'};
char Y[6] = {'B','D','C','A','B','A'};

struct cb{
    int            c[8][7];
    unsigned int   b[7][6];
};

struct cb* lcs_length(char *X, int xl, char *Y, int yl);
void print_lcs(unsigned int b[7][6], char *X, int i, int j);

int main(){
    struct cb *optvalue;
    optvalue = lcs_length(X,7,Y,6);
    print_lcs(optvalue -> b, X,7,6);
    printf("\n");
    return 0;
}

struct cb* lcs_length(char *X, int xl, char *Y, int yl){
    int i, j, i2, j2;
    int m = xl;
    int n = yl;
    
    static struct cb store;
    for(i = 1; i <= m; i++)
        store.c[i][0] = 0;
    for(j = 0; j <= n; j++)
        store.c[0][j] = 0;
    
    int m2,n2;
    for(m2 = 0; m2 < m; m2++){
        for(n2 = 0; n2 < n; n2++){
            store.b[m2][n2] = 0;
        }
    }
    
    for(i2 = 1; i2 <= m; i2++){
        for(j2 = 1; j2 <= n;j2++){
            if(X[i2-1] == Y[j2-1]){
                store.c[i2][j2] = store.c[i2-1][j2-1] + 1;
                store.b[i2-1][j2-1] = 256;
            }
            else if(store.c[i2-1][j2] >= store.c[i2][j2-1]){
                store.c[i2][j2] = store.c[i2-1][j2];
                store.b[i2-1][j2-1] = 512; 
            }
            else{
                store.c[i2][j2] = store.c[i2][j2-1];
                store.b[i2-1][j2-1] = 1024;
            }
        }
    }

    return &store;
}

void print_lcs(unsigned int b[7][6], char *X, int i, int j){
    if( i == 0 || j == 0)
       return;
    
    if(b[i-1][j-1] & 256){
        print_lcs(b,X,i-1,j-1);
        printf("%c",X[i-1]);
    }
    else if(b[i-1][j-1] & 512){
        print_lcs(b,X,i-1,j);
    }
    else
        print_lcs(b,X,i,j-1);
}



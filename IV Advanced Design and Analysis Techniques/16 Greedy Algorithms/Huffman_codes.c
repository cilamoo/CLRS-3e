/**
 * binary character code (or code for short):in which each character is 
 * represented by a unique binary string, which we call a codeword.
 * 
 * fixed-length code
 * 
 * A variable-length code can do considerably better than a fixed-length code, by
 * giving frequent characters short codewords and infrequent characters long codewords
 * 
 * 1.Prefix codes
 * We consider here only codes in which no codeword is also a prefix of 
 * some other codeword. Such codes are called prefix codes, a prefix code 
 * can always achieve the optimal data compression among any character 
 * code.
 * 
 * Prefix codes are desirable because they simplify decoding. Since no codeword 
 * is a prefix of any other, the codeword that begins an encoded file is unambiguous.
 * 
 * The decoding process needs a convenient representation for the prefix code so 
 * that we can easily pick off the initial codeword. A binary tree whose leaves are 
 * the given characters provides one such representation. We interpret the binary 
 * codeword for a character as the simple path from the root to that character, where 0 
 * means “go to the left child” and 1 means “go to the right child.” 
 * 
 * Note that these are not binary search trees, since the leaves need not appear in 
 * sorted order and internal nodes do not contain character keys.
 * 
 * An optimal code for a file is always represented by a full binary tree, in which 
 * every nonleaf node has two children
 * 
 * if C is the alphabet from which the characters are drawn and all character frequencies
 * are positive, then the tree for an optimal prefix code has exactly |C| leaves, one for
 * each letter of the alphabet, and exactly |C|-1 internal nodes
 * 
 * 2.Constructing a Huffman code
 * Huffman invented a greedy algorithm that constructs an optimal prefix code called 
 * a Huffman code.
 * 
 * The algorithm uses a min-priority queue Q, keyed on the freq attribute, to identify 
 * the two least-frequent objects to merge together.
 * 
 * HUFFMAN(C)
 * 1 n = |C|
 * 2 Q = C
 * 3 for i = 1 to n-1
 * 4     allocate a new node z
 * 5     z.left = x = EXTRACT-MIN(Q)
 * 6     z.right = y = EXTRACT-MIN(Q)
 * 7     z.freq = x.freq + y.freq
 * 8     INSERT(Q,z)
 * 9 return EXTRACT-MIN(Q) // return the root of the tree
 * 
 * To analyze the running time of Huffman’s algorithm, we assume that Q is implemented
 * as a binary min-heap (see Chapter 6). For a set C of n characters, we can initialize 
 * Q in line 2 in O(n) time using the BUILD-MIN-HEAP procedure discussed in Section 6.3.
 *  The for loop in lines 3–8 executes exactly n - 1 times, and since each heap operation
 *  requires time O(lgn), the loop contributes O(nlgn) to the running time. Thus, the 
 * total running time of HUFFMAN on a set of n characters is O(nlgn). We can reduce the 
 * running time to O(nlglgn) by replacing the binary min-heap with a van Emde Boas tree
 *  (see Chapter 20).
 * 
 * 3.Correctness of Huffman’s algorithm
 * 
 * Lemma 16.2
 * Let C be an alphabet in which each character c∈C has frequency c.freq. Let 
 * x and y be two characters in C having the lowest frequencies. Then there exists 
 * an optimal prefix code for C in which the codewords for x and y have the same 
 * length and differ only in the last bit.
 * 
 * Lemma 16.2 implies that the process of building up an optimal tree by mergers 
 * can, without loss of generality, begin with the greedy choice of merging together 
 * those two characters of lowest frequency. Why is this a greedy choice? We can 
 * view the cost of a single merger as being the sum of the frequencies of the two items 
 * being merged. Exercise 16.3-4 shows that the total cost of the tree constructed 
 * equals the sum of the costs of its mergers. Of all possible mergers at each step, 
 * HUFFMAN chooses the one that incurs the least cost.
 * 
 * Lemma 16.3
 * Let C be a given alphabet with frequency c.freq defined for each character c∈C.
 * Let x and y be two characters in C with minimum frequency. Let C' be the alphabet
 *  C with the characters x and y removed and a new character z added, so that
 *  C' = C - {x,y} U {z}. Define freq for C' as for C, except that
 *  z.freq = x.freq + y.freq. Let T' be any tree representing an optimal prefix code
 * for the alphabet C'. Then the tree T , obtained from T' by replacing the leaf node 
 * for z with an internal node having x and y as children, represents an optimal prefix 
 * code for the alphabet C.
 * 
 * Theorem 16.4
 * Procedure HUFFMAN produces an optimal prefix code
 * 
 *
 */

/*TODO: code implementation */
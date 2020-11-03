Earlier parts have presented other
widely applicable techniques, such as divide-and-conquer, randomization, and how
to solve recurrences. The techniques in this part are somewhat more sophisticated,
but they help us to attack many computational problems.

//表格法, 一种表, 查找表 
1.Dynamic programming, “Programming” in this context refers
to a tabular method, not to writing computer code.

2.divide-and-conquer algorithms partition the problem into disjoint subproblems,
solve the subproblems recursively, and then combine their solutions to solve
the original problem
//缓存
A dynamic-programming algorithm solves each
subsubproblem just once and then saves its answer in a table
//应用于最优解
3.apply dynamic programming to optimization problems. Such problems
can have many possible solutions

4.When developing a dynamic-programming algorithm, we follow a sequence of
four steps:
1. Characterize the structure of an optimal solution.
2. Recursively define the value of an optimal solution.
3. Compute the value of an optimal solution, typically in a bottom-up fashion.
4. Construct an optimal solution from computed information


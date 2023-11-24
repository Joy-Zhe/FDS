## Search tree
##### 1-2 In a binary search tree which contains several integer keys including 4, 5, and 6, if 4 and 6 are on the same level, then 5 must be their parent.
+ (Ans: F) They may be not the direct son of 5
##### 2-3 Given a binary search tree with its preorder traversal sequence { 8, 2, 15, 10, 12, 21 }. If 8 is deleted from the tree, which one of the following statements is FALSE?
+ A. One possible preprder traversal sequence of the resulting tree may be { 2, 15, 10, 12, 21 }
+ B. One possible preprder traversal sequence of the resulting tree may be { 10, 2, 15, 12, 21 }
+ ***C. One possible preprder traversal sequence of the resulting tree may be { 15, 10, 2, 12, 21 }***
+ D. It is possible that the new root may have 2 children
+ search tree——delete
## Graph
+ If an undirected graph G = (V, E) contains 7 vertices. Then to guarantee that G is connected in any cases, there has to be at least \_\_\_\_ edges.**(Ans:16)**
+ **Ans:** first generate a connected graph with 7 - 1 = 6 vertices, then it will need $C_6^2 = 15$ edges to make itself absolutely connected. Finally, connect the $7^{th}$ vertex to the former graph, then we have 15 + 1 = 16 
# Basic Data Structure
## Idea
+ `Union(i,j)`:将具有某一关系的元素归为同一类，最暴力的方法——直接作为叶节点的子节点插入。
``` C
void SetUnion(DisjSet S, SetType Rt1, SetType Rt2){
	S[Rt2] = Rt1;
	return;
}
```
+ `Find(i)`:查找某一个元素所在集合的根节点。
``` C
ElementType Find(ElementType X, DisjSet S){
	for(; S[X]; X = S[X]);
	return X;
}
```
+ Optimize:
1) Union-by-size: 将规模较小的树合并至较大的树
	+ record the size: `S[root] = -size//initialized to be -1`
	+ `T` is a tree created bt union-by-size, and have `N` nodes, then 
$$height(T)\leq \lfloor log_2(N)\rfloor + 1$$
+ union time complexity: $O(log_2 (N))$
+ Time complexity of N Union and M find operations: $O(N + M log_2(N))$
2) Union-by-Height:将高度较小的树合并至较大的树
+ 复杂度分析同上
3) Path Compression
+ resursion one:
``` C
ElementType Find(ElementType X, DisJSet S){
	if(S[X] <= 0) 
		return X;
	else 
		return S[X] = Find(S[X], S);
}
```
+ not recursion one:
``` C
ElementType Find(ElementType X, DisjSet S){
	ElementType root, trail, lead;
	for(root = X; S[root] > 0; root = S[root]);//find root
	for(trail = X; trail != root; trail = lead){
		lead = S[trail];
		S[trail] = root;
	}
	return root;
}
```
### Worst Case for Union-by-rank and Path Compression
+ see [(PDF) Worst-case Analysis of Set Union Algorithms (researchgate.net)](https://www.researchgate.net/publication/220430653_Worst-case_Analysis_of_Set_Union_Algorithms)
+ and [并查集复杂度 - OI Wiki](https://oiwiki.org/ds/dsu-complexity/)
## HW7 
### 7-1 File Transfer
+ We have a network of computers and a list of bi-directional connections. Each of these connections allows a file transfer from one computer to another. Is it possible to send a file from any computer on the network to any other?
### Input Specification:
+ Each input file contains one test case. For each test case, the first line contains N (2≤N≤104), the total number of computers in a network. Each computer in the network is then represented by a positive integer between 1 and N. Then in the following lines, the input is given in the format:
```
I c1 c2  
```
+ where `I` stands for inputting a connection between `c1` and `c2`; or
```
C c1 c2    
```
+ where `C` stands for checking if it is possible to transfer files between `c1` and `c2`; or
```
S
```
+ where `S` stands for stopping this case.
### Output Specification:
+ For each `C` case, print in one line the word "yes" or "no" if it is possible or impossible to transfer files between `c1` and `c2`, respectively. At the end of each case, print in one line "The network is connected." if there is a path between any pair of computers; or "There are `k` components." where `k` is the number of connected components in this network.
### Sample Input 1:
```in
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
S
```
### Sample Output 1:
```out
no
no
yes
There are 2 components.
```
### Sample Input 2:
```in
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
I 1 3
C 1 5
S
```
### Sample Output 2:
```out
no
no
yes
yes
The network is connected.
```
+ my src:
``` C
#include<stdio.h>
int num[10001];
int find(int *a, int num){
    int root = num, node = num;
    while(a[root] != root)
        root = a[root];
    while(node != root){
        a[node] = root;
        node = a[node];
    }
    return root;
}
int main (){
    int n, op, n1, n2;
    int cnt = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        num[i] = i;
    while((op = getchar()) != 'S'){
        if(op == 'C'){
            scanf("%d %d", &n1, &n2);
            if(find(num, n1) != find(num, n2))
                printf("no\n");
            else
                printf("yes\n");
        }else if(op == 'I'){
            scanf("%d %d", &n1, &n2);
            int tmp;
            tmp = find(num, n2);
            num[tmp] = n1;
        }
    }
    for(int i = 1; i <= n; i++){
        if(num[i] == i)
            cnt++;
    }
    if(cnt <= 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", cnt);
    return 0;
}
```
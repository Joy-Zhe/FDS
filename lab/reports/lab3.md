# Chapter 1: Introduction
### Problem description：
+ Holiday is coming. Lisa wants to go home by train. But this time, Lisa does not want to go home directly -- she has decided to take the second-shortest rather than the shortest path. Your job is to help her find the path.
+ There are `M` stations and `N` **unidirectional** railway between these stations. For simplicity Lisa starts at No.`1` station and her home is at No.`M` station.
+ The second-shortest path can **backtrack**, i.e., use the same road more than once. The second-shortest path is the shortest path whose length is longer than the shortest path(s) (i.e. if two or more shortest paths exist, the second-shortest path is the one whose length is longer than those but no longer than any other path).
+ Here is 2 examples for 2 possible conditions:
1) including backtrack
	+ we can see the shortest path is ***1-2-4-5*** with a total length of 100
	+ and the $2^{nd}$ shortest path is ***1-2-4-2-4-5*** with a total length of 120
![eg1](D:\code\Learning\DS\DS\e.g.1.png)
2) including dual or more paths between 2 vertices
	+ we can see the shortest path is ***1-2*** with a total length of 20
	+ and the $2^{nd}$ shortest path is ***1-2*** with a total length of 30
![eg2](D:\code\Learning\DS\DS\e.g.2.png)
# Chapter 2: Algorithm Specification
#### The Data Stucture
+ the main structure
```
struct edge{
    int next_V;
    int dis;
    int next;
}N[5001];
cnt := the counter for all the nodes
head[5001] := the start index of the head vertex
```
+ add new edge
``` 
Procedure add(from: the start vertex, to: the end vertex, dis: distance of this edge)
	cnt++
	the vertex edge N[cnt] connected to := to
	the distance of edge N[cnt] := dis
	next edge's index for edge N[cnt] := head[from]
	head[from] := cnt
```
+ enumerate edges begin from vertex `v`
```
Procedure enumerate(v: the vertex as the begin point)
	var i := the index of the edges
	for i := head[v]; index i is not 0
	begin	
		next_V := N[i].next_V
		distance := N[i].dis
		i := N[i].next
	end
```
#### The judging programmes
+ ***Generating and Testing:*** 
+ ***Generating:***
	+ with randonmized edges
``` 
Procedure Generate(m : the number of vertices, n : the number of edges)
	for i from 1 to n
	begin 
		randomize (a,b) and the distance between them
	end
```
+ ***testing***:
	+ drawing the graph with shortest path with matlab
	+ judge if it's a possible $2^{nd}$ shortest path
#### the main algorithms
##### the dijkstra algorithm
+ although this problem need to find the $2^{nd}$ shortest path, but it's necessary in the way to approach the answer.
+ **Summary:** 
	+ To find the shortest path from the start to the end, we can use **dijkstra algorithm**
	+ The main thoughts of this algorithm is to find the nearest vertex and use it to update the present `min_dis[]` array
+ **Detail:** 
	+ first, initialize the min_dis array with the edge go from the $1^{st}$ vertex.
	+ then begin a loop, each time find a nearest vertex `v_next` first(set its flag as chosen), and use the chosen vertex to update the vertices which haven't been chosen yet in the `min_dis` array, compare the distance from `v_next` to it with its present path length in `min_dis`, keep it always the minimum.
	+ after all the vertices are chosen, the algorithm has done, and the shortest path from start to the end is the last element in the array `min_dis`
```
Procedure dijkstra(n: the number of vertices, *f: the array record the passed vertices, *dis: the array store the shortest distance, *path: record the path, flag: choose the order) 
    var v_next
    initialize dis[]
    while(can find a not passed nearest vertex) begin
	    v_next := the nearest vertex
	    if(not found) 
		    all found, quit
		f[v_next] := passed
		for j run all the connected vertex with v_next 
		begin
			var next := the next vertex of the present vertex
			var w := the distance between the present and next vertex
			if(the shortest dis[v_next] + w < the original shortest dis[next])
				update dis[next] and path[next]
		end
    end
```
##### How to get the shortest path from end to start
+ **ATTENTION:** Because the graph is unidirectional, so the dijkstra from the end point cannot be done directly by enumerating from the end point(there may be no edge back while there is actually edge go).
	+ Thus, here I use an algorithm to solve this problem
	+ The algorithm need another "virtual graph" of the present graph:
	+ **I define the virtual graph as follow:** It's an undirected graph of the original graph
	+ **How to get it:** We only need to generate it together with the original graph like this
```
add (from, to)
add_virtual (from, to)
add_virtual (to, from)
```
+ then comes the judge function to judge whether `(y ,  x)` exists in the original graph while enumerating (x, y) in the virtual graph
	+ for example, when I need to enumerate `(x, home)`, in my dijkstra function, I will find it by `(home, x)`, thus we use the virtual graph to enumerate first, and then judge if `(x, home)` is available in the real(original) graph
	+ here is the function
```
Procedure back_judge(x: the from point in the virtual graph, y: the to point in the virtual graph) 
	 for i enumerate the edges start with head[y]
	 begin
		 if find (y,x)
			 return available
	 end
	return unavilable
```
+ With this function, we can get a shortest path for end to st by enumerating in the virtual graph first and then judge its existence in the real graph
```
Procedure dijkstra_back(n: the number of vertices, *f: the array record the passed vertices, *dis: the array store the shortest distance, *path: record the path, flag: choose the order) 
    var v_next
    initialize dis[]
    while(can find a not passed nearest vertex) begin
	    v_next := the nearest vertex
	    if(not found) 
		    all found, quit
		f[v_next] := passed
		for j run all the connected vertex with v_next 
		begin
			var next := the next vertex of the present vertex
			var w := the distance between the present and next vertex
			if(the shortest dis[v_next] + w < the original shortest dis[next] and (next, V_next) is available)
				update dis[next] and path[next]
		end
    end

```

##### the $2^{nd}$ shortest path algorithm
+ **Summary:** 
	1) use twice the **dijkstra algorithm**(one from the start vertex, one from the end vertex to the start vertex), and stored in `min_dis[]` and `min2_dis[]`
	2) enumerate all the possible edges(ordered (v1, v2), **e.g.** (2,4) and (4,2) have different meanings, (2,4) means $1\rightarrow 2\rightarrow 4\rightarrow home$, while (4,2) means $1\rightarrow 4\rightarrow 2\rightarrow home$), and use the 2 array get ***the distance from  start to v1*** and ***the distance from end to v2***
	3) add the two distance with the distance between them, update the $2^{nd}$ shortest path if find a path larger than shortest and smaller than the present $2^{nd}$ shortest path
+ **the correctness:**
	+ for edge (x , y) , `min_dis[x]` can get the shortest path from the start point to x, and `min2_dis[y]` is the shortest path from y to the end point, thus, `min_dis[x] + min2_dis[y] + dis(x,y)` is the shortest path length in the path $1\rightarrow x \rightarrow y \rightarrow home$
		+ ***p.s.*** because the shortest path of $1\rightarrow home$ has been figure out in the previous step, here we can directly use it by `min_dis[home]` or `min2_dis[1]`
	+ use a varite `ans_min_2nd` to record the $2^{nd}$ shortest path 
	+ by enumerating all the possible edges, we can find the shortest path including a certain edge (x,y)
	+ Since the $2^{nd}$ shortest path is only longer than the shortest path, thus the answer must be among the shortest path including each edge 
		+ **why:** it's clear that there are 2 different conditions；
			1) edge (x,y) is on one of the shortest path of $1\rightarrow home$
				+ it's one of the shortest path
			2) edge (x,y) is not on the shortest path of $1\rightarrow home$
				+ it's a longer path than the shortest path, but since it's the shortest path including (x,y), thus this path can be a 'candidate' for the  $2^{nd}$ shortest path.
	+ while find a path longer than `min_dis[home]` and shorter than the present `ans_min_2nd`, update the $2^{nd}$ shortest path stored in `ans_min_2nd`.
```
Produce find2nd()
	initialize 2nd_min := INF
	initialize min := min_dis[home] the shortest path to home
	for i enumerate all the vertex
	begin
		for j enumerate all the connected vertices to i
		begin
			var w := length of edge (i, j)
			if(w + min_dis[i] + min2_dis[j] > min(w + min_dis[i] + min2_dis[j] < 2nd_min)
				update 2nd_min
				record the edge (i,j)
		end
	end
```
##### the output part
+ **Summary:** let the found edge as (ansi, ansj), then because the path array record the index of the former vertex, to get the path of 1 to ansi, we need a stack to push the sequence of the path into the stack first. **However**, the path ansj to home is actually get by home to ansj, thus it's already the sequence of the ans path, we just need to print it out after pop all the element in the 1 to ansi stack. 
+ p.s. need to use the edge (ansi, ansj) recorded in `find2nd()`
``` 
Procedure output()
	for i enumerate the path from ansi to the start
	begin
		push i
	end
	while(stack is not empty)
	begin
		pop 
		print
	end
	for i enumerate the path from ansj to the end
	begin
		print i
	end
```

# Chapter 3: Testing Results
+ **ATTENTION:** the highlighted path in the graph are all shortest path found by matlab but not the answer of the problem!

|(v,e)| |10,1000|200,1000|500,1500|800,2000|1100,3000|1500,5000|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
||(K)|$10^6$|$10^4$|$10^{4}$|$10^3$|$10^3$|$10^2$|
| |Ticks|10877|2146|11599|2612|5076|983|
||Total Time(sec)|10.877|2.146|11.599|2.612|5.076|0.983|
||Duration(sec)|$1.0877\times 10^{-5}$|$2.146\times10^{-4}$|$1.1599\times 10^{-3}$|$2.612\times 10^{-3}$|$5.076\times 10^{-3}$|$9.83\times 10^{-3}$
|output | |![graph](D:\code\Learning\DS\lab\lab3\outgraph\1.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\2.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\3.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\4.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\5.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\6.png)|
|graph| |![graph](D:\code\Learning\DS\lab\lab3\outgraph\11.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\22.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\33.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\44.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\55.png)|![graph](D:\code\Learning\DS\lab\lab3\outgraph\66.png)
+ ***The Graph for the runtimes:***
![graph](D:\code\Learning\DS\lab\lab3\outgraph\graph.png)
+ Some examples:
1) a normal example
+ the shortest path is $1\rightarrow 2 \rightarrow 3\rightarrow 6\rightarrow 10$ with a length of $40 + 13 + 46 + 38 = 137$
+ the $2^{nd}$ shortest path is $1\rightarrow 2 \rightarrow 3\rightarrow 6\rightarrow 5 \rightarrow 10$ with a length of $40 + 13 + 46 + 34 + 26 = 159$
+ ![e1](D:\code\Learning\DS\lab\lab3\outgraph\e1.png)
+ ![e1](D:\code\Learning\DS\lab\lab3\outgraph\e12.png)
2) back tracking from home
+ the shortest path is $1\rightarrow 10$ with a length of $18$
+ the $2^{nd}$ shortest path is $1\rightarrow 10 \rightarrow 5\rightarrow 9 \rightarrow 4 \rightarrow 2 \rightarrow 10$ with a length of $18 + 8+1+9+16+15=67$
+ ![e1](D:\code\Learning\DS\lab\lab3\outgraph\e2.png)
+ ![e1](D:\code\Learning\DS\lab\lab3\outgraph\e22.png)
3) back tracking from home with a double road($9\rightarrow4 \ d = 9or4$)
+ the shortest path is $1\rightarrow 10$ with a length of $18$
+ the $2^{nd}$ shortest path is $1\rightarrow 10 \rightarrow 5\rightarrow 9 \rightarrow 4 \rightarrow 2 \rightarrow 10$ with a length of $18 + 8+1+4+16+15=62$(the answer changed from 67 to 62 due to the added 4)
+ ![e1](D:\code\Learning\DS\lab\lab3\outgraph\e4.png)
+ ![e1](D:\code\Learning\DS\lab\lab3\outgraph\e42.png)

# Chapter 4: Analysis and Comments
1) the time complexity
	1) the dijkstra algorithm
		+ there are a n-loop
		+ in each loop step, there are a 0-n loop to enumerate the possible edges and a `find_min` function with time complexity of $O(n)$
		+ Thus, the worst case of dijkstra algorithm is $O(n^2)$
	2) the `find_min` function enumerate all the vertices, thus it's $O(n)$
+ In general, the time complexity of the algorithm is actually the time complexity of the dijkstra algorithm, which is $O(n^2)$.
2) the space complexity
	+ the structure to store the edges has a head vertex array cost `n`(number of vertices) space and the node of edges need `n * 3` space, it's $O(n)$
	+ the structure to store the edges in the virtual no direction graph has the same space cost as the original edges, thus it's $O(n)$
	+ the 2 min_dis array store the shortest paths, thus it's $O(n)$
+ In general, the space complexity of the algorithm is $O(n)$

# Appendix: Source Code in C
+ the **main.c** file:
``` C
#include<stdio.h>
#include"tester.h"
#define INF 99999999
int min_path[200001], min2_path[200001];
int min_dis[200001], min2_dis[200001];//min_dis[] record the shortest distance from st to end
                                    //min2_dis[] record the shortest distance from end to st
int flag_toend[200001], flag_tost[200001];//to judge whether the path have been updated(one for go, one for back)
int find_min(int *min_dis, int *f, int n);//find the next shortest vertex, if not exist, return 0, else return the index of the vertex
struct edge{
    int next_V;//store the vertex this edge go to
    int dis;//store distance
    int next;//store the index of the previous edge connected with the same head
}N[500001], Nforback[500001];// the real graph and the virtual one
int head[500001], head_virtual[500001], cnt, cnt_v;
void add_edge(int from, int to, int dis){
    cnt++;//the total number of the node of edges
    N[cnt].next_V = to;//store the vertex this edge connect to
    N[cnt].dis = dis;//store the distance of this edge
    N[cnt].next = head[from];//store the index of the previous edge connected with the same head
    head[from] = cnt;//update the index of the last 'from' with the latest 'cnt'
}
void add_virtualedge(int from, int to, int dis)
    cnt_v++;//the total number of the node of edges
    Nforback[cnt].next_V = to;//store the vertex this edge connect to
    Nforback[cnt].dis = dis;//store the distance of this edge
    Nforback[cnt].next = head_virtual[from];//store the index of the previous edge connected with the same head
    head_virtual[from] = cnt_v;//update the index of the last 'from' with the latest 'cnt'
}
int back_judge(int x, int y){//for (x,y) in the virtual graph, judge if (y,x) is possible in the real graph
    int next;
    for(int i = head[y]; i; i = N[i].next){
        next = N[i].next_V;
        if(next == x)
            return 1;
    }
    return 0;
}
//flag == 1 represent st to end, flag == home represent end to st
void dijkstra(int n, int *f, int *dis, int *path, int flag);
void dijkstra_back(int n, int *f, int *dis, int *path, int flag);
int main (){
    int home, total_edge;
    int pre, next, dis;
    int mode;//choose the testing mode
    int ans_min_2nd = INF, min = INF, ansi = 0, ansj = 0;
    FILE *fpin;
    printf("choose the testing mode(0 for by hand, 1 for auto):");
    scanf("%d", &mode);
    printf("type in the number of vertices and edges:");
    if(mode == 0)//type by hand
        scanf("%d %d", &home, &total_edge);
    else if(mode == 1){//generate by the tester
        scanf("%d %d", &home, &total_edge);
        tester(home, total_edge);
        fpin = fopen("data.in", "r");//open a file to store the input
        fscanf(fpin, "%d %d", &home, &total_edge);
    }
    //initialize the distance and flag
    for(int i = 1; i <= home; i++){
        min_dis[i] = INF;//set to infinite
        min2_dis[i] = INF;//set to infinite
        flag_toend[i] = 0;
        flag_tost[i] = 0;
        min_path[i] = -1;//set to no path(-1)
        min2_path[i] = -1;//set to no path(-1)
    }
    //initialize the edges
    for(int i = 1; i <= total_edge; i++){
        if(mode == 0)
            scanf("%d %d %d", &pre, &next, &dis);
        if(mode == 1)
            fscanf(fpin, "%d %d %d", &pre, &next, &dis);
        add_edge(pre, next, dis);//add (pre, next) to the edges
        add_virtualedge(pre, next, dis);// create a virtual graph with no direction
        add_virtualedge(next, pre, dis);
    }
    dijkstra(home, flag_toend, min_dis, min_path, 1);//st to end dijkstra
    dijkstra_back(home, flag_tost, min2_dis, min2_path, home);//end to st dijkstra
    //------------------------------find the 2nd shortest path-------------------------------
    ans_min_2nd = INF;
    min = INF;
    ansi = 0;
    ansj = 0;
    for(int i = 1; i <= home; i++){
        for(int j = head[i]; j; j = N[j].next){
            int next_V = N[j].next_V, w = N[j].dis;
            if(((min_dis[i] + min2_dis[next_V] + w) > min_dis[home] && ((min_dis[i] + min2_dis[next_V] + w) < ans_min_2nd))){//if larger than min and shorter than present min2nd, update
                ans_min_2nd = min_dis[i] + min2_dis[next_V] + w;
                ansi = i;
                ansj = next_V;
            }
        }
    }
    //---------------------------------------------------------------------------------------
    //---------------------------------------output part--------------------------------------
    int ans_path[5001], pos = 0;
    if(ans_min_2nd == INF){
        printf("no answer!");
        return 0;
    }
    for(int i = ansi; i != -1; i = min_path[i]){
        pos++;
        ans_path[pos] = i;
    }//push the former part path into the stack
    printf("%d", ans_min_2nd);
    while(pos){
        printf(" %d", ans_path[pos]);
        pos--;
    }
    for(int i = ansj; i != -1; i = min2_path[i]){//print the latter ones
        printf(" %d", i);
    }
    //----------------------------------------------------------------------------------------
    if(mode)
        fclose(fpin);
    return 0;
}
int find_min(int *min_dis, int *f, int n){//find the next shortest vertex, if not exist, return 0, else return the index of the vertex
    int min = INF, next = 0;
    for(int i = 1; i <= n; i++){
        if(min > min_dis[i] && f[i] == 0){//ensure the vertex hasn't been enumerated
            min = min_dis[i];
            next = i;
        }
    }
    return next;
}
void dijkstra(int n, int *f, int *dis, int *path, int flag){//flag == 1 represent st to end, flag == home represent end to st
//this function is to find the shortest path from st to end
    for(int i = 1; i <= n; i++) {
        dis[i] = INF;
        f[i] = 0;    
    }
    int v_next;
    dis[flag] = 0;//initialize the distance for itself
    while(find_min(dis, f, n)){
        v_next = find_min(dis, f, n);//find the nearest vertex
        if(v_next == 0)//not found(all passed), quit
            break;
        f[v_next] = 1;
        for(int j = head[v_next]; j; j = N[j].next){
            int next = N[j].next_V, w = N[j].dis;
            if(((dis[v_next] + w) < dis[next])){//find a shorter path
                dis[next] = dis[v_next] + w;
                path[next] = v_next;
            }
        }
    }
    return;
}
void dijkstra_back(int n, int *f, int *dis, int *path, int flag){//flag == 1 represent st to end, flag == home represent end to st
//this function is to find the shortest path from end to st, need the help of the "virtual graph"
    for(int i = 1; i <= n; i++) {
        dis[i] = INF;
        f[i] = 0;    
    }
    int v_next, canback = 0;
    dis[flag] = 0;//initialize the distance for itself
    while(find_min(dis, f, n)){
        v_next = find_min(dis, f, n);//find the nearest vertex
        if(v_next == 0)//not found(all passed), quit
            break;
        f[v_next] = 1;
        for(int j = head_virtual[v_next]; j; j = Nforback[j].next){
            int next = Nforback[j].next_V, w = Nforback[j].dis;
            canback = back_judge(v_next, next);//if the back path (V_next, next) have a possible path (next, V_next) in the real graph
            if(((dis[v_next] + w) < dis[next]) && canback){//find a shorter path and it can be reached in the real graph
                dis[next] = dis[v_next] + w;
                path[next] = v_next;
            }
        }
    }
    return;
}
```
+ the **tester.h** generator:
``` C
#ifndef _TESTER_H_
#define _TESTER_H_
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
int a[10001], b[10001], d[10001];
void tester(int m, int n){
    srand(time(0));//randomize the seed
    FILE *f;
    f = fopen("data.in","w");    
    fprintf(f,"%d %d\n", m, n);//output m n
    for(int i = 1; i <= n; i++){
        a[i] = 1 + rand() % m;
        b[i] = 1 + rand() % m;
        d[i] = 1 + rand() % 5000;//change this value to change the length of the distances
        fprintf(f, "%d %d %d\n", a[i], b[i], d[i]);
    }
    fclose(f);
    //the following code are going to output a code of a matlab based graph
    FILE *fm;
    fm = fopen("matlab_auto.txt", "w");
    fprintf(fm, "s = [");
    for(int i = 1; i <= n; i++)
        fprintf(fm, "%d ", a[i]);
    fprintf(fm, "];\n");
    fprintf(fm, "t = [");
    for(int i = 1; i <= n; i++)
        fprintf(fm, "%d ", b[i]);
    fprintf(fm, "];\n");
    fprintf(fm, "w = [");
    for(int i = 1; i <= n; i++)
        fprintf(fm, "%d ", d[i]);
    fprintf(fm, "];\n");
    fprintf(fm, "G = graph(s,t,w);\nn = %d;\nplot(G, 'EdgeLabel', G.Edges.Weight, 'linewidth', 2) ;\nset( gca, 'XTick', [], 'YTick', [] );\n[P,d] = shortestpath(G, 1, n);\nmyplot = plot(G, 'EdgeLabel', G.Edges.Weight, 'linewidth', 2);\nhighlight(myplot, P, 'EdgeColor', 'r');\nD = distances(G);\nD(1,n);", m);
    fclose(fm);
    return;
}
#endif
```
# Declaration
+ ***I hereby declare that all the work done in this project titled "Lab3 Report" is of my independent effort.***
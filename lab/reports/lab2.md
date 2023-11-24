# Chapter 1: Introduction
### Problem description：
+ Given two 2-dimentional shapes A and B which are represented as closed polygons, our goal is to find the optimal correspondences (or "match") between points in A and B. 
+ That means, we need to find a polygon in B which is most simlar with polygon A, and the match between A , B should be ascending.
+ Such as A is a triangle, and we need to find a most similar triangle with A in B which may be zoomed or rotated.
# Chapter 2: Algorithm Specification
#### The judging programmes
+ ***Generating and Testing:*** 
+ generate 2 polygon, the first one is totally randomized, and the first `n_A` dots are directly changed from the dots in polygon A by adding the Horizontal and vertical coordinates with 50 **(x + 50, y + 50)**
+ Why this doesn't influence the running time?
+ Because the program will finally run all the possible answers, the order of the points doesn't matter.
``` 
Procedure Generate()
	start:=the start time of the test process
	for i := 1 to n_A do
	begin 
		randomize generate (x_A, y_A)
		(x_B, y_B) = (x_A + 50, y_A + 50)
	end
	for i := n_A + 1 to n_B do
	begin 
		randomize generate (x_B, y_B)
	end
```
+ ***testing***:
+ **the way to confirm the program:** the answer match will be printed out, for most testing data, the answer may be a series same match between A and B(such as $(1,1)$,$(2,2)$, $(3,3)$,......), if the answer match is this, then it's absolutely correct because the first n_A point in B is changed from A directly.
+ If the answer is not like this, we can judge it directly by graph. By drawing and comparing the 2 polygons, we can find whether it's simular.
+ And the voting table, and all the pathes which have been enumerated will be printed in 2 txt files.
```
Procedure Test()
	start:=the start time of the test process
	for i:=1 to k do
	begin 
		run the function
	end
	end:=the end time of the test process
	print the information
```
+ ***judging:***
	+ by compare the former 2 match on the path with the present match, use the angle and the proportion of the corresponding side in the 2 polygons.
	+ ***The correctness:***
		+ by the proportion of the 2 corresponding sides and the angle between them, we can confirm the simularity between the 2 small triangles, and by applying this method to every consecutive 3 points, the simularity between the 2 polygons will be confirmed by this method.
```
Procedure match(n1: the first match, n2: the second match, n3: the third match)
	var p1, p2, p3, angle1, angle2
	var ma1, ma2, ma3, mb1, mb2, mb3
	ma1 = A's length between n1 and n2
	ma2 = A's length between n2 and n3
	ma3 = A's length between n3 and n1
	mb1 = B's length between n1 and n2
	mb2 = B's length between n2 and n3
	mb3 = B's length between n3 and n1
	p1 = ma1 / mb1
	p2 = ma2 / mb2
	angle1 = arccos((ma1^2 + ma2^2 - ma3^2)/(2*ma1*ma2))
	angle2 = arccos((mb1^2 + mb2^2 - mb3^2)/(2*mb1*mb2))
	if p1 almost = p2 and angle1 almost = angle2
		return a good match
	else 
		return a bad match
```
1) the enumerate algorithm
+ **Summary:** 
	+ use a recursive programme to enumerate all the path from the "forest". And in order to trace back to the root of a tree, the path will be recorded in a stack (simulated by an array in this programme). By cooperating with the match function to judge if the path is a seriers of correct matches at present, if not, pruning the present tree.
+ **Detail:** (this is the part of the data structure "tree" or called "forest")
	1) First use a "for" loop to enumerate a new tree node, which is also the root node for next step, the tree node will enumerate a possible match
	2) By judging the similarity between the present 3 or more points, the programme will decide whether to cut this tree or cultivate this tree(if do not cut, the already passed path will keep push into the stack)
	3) if cut the branch, then pop the present match from the stack to find next match(that is, go to another tree path, which lies on the present node's "brother node")
	4) if not cut the branch, then keep on enumerating(keep on going to the "child node")
	5) do the former steps recursively, then the tree(forest) will be fully enumerated 
	6) while the stack is full, that means a possible path appeared, and the programme need to vote for the matches in the path.
```
Procedure tree_dfs(Info *stack, int stack_pointer, int pos_A, int pos_B, int n_A, int n_B)
    if stack is full
        the number of votes to (i, j) ++
        pop out the last element in the stack
        return
    for i:= pos_A + 1 to n_A do
    begin
        f = 0;
        for enumerate the path have been gone do
        begin
            if(selected[k].pos_A >= i || p != (i - 1)){
                skip this i and enumerate the next i
        end
        for j := pos_B + 1 to n_B do
        begin
            for enumerate the path have been gone do
            begin
                if(selected[k].pos_B >= j)
                    skip this j and enumerate the next j
            push (i, j) to the stack
            if(there are more than 3 matches)
                if match(this match and the former 2 matches) failed
					pop this match from the stack
					skip this match
            tree_dfs(selected, p, i, j, n_A, n_B, fpout);
            after return pop the no use one from stack
        end
    end
    return
```
2) the output part
+ **Summary:**
	+ The ordinate of points in A are fixed, so find the maximum number of votes in each row of the voting table, and guarantee the points in B are in ascending order.
+ function to find the maximum number of votes in each row:
``` 
Procedure find_max(int t[][1001], int line, int n_B, int st){
    int max = -1;
    for i = st + 1 to n_B dp
    begin    
        if find a larger number of vote
            update max
            record the coordinate
    end
    set the number of votes of the selected match to 0
```
#### The data structure
1) The stack:
	+ use an array to represent the stack.
	+ set the index pointer as 0 to represent an empty stack
	+ when the stack is full, prevent it from push
+ push:
```
Procedure push(Info* present, int pointer, int num){
    pointer++
    present[pointer] = num
```
+ pop:
```
Procedure pop(Info* present, int pointer, int num){
    present[pointer] = num    
    pointer--
```
2) The tree:
	+ use a stack to store a path in the tree, and after used, delete it immediately, that means , it will only cost space less than the maximum size of the stack
	+ the traversal is done by enumerating all the possible path. And if the backtracking is done by store the path in the stack. When need to track back, pop the elements in the stack and change the path.
# Chapter 3: Testing Results
+ **put in 2 numbers:** the number of points in polygon A and B 

|$N_A = 6$|$N_B$|100|300|500|700|900|1100|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
||Iterations(K)|$100$|$50$|$10$|1|1|1|
| |Ticks|6582|92162|88537|25549|50616|99746
||Total Time(sec)|6.582|92.162|88.537|25.549|50.616|99.746
||Duration(sec)|$0.06582$|$1.843$|$8.854$|$25.549$|$50.616$|$99.746$
|the runtimes | |![graph](D:\code\Learning\DS\lab\lab2\outgraph\1.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\2.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\3.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\4.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\5.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\6.png)|
|the 2 polygons | |![graph](D:\code\Learning\DS\lab\lab2\outgraph\11.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\21.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\31.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\41.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\51.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\61.png)|the voting table｜｜![graph](D:\code\Learning\DS\lab\lab2\outgraph\v1.png)｜![graph](D:\code\Learning\DS\lab\lab2\outgraph\v2.png)｜![graph](D:\code\Learning\DS\lab\lab2\outgraph\v3.png)｜![graph](D:\code\Learning\DS\lab\lab2\outgraph\v4.png)｜![graph](D:\code\Learning\DS\lab\lab2\outgraph\v5.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\v6.png)|
|the voting table||![graph](D:\code\Learning\DS\lab\lab2\outgraph\v1.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\v2.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\v3.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\v4.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\v5.png)|![graph](D:\code\Learning\DS\lab\lab2\outgraph\v6.png)
+ the sample on PTA:(The answer is correct)
![sample](D:\code\Learning\DS\lab\lab2\outgraph\pta.png)
+ ***The Graph for the runtimes:***
![graph](D:\code\Learning\DS\lab\lab2\outgraph\graph.png)
# Chapter 4: Analysis and Comments
1) the time complexity
	+ the enumerate function have the largest time complexity, so the time complexity of the whole programme depends on the time complexity of enumerate function.
	+ the time complexity of a recursive function can be considered as the sum of each recursively step.
	+ If not cutting the useless branches, the worst time complexity will be O($n^k$)(k is the number of points in A)
	+ But after the cutting, the time complexity can be hugely decreased.(Which can be seen from examples)
2) the space complexity
	+ Because the tree or the forest is destoryed after a failure path or a successful match, so the space complexity of the programme is the maximum size of the stack which store the present path. 
	+ Thus, the time complexity is the depth of the forest, which is $O(n)$
+ During the lab, I learnt how to adjust the iteration times to adjust the ticks to decrease the inaccurancy. And in order to write a convenient testing programme, I adjust for many times to make the input and the output to be easy to use. This lab increased my understand for optimizing and inhanced my understand for tree and stack data structure.


# Appendix: Source Code in C
+ the generating function:
``` C
#ifndef _TESTER_H_
#define _TESTER_H_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
typedef struct{
    int pos_A;
    int pos_B;
}Info;
double a[1001][2], b[1001][2];
void generate_tester(int n_A, int n_B, double ta[][2], double tb[][2], int rotate){
    srand(time(0));
    for(int i = 1; i <= n_A; i++){
        ta[i][0] = rand() % 100 - 50;//generating X_A between [-50, 50)
        ta[i][1] = rand() % 100 - 50;//generating Y_A between [-50, 50)
        if(rotate == 0){//not rotate
            tb[i][0] = ta[i][0] + 50;//set X_B as X_A move 50 right
            tb[i][1] = ta[i][1] + 50;//set Y_B as Y_A move 50 right
        }else{//rotate
            tb[i][0] = (ta[i][0] + 50) * cos(0.3) - (ta[i][1] + 50) * sin(0.3);//have a rotate, times a matrix to accomplish this work
            tb[i][1] = (ta[i][0] + 50) * sin(0.3) + (ta[i][1] + 50) * cos(0.3);
        }  
    }
    for(int i = n_A + 1; i <= n_B; i++){
        tb[i][0] = rand() % 100 - 50;//randomly generate the left points
        tb[i][1] = rand() % 100 - 50;
    }
    return;
}
#endif
```
+ the main programme:
``` C
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"tester.h"
struct Node{
    int pos_A;
    int pos_B;
    struct Node *child;
    struct Node *brother;
};
clock_t start, stop;
double duration, total_time;
int flag[1001][1001];
double a[1001][2], b[1001][2];
int output[1001];
Info stack[1001];
int table[1001][1001];//create table
int p_stack = 0;//pointer for the stack
typedef struct Node * TreeNode;
int cnt = 0;
int match(Info n1, Info n2, Info n3);//calculate the angle and the scale of the same lines to judge whether it's a possible match
void tree_dfs(Info *selected, int p, int pos_A, int pos_B, int n_A, int n_B, FILE *fpout);//the forest to enumerate all the possible match
Info find_max(int t[][1001], int line, int n_B, int st);//find the current maximum in the table
Info select[1001];
void Initialize_table(int n_A, int n_B){//Initialize the voting table to be all 0
    for(int i = 1; i <= n_A; i++){
        for(int j = 1; j <= n_B; j++)
            table[i][j] = 0;
    }
}
int main (){
    int m, n, flag = 0, type;
    int ticks, k = 1;
    TreeNode r = NULL;
    FILE *fpout, *fpvote;
    fpout = fopen("out_tree.txt", "w+");//open a file to store the paths in the tree/forest
    fpvote = fopen("voting table.txt", "w+");//open a file to store the voting table
    printf("select the testing method:(0 for auto, 1 for type)");
    scanf("%d", &type);
    printf("Input the number of points in A and B:");//prepare for input
    scanf("%d %d", &m, &n);
    if(type == 0){
        printf("whether rotate(0no, 1yes):");//ask whether to rotate, 1 represent yes
        scanf("%d", &flag);
    }
    printf("Input running times(k):");//ask the iteration of the program
    scanf("%d", &k);
    if(type == 0)//if auto, automaticly generate
        generate_tester(m, n, a, b, flag);//generating the test polygons
    else{//if type, type in by hand
        for(int i = 1; i <= m; i++){
            scanf("%lf %lf", &a[i][0], &a[i][1]);
        }
        for(int i = 1; i <= n; i++){
            scanf("%lf %lf", &b[i][0], &b[i][1]);
        }
    }
    start = clock();//start count
    for(int i = 1; i <= k; i++){//run k1 times
        Initialize_table(m, n);
        tree_dfs(select, 0, 0, 0, m, n, fpout);
    }
    stop = clock();//stop count
    ticks = (stop - start);
    total_time = (double)(stop - start)/CLK_TCK;
    duration = (double)(total_time / k);
    Info tmp;
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            fprintf(fpvote, "%d ", table[i][j]);//write the voting result
        }
        fprintf(fpvote, "\n");
    }
    for(int i = 1; i <= m; i++){//out put the best matches
        tmp = find_max(table, i, n, output[i - 1]);//find max number of vote for this A
        output[tmp.pos_A] = tmp.pos_B;//store position of B
    }
    for(int i = 1; i <= m; i++){
        printf("(%d,%d):A(%2.2lf,%2.2lf) B(%2.2lf,%2.2lf)\n", i, output[i], a[i][0], a[i][1], b[i][0], b[i][1]);//print the answer
    }
    printf("iterations = %d\nticks = %d\ntotal time = %lfs\nduration = %.9lfs\n", k, ticks, total_time, duration);//print the information of the runtime
    fclose(fpout);
    fclose(fpvote);//close the files
    return 0;
} 

int match(Info n1, Info n2, Info n3){//calculate the angle and the scale of the same lines to judge whether it's a possible match
    double p1, p2, angle1, angle2;
    double ma1, ma2, ma3, mb1, mb2, mb3;
    ma1 = sqrt((a[n1.pos_A][1] - a[n2.pos_A][1]) * (a[n1.pos_A][1] - a[n2.pos_A][1]) + (a[n1.pos_A][0] - a[n2.pos_A][0]) * (a[n1.pos_A][0] - a[n2.pos_A][0]));//calculate side 1 of A
    mb1 = sqrt((b[n1.pos_B][1] - b[n2.pos_B][1]) * (b[n1.pos_B][1] - b[n2.pos_B][1]) + (b[n1.pos_B][0] - b[n2.pos_B][0]) * (b[n1.pos_B][0] - b[n2.pos_B][0]));//calculate side 1 of B
    ma2 = sqrt((a[n3.pos_A][1] - a[n2.pos_A][1]) * (a[n3.pos_A][1] - a[n2.pos_A][1]) + (a[n3.pos_A][0] - a[n2.pos_A][0]) * (a[n3.pos_A][0] - a[n2.pos_A][0]));//calculate side 2 of A
    mb2 = sqrt((b[n3.pos_B][1] - b[n2.pos_B][1]) * (b[n3.pos_B][1] - b[n2.pos_B][1]) + (b[n3.pos_B][0] - b[n2.pos_B][0]) * (b[n3.pos_B][0] - b[n2.pos_B][0]));//calculate side 2 of B
    ma3 = sqrt((a[n3.pos_A][1] - a[n1.pos_A][1]) * (a[n3.pos_A][1] - a[n1.pos_A][1]) + (a[n3.pos_A][0] - a[n1.pos_A][0]) * (a[n3.pos_A][0] - a[n1.pos_A][0]));//calculate side 3 of A
    mb3 = sqrt((b[n3.pos_B][1] - b[n1.pos_B][1]) * (b[n3.pos_B][1] - b[n1.pos_B][1]) + (b[n3.pos_B][0] - b[n1.pos_B][0]) * (b[n3.pos_B][0] - b[n1.pos_B][0]));//calculate side 3 of B
    p1 = ma1 / mb1;//the proportion between side 1 in A and B
    p2 = ma2 / mb2;//the proportion between side 2 in A and B
    angle1 = acos((ma1 * ma1 + ma2 * ma2 - ma3 * ma3) / (2 * ma1 * ma2));//The Law of Cosines to calculate angle between side 1 and 2 in A
    angle2 = acos((mb1 * mb1 + mb2 * mb2 - mb3 * mb3) / (2 * mb1 * mb2));//The Law of Cosines to calculate angle between side 1 and 2 in B
    if(fabs(p1 - p2) < 0.01 && fabs(angle1 - angle2) < 0.01)
        return 1;//simular return 1
    else
        return 0;//not simular return 0
}
void tree_dfs(Info *selected, int p, int pos_A, int pos_B, int n_A, int n_B, FILE *fpout){
    int f = 0;
    if(p == n_A){//stack is full, start voting, and then pop all the
        for(int i = 1; i <= p; i++){
            table[selected[i].pos_A][selected[i].pos_B]++;//vote all the match in the path
        }
        p--;//pop the last one match to enumerate the next possible match
        return;
    }
    for(int i = pos_A + 1; i <= n_A; i++){//enumerate A
        f = 0;//f = 0 represent going on this loop
        for(int k = 1; k <= p; k++){
            if(selected[k].pos_A >= i || p != (i - 1)){//if this point in A has existed or it's not ascending for A
                f = 1;//if so, skip this A
                break;
            }
        }
        if(f == 1)//skip this A
            continue;
        for(int j = pos_B + 1; j <= n_B; j++){//enumerate point in B
            f = 0;
            for(int k = 1; k <= p; k++){
                if(selected[k].pos_B >= j){//if this point in B is not ascending
                    f = 1;
                    break;
                }
            }
            if(f == 1)//skip this B
                continue;
            p++;//if A and B is possible at present, prepare for push
            selected[p].pos_A = i;//push the horizontal coordinate
            selected[p].pos_B = j;//push the vertical coordinate
            for(int t = 1; t <= p; t++)
                fprintf(fpout, "(%d,%d)", selected[t].pos_A, selected[t].pos_B);
            fprintf(fpout, "\n");
            if(p >= 3){//if 3 matches already exists, judge if they are similar
                if(match(selected[p - 2], selected[p - 1], selected[p]) == 0){//if not similar, cut the path and change to another child of the parent
                    selected[p].pos_A = 0;
                    selected[p].pos_B = 0;
                    p--;//pop the last match
                    continue;//skip this B to enumerate its "brother"
                }
            }
            tree_dfs(selected, p, i, j, n_A, n_B, fpout);//recursively enumerate
            p--;//pop the no use match
        }
    }
    return;
}

Info find_max(int t[][1001], int line, int n_B, int st){//find the current maximum in the table
    int max = -1;
    Info ans;
    // for(int i = 1; i <= n_A; i++){
        for(int j = st + 1; j <= n_B; j++){
            if(t[line][j] > max){//record the (A,B) match when there is a larger voting
                max = t[line][j];
                ans.pos_A = line;
                ans.pos_B = j;
            }
        }
    // }
    t[line][ans.pos_B] = 0;//set this match to 0 to prevent from selecting it again
    return ans;
}
```

# Declaration
+ ***I hereby declare that all the work done in this project titled "Lab1 Report" is of my independent effort.***
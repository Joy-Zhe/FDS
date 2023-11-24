# Chapter 1: Introduction
### Problem description：
+ Give an $N\times N$ integer matrix $(a_{ij})_{N\times N}$, find the maximum submatrix sum. 
+ **p.s.:** the maximum submatrix sum means the sum of the elements in this submatrix is the largest among all the submatrices
+ If the maximum sum is negative, set the maximum sum to 0.
+ Deal with the problem with $O(N^6)$, $O(N^4)$ Algorithm and an optimized algorithm.
# Chapter 2: Algorithm Specification
#### the judging programme
+ ***generation:*** 
``` 
Procedure Generation(n:integer, m:2-dimension array)
	var i, j:integer
	for i:=0 to n-1 do
	begin 
		for j:=0 to n-1 do
		begin	
			m[i][j] = an integer in [-50, 49]
		end
	end 
```
+ ***testing***:
+ **the way to confirm the program:** the matrix will be printed, by compare the 3 outputs, if they have all the same `max` as the $N^6$ one, the answer should be correct ; And because the original matrix is printed on the screen, so it's also possible to confirm the answer by calculate the submatrix.
```
Procedure Test()
	start:=the start time of the test process
	for i:=1 to k do
	begin 
		run one of the algorithm function
	end
	end:=the end time of the test process
	print the information
```
1) the $O(N^6)$ algorithm
+ **Summary:** 
	+ enumerate the start point of the submatrix, and then enumerate the row span and the column span of the submatrix, finally use 2 loops to calculate the sum. 
	+ compare all the submatrices and find the largest one
```
Procedure N6algorithm(n:integer, m:2-dimension array)
	var i, j, k, l, r, c, tmp_sum, ans:integer
	tmp_sum:=0
	ans:=0
	for i, enumerate the start point do
	begin
		for k as the submatrix's row length do
		begin
			for l as the submatrix's column length do
			tmp_sum:=0
			begin
				for r,c run the position of element in submatrix do
				begin	
					tmp_sum:=tmp_sum+m[r][c]
				end
				compare ans with tmp_ans
				if find a larger sum
					update
			end
		end
	end		
```
2) the $O(N^4)$ algorithm
+ **Summary:**
	+ **preprocess:**  make element `m[i][j]` be the sum of the submatrix from `m[0][0]` to `m[i][j]`
	+ enumerate the start point and the end point, calculate the sum of the submatrix with the *Principle of inclusion-exclusion*, compare the sum with the ans each time to find the maximum.
``` 
Procedure N4algorithm(n:integer, m:2-dimension array)
	var i, j, k, l, tmp_sum, ans:integer
	tmp_sum:=0
	ans:=0
	for i,j enumerate all the point do
	begin
		m[i][j]:=the sum of m[i][0] to m[i][j]
	end
	for i,j enumerate all the point do
	begin	
		m[j][i]:=the sum of m[0][i] to m[j][i]
	end
	for i,j enumerate the start point of the submatrix do
	begin
		for k,l enumerate the end point of the submatrix do
		begin
			set tmp_sum to 0
			begin
				tmp_sum:=the sum of the submatrix 
				compare ans with tmp_sum
				if find a larger sum
					update
			end
		end
	end	
```

# Chapter 3: Testing Results
+ put in 4 numbers: $N$, $k1$, $k2$, and $k3$.
+ $k1$, $k2$, and $k3$ are the different Iteration time determined by the tester.
+ the original matrix is first printed
+ the max and position of maximum is printed at the front of the output 

| |N|5|10|30|50|80|100|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|$O(N^6)$|Iterations(K)|$10^7$|$10^5$|$10^2$|10|1|1|
| |Ticks|27125|8099|3188|5695|8958|32655
||Total Time(sec)|27.125|8.099|3.188|5.695|8.792|32655
||Duration(sec)|$2.712\times 10^{-6}$|$8.099\times 10^{-5}$|$0.03188$|0.5695|8.958|32.655
|$O(N^4)$|Iterations(K)|$10^7$|$10^5$|$10^3$|100|100|10|
| |Ticks|8277|924|638|464|2817|732|
||Total Time(sec)|8.277|0.924|0.638|0.464|2.984|0.782|
||Duration(sec)|$8.28\times 10^{-7}$|$9.24\times 10^{-6}$|$6.38\times 10^{-4}$|0.00464|0.02984|0.0732|
| | |![1](D:\code\Learning\DS\lab\lab1\pic\5f.png)|![1](D:\code\Learning\DS\lab\lab1\pic\10f.png)|![1](D:\code\Learning\DS\lab\lab1\pic\30f.png)|![1](D:\code\Learning\DS\lab\lab1\pic\50f1.png)|![1](D:\code\Learning\DS\lab\lab1\pic\80f0.png)|![1](D:\code\Learning\DS\lab\lab1\pic\100f0.png)|
+ ***The Graph for the runtimes:***
![graph](D:\code\Learning\DS\lab\lab1\pic\2.png)
# Chapter 4: Analysis and Comments
1) for the $O(N^6)$ algorithm:
	+ the time complexity: 
		1) to enumerate the start point, it takes 2 n-loops(one for row position, one for column position)
		2) to enumerate the length and the height of the submatrix, it takes 2 loops(one for length, one for height)
		3) to calculate the sum of the submatrix, it also takes 2 loops to add element in two different directions.
		4) because all the loops are nested, the total time comlexity is $O(N^6)$
	+ the space complexity:
		+ use an $N\times N$ 2-dimension array, thus $O(N^2)$
2) for the $O(N^4)$ algorithm:
	+ the time complexity: 
		+ preprocess: 2 n-loops for each direction, it's $O(N^2)$
		1) to enumerate the start point, it takes 2 n-loops(one for row position, one for column position)
		2) to enumerate the end point of the submatrix, it takes 2 n-loops
		3) because the loops 1,2 are nested, and it has a larger time complexity($O(N^4)$) than the preprocess step. Thus, the total time comlexity is $O(N^4)$
	+ the space complexity:
		+ use an $N\times N$ 2-dimension array, thus $O(N^2)$
+ During the lab, I learnt how to adjust the iteration times to adjust the ticks to decrease the inaccurancy. And in order to write a convenient testing programme, I adjust for many times to make the input and the output to be easy to use. This lab increased my understand for optimizing.

# Chapter 5: An optimized algorithm(bonus)
+ the $O(N^3)$ algorithm
### algorithm specification
+ **Summary:**
	+ **preprocess:** manipulate each row, make the $j^{th}$ element in row $i$ be the sum of `m[i][0]` to `m[i][j]` to decrease a n-loop in the latter calculation
	+ enumerate the length of the submatrix from column $i$ to column $j$(such as $[1,3]$), then calculate the sum between $[i,j]$ in this row 
	+ then find the maximum sum in the column direction by add the sum to the *tmp_sum* first, and then if the *tmp_sum* is still positive, keep on adding, else if it become negative, it will only decrease the sum of the next number, so reset it to 0 to find a new submatrix. If the *tmp_sum* is larger than *ans*, update *ans*
``` 
Procedure N3algorithm(n:integer, m:2-dimension array)
	var i, j, k, m_tmp, tmp_sum, ans:integer
	tmp_sum:=0
	ans:=0
	for i in the main matrix's row do
	begin
		for j in row i's columns do
		begin	
			m[i][j]:=m[i][j]+m[i][j-1]
		end	
	end
	for i enumerate the start point in row do
	begin
		for j enumerate the end point in row do
		begin
			tmp_sum:=0
			for k run all the rows do
			begin
				m_tmp:=the sum from m[k][i] to m[k][j]
				tmp_sum:=tmp_sum+m_tmp;
				if tmp_sum>ans
					update ans
				if tmp_sum<0
					tmp_sum:=0
			end
		end
	end	
```
### Testing results
+ put in 4 numbers: $N$, $k1$, $k2$, and $k3$.
+ $k1$, $k2$, and $k3$ are the different Iteration time determined by the tester.

| |N|5|10|30|50|80|100|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|$O(N^6)$|Iterations(K)|$10^6$|$10^5$|$10^2$|10|1|1|
| |Ticks|2539|8864|3226|5885|8907|32754
||Total Time(sec)|2.539|8.864|3.226|5.885|8.907|32.754
||Duration(sec)|$2.539\times 10^{-8}$|$8.864\times 10^{-5}$|$3.226\times 10^{-2}$|0.5885|8.907|32.754
|$O(N^4)$|Iterations(K)|$10^6$|$10^5$|$10^3$|$10^3$|100|10|
| |Ticks|717|1076|658|4757|2963|729|
||Total Time(sec)|0.717|1.076|0.658|4.757|2.963|0.729|
||Duration(sec)|$7.17\times 10^{-7}$|$1.076\times 10^{-5}$|$6.58\times 10^{-4}$|0.004757|0.02963|0.0729|
|$O(N^3)$|Iterations(K)|$10^6$|$10^6$|$10^4$|$10^4$|$10^3$|$10^3$|
| |Ticks|275|2012|431|2315|1022|1631|
||Total Time(sec)|0.275|2.012|0.431|2.315|1.022|1.631|
||Duration(sec)|$2.75\times 10^{-7}$|$2.012\times 10^{-6}$|$4.31\times 10^{-5}$|$2.315\times 10^{-4}$|$1.022\times 10^{-3}$|0.001631|
| | |![1](D:\code\Learning\DS\lab\lab1\pic\53f.png)|![1](D:\code\Learning\DS\lab\lab1\pic\103f.png)|![1](D:\code\Learning\DS\lab\lab1\pic\303f.png)|![1](D:\code\Learning\DS\lab\lab1\pic\503f.png)|![1](D:\code\Learning\DS\lab\lab1\pic\803f.png)|![1](D:\code\Learning\DS\lab\lab1\pic\1003f.png)|
+ ***The Graph for the runtimes:***
![graph](D:\code\Learning\DS\lab\lab1\pic\3.png)
### Analysis
+ the time complexity:
	+ the preprocess: use 2 nested n-loops to get a "sum up" matrix in each row, it's $O(N^2)$
	+ enumerate the start point and the end point in each line, that's $O(N^2)$, and because of the preprocess, get the sum will be $O(1)$; and to enumerate the sum in the column direction, it takes another loop, thus, the total time coplexity comes to $O(N^3)$
+ the space complexity: same as the former 2 algorithm, $O(N^2)$

# Appendix: Source Code in C
``` C
#include<time.h>
#include<stdio.h>
#include<stdlib.h>  

clock_t start, stop;
double duration, total_time;
typedef struct {//the structure is used to store the information of the maximum submatrix
    int max;//the value of the sum
    int r_start;//the start row
    int c_start;//the start column
    int r_end;//the end row
    int c_end;//the end column
}save_ans;
save_ans max_subm;

void generate_test(int n, int m[][n]){//generate the testing matrix
    srand(time(0));//randanmize the seed
    printf("the matrix is:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = (int)(rand() % 100 - 50);//the number will be [-50,49]
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
    return;
}

int N6algorithm(int n, int m[][n]){
    int tmp_sum = 0;//record the sum of a single submatrix
    int ans = 0;//record the present maximum sum
    for(int i = 0; i < n; i++){//the row
        for(int j = 0; j < n; j++){//the column
            for(int k = 0; (i + k) < n; k++){//the row length
                for(int l = 0; (j + l) < n; l++){//the column length
                    tmp_sum = 0;
                    for(int r = i; r <= i + k; r++){
                        for(int c = j; c <= j + l; c++)
                            tmp_sum += m[r][c];
                    }
                    if(ans < tmp_sum){//ans<tmp_sum, update the maximum matrix
                        ans = tmp_sum;
                        max_subm.max = ans;
                        max_subm.r_start = i;
                        max_subm.c_start = j;
                        max_subm.r_end = i + k;
                        max_subm.c_end = j + l;
                    }
                }
            }
        }
    }
    return ans;
}

  

int N4algorithm(int n, int m[][n]){
    int tmp_sum = 0;//record the sum of a single submatrix
    int ans = 0;//record the present maximum sum
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n; j++){//make the j^th element be the sum of all the former elements in its row
            m[i][j] = m[i][j] + m[i][j - 1];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n; j++){//make the j^th element be the sum of all the former elements in its column
            m[j][i] = m[j][i] + m[j - 1][i];
        }
    }
    for(int i = 0; i < n; i++){//start point's row position
        for(int j = 0; j < n; j++){//start point's column position
            for(int k = n - 1; k >= i; k--){//end point's row position
                for(int l = n - 1; l >= j; l--){//end point's column position
                    //in 4 different conditions, calculate the sum of the submatrix from (i,j) to (k, l)
                    if(i && j)//i and j are all not in the corner
                        tmp_sum = m[k][l] - m[i - 1][l] - m[k][j - 1] + m[i - 1][j - 1];//minus 2 parts and add back the part decreased for 2 times
                    else if(!i && j)//i is in the corner
                        tmp_sum = m[k][l] - m[k][j - 1];
                    else if(i && !j)//j is in the corner
                        tmp_sum = m[k][l] - m[i - 1][l];
                    else if(!i && !j)//start from the upleft corner
                        tmp_sum = m[k][l];
                    if(ans < tmp_sum){//ans<tmp_sum, update the maximum matrix
                        ans = tmp_sum;
                        max_subm.max = ans;
                        max_subm.r_start = i;
                        max_subm.c_start = j;
                        max_subm.r_end = k;
                        max_subm.c_end = l;
                    }
                }
            }
        }
    }
    return ans;
}

int N3algorithm(int n, int m[][n]){
    int tmp_sum = 0;
    int m_tmp = 0;
    int ans = 0;
    for(int i = 0; i < n; i++){//preprocess each row's element
        for(int j = 1; j < n; j++){
            m[i][j] = m[i][j] + m[i][j - 1];//make the jth one be the sum of [0,j]
        }
    }
    int r_st_tmp = 0;
    for(int i = 0; i < n; i++){//head
        for(int j = i; j < n; j++){//tail
            tmp_sum = 0;
            r_st_tmp = 0;
            for(int k = 0; k < n; k++){//get the maximum by only save the one that enlarge the sum
                if(i)
                    m_tmp = m[k][j] - m[k][i - 1];//get the sum from m[k][i] to m[k][j]
                else
                    m_tmp = m[k][j];//get the sum from m[k][0] to m[k][j]
                tmp_sum += m_tmp;//add to tmp_sum
                if(ans < tmp_sum){//ans<tmp_sum, update the maximum matrix
                    ans = tmp_sum;
                    max_subm.max = ans;
                    max_subm.r_start = r_st_tmp;
                    max_subm.c_start = i;
                    max_subm.r_end = k;
                    max_subm.c_end = j;
                }
                if(tmp_sum < 0){//tmp_sum<0, will decrease the next number, reset to 0
                    tmp_sum = 0;
                    r_st_tmp = k + 1;
                }
            }
        }
    }
    return ans;
}
  
int main (){
    int n, r, c, ans, k1, k2, k3, ticks;
    //input part
    printf("Input N:");
    scanf("%d", &n);
    printf("Input iteration times k1:");
    scanf("%d", &k1);
    printf("Input iteration times k2:");
    scanf("%d", &k2);
    printf("Input iteration times k3:");
    scanf("%d", &k3);//input n and 3 iteration times
    int matrix[n][n];//original matrix
    int m_tmp[n][n];//saved matrix
    //matrix part
    generate_test(n, matrix);//generate and print matrix
    //N^6 part
    start = clock();
    for(int i = 1; i <= k1; i++)//run k1 times
        ans = N6algorithm(n, matrix);
    stop = clock();
    ticks = (stop - start);
    total_time = (double)(stop - start)/CLK_TCK;
    duration = (double)(total_time/k1);
    printf("N^6Algorithm\nmax = %d\nFrom (%d,%d) to (%d,%d)\n", max_subm.max, max_subm.r_start, max_subm.c_start, max_subm.r_end, max_subm.c_end);//print the information of the answer matrix
    printf("iterations = %d\nticks = %d\ntotal time = %lfs\nduration = %.9lfs\n", k1, ticks, total_time, duration);//print the information of the runtime
    //N^4 part
    start = clock();
    for(int t = 1; t <= k2; t++){//run k2 times
        for(int i = 0; i < n; i++){//save the matrix because the matrix will change in this algorithm
            for(int j = 0; j < n; j++)
                m_tmp[i][j] = matrix[i][j];
        }
        ans = N4algorithm(n, m_tmp);
    }
    stop = clock();
    ticks = (stop - start);
    total_time = (double)(stop - start)/CLK_TCK;
    duration = (double)(total_time/k2);
    printf("N^4Algorithm\nmax = %d\nFrom (%d,%d) to (%d,%d)\n", max_subm.max, max_subm.r_start, max_subm.c_start, max_subm.r_end, max_subm.c_end);//print the information of the answer matrix
    printf("iterations = %d\nticks = %d\ntotal time = %lfs\nduration = %.9lfs\n", k2, ticks, total_time, duration);//print the information of the runtime
    //N^3 part
    start = clock();
    for(int t = 1; t <= k3; t++){//run k3 times
        for(int i = 0; i < n; i++){//save the matrix because the matrix will change in this algorithm
            for(int j = 0; j < n; j++)
                m_tmp[i][j] = matrix[i][j];
        }
        ans = N3algorithm(n, m_tmp);
    }
    stop = clock();
    ticks = (stop - start);
    total_time = (double)(stop - start)/CLK_TCK;
    duration = (double)(total_time/k3);
    printf("N^3Algorithm\nmax = %d\nFrom (%d,%d) to (%d,%d)\n", max_subm.max, max_subm.r_start, max_subm.c_start, max_subm.r_end, max_subm.c_end);//print the information of the answer matrix
    printf("iterations = %d\nticks = %d\ntotal time = %lfs\nduration = %.9lfs\n", k3, ticks, total_time, duration);//print the information of the runtime
    return 0;
}
```

# Declaration
+ ***I hereby declare that all the work done in this project titled "Lab1 Report" is of my independent effort.***
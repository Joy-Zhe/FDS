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
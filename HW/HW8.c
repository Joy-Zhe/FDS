#include<stdio.h>
int matrix[201][201];
int flag[201];
int main (){
    int n, m, n_cycle;
    int in, out;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        scanf("%d %d", &in, &out);
        matrix[in][out] = 1;
        matrix[out][in] = 1;
    }
    scanf("%d", &n_cycle);
    for(int i = 1; i <= n_cycle; i++){
        int tmp_n, former, latter, first;
        int f = 1;
        scanf("%d", &tmp_n);
        scanf("%d", &first);
        former = first;
        flag[first] = 1;
        for(int j = 2; j <= tmp_n; j++){
            scanf("%d", &latter);
            flag[latter] = 1;
            if(matrix[former][latter] == 0)
                f = 0;
            former = latter;
        }
        if((former != first) /*|| (tmp_n != (n + 1))*/)
            f = 0;
        for(int j = 1; j <= n; j++){
            if(flag[j] == 0){
                f = 0;
                break;
            }
        }
        if(f == 1)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
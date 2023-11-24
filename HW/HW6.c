#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int ans[2001];
int input[2001];
int find_Lsum(int n){//计算左子树的元素个数
    if(n <= 1)
        return 0;
    if(n == 2)
        return 1;
    int level = log2(n);
    int last = n - (pow(2, level) - 1);
    if(level == 0)
        return 1;
    int last_L;
    if(last >= pow(2, level - 1)){
        last_L = pow(2, level - 1);
    }else
        last_L = last;
    return (last_L + (pow(2, level) - 1) / 2);
}
int cmp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}
void output(int *out, int p, int *in, int l, int r, int max){
    if(l > r || p > max || l < 0 || r < 0)
        return;
    int cnt_L, cnt_R;
    int tar;
    cnt_L = find_Lsum(r - l + 1);
    cnt_R = r - l - cnt_L;
    tar = l + cnt_L;
    // printf("l:%d r:%d %d:%d:%d\n", l, r, tar, cnt_L, cnt_R);
    // for(int i = l; i < tar; i++)
    //     printf("%d ", in[i]);
    // printf("\n");
    ans[p] = in[tar];
    output(out, p * 2, in, l, tar - 1, max);//左子树
    output(out, p * 2 + 1, in, tar + 1, r, max);//右子树
    return;
}
int main (){
    int n, mid;
    int l, r;
    int p = 1;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &input[i]);
    }
    l = 0;
    r = n - 1;
    qsort(input, n, sizeof(int), cmp);
    // for(int i = 0; i < n; i++){
    //     printf("%d ", input[i]);
    // }
    output(ans, 1, input, l, r, n);
    for(int i = 1; i <= n; i++){
        if(i == 1)
            printf("%d", ans[i]);
        else
            printf(" %d", ans[i]);
    }
    return 0;
}
#include<stdio.h>
int stack[1001];
int main (){
    int top = 0;
    int cur = 1;
    int M, N, K, num, ans[1001];//ans = 0 represent no
    scanf("%d %d %d", &M, &N, &K);
    for(int i = 0; i <= K; i++)
        ans[i] = 1;
    for(int i = 0; i < K; i++){
        for(int k = 0; k <= N; k++)
            stack[k] = 0;
        top = 0;
        cur = 1;
        for(int j = 0; j < N; j++){
            scanf("%d", &num);
            if(ans[i] == 0)
                continue;
            if(stack[top] == num){
                stack[top] = 0;
                top--;
            }else{
                while(stack[top] < num && cur <= N){
                    top++;
                    stack[top] = cur;
                    cur++;
                    if(top > M){
                        ans[i] = 0;
                        break;
                    }
                }
                if(stack[top] == num){
                    stack[top] = 0;
                    top--;
                }
            }
        }
        if(top)
            ans[i] = 0;
    }
    for(int i = 0; i < K; i++){
        if(ans[i] == 1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
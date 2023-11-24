#include<stdio.h>
int s1[1001];
char s2[1001];
int judge_ilegal(int n2, char op, int n1);
int main(){
    int n;
    int top1, top2;
    int n1, n2, ans;
    char op;
    scanf("%d", &n);
    top1 = n;
    top2 = n - 1;
    for(int i = 1; i <= n; i++)
        scanf("%d", &s1[i]);
    for(int i = 1; i < n; i++){
        scanf("%c", &s2[i]);
        if(s2[i] != '+' && s2[i] != '-' && s2[i] != '*' && s2[i] != '/')
            i--;
    }
    while(top2){
        n1 = s1[top1];
        top1--;
        n2 = s1[top1];
        top1--;
        op = s2[top2];
        top2--;
        int flag;
        flag = judge_ilegal(n2, op, n1);
        if(!flag){
            printf("ERROR: %d%c%d", n2, op, n1);
            return 0;
        }
        switch (op){
            case '+':
                ans = n2 + n1;
                break;
            case '-':
                ans = n2 - n1;
                break;
            case '*':
                ans = n2 * n1;
                break;
            case '/':
                ans = n2 / n1;
                break;
            default:
                break;
        }
        top1++;
        s1[top1] = ans;
    }
    printf("%d", s1[1]);
    return 0;
}
int judge_ilegal(int n2, char op, int n1){
    if(op == '/' && n1 == 0)
        return 0;
    return 1;
}
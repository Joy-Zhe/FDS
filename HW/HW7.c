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
            int tmp1, tmp2;
            tmp1 = find(num, n1);
            tmp2 = find(num, n2);
            if((tmp1 != n1 && tmp2 != n2) || (tmp1 == n1 && tmp2 == n2))
                num[tmp2] = n1;
            else{
                if(num[n1] == tmp2)
                    num[tmp1] = n2;
                for(int i = 1; i <= n; i++){
                    printf("%d ", num[i]);
                }
                printf("\n");
            }
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
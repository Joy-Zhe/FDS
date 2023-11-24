#include<stdio.h>
struct edge{
    int next_V;
    int dis;
    int next;
}N[5000];
int head[5000], cnt;
void add_edge(int from, int to, int dis){
    cnt++;
    N[cnt].next_V = to;
    N[cnt].dis = dis;
    N[cnt].next = head[from];
    head[from] = cnt;
}
int main (){
    int m, n;
    int from, to, w;
    scanf("%d %d", &m, &n);
    for(int i = 1; i <= n; i++){
        scanf("%d %d %d", &from, &to, &w);
        add_edge(from, to, w);
        add_edge(to, from, w);
    }
    for(int i = 1; i <= cnt; i++)
        printf("N[%d] = %d %d %d\n", i, N[i].next_V, N[i].dis, N[i].next);
    for(int i = 1; i <= m; i++)
        printf("Head[%d] = %d\n", i, head[i]);
    return 0;
}
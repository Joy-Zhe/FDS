#include<stdio.h>
#include<stdlib.h>
struct e{
    int v1, v2;
    int w;
}edges[10001];
typedef struct e * Edge;
int cmp(const void *a, const void *b){
    Edge tmp1 = (Edge)a;
    Edge tmp2 = (Edge)b;
    return (tmp1->w - tmp2->w);
}
int num[10001], ans[10001];//array for union set
int find(int *a, int num);//find root
void union_set(int v1, int v2, int *a);//get union set
int judge_connected(int n);
int adjM[10001][10001];
int adjM_used[10001][10001];
int path[10001], able[10001], f[10001];
int update_graph(int st);
int find_circle(int from, int to, int st, int n);
int find_MST(int n, int cnt);
int main (){
    int n, m, cnt = 0, cnt_link = 0, cnt_same = 0;
    int v1, v2, w, min;
    FILE *fin, *fout;
    fin = fopen("data.in", "r");
    fout = fopen("HW10_2.out", "w");
    // scanf("%d %d", &n, &m);
    fscanf(fin, "%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        num[i] = i;
        ans[i] = i;
    }
    for(int i = 1; i <= m; i++){
        fscanf(fin, "%d %d %d", &v1, &v2, &w);
        // scanf("%d %d %d", &v1, &v2, &w);
        adjM[v1][v2] = w;
        adjM[v2][v1] = w;
        edges[cnt].v1 = v1;
        edges[cnt].v2 = v2;
        edges[cnt].w = w;
        union_set(v1, v2, num);
        cnt++;
    }
    for(int i = 1; i <= n; i++){
        if(num[i] == i)
            cnt_link++;
    }
    if(judge_connected(n) == 0){
        // printf("No MST\n%d", cnt_link);
        fprintf(fout, "No MST\n%d", cnt_link);
        return 0;
    }
    qsort(edges, cnt, sizeof(struct e), cmp);
    // for(int i = 0; i < cnt; i++){
    //     printf("%d %d %d\n", edges[i].v1, edges[i].v2, edges[i].w);
    // }
    int flag = 0;
    for(int i = 0; i < cnt; i++)
        able[i] = 1;
    min = find_MST(n, cnt);
    for(int i = 0; i < cnt; i++)
        f[i] = path[i];
    int tmp_min;        
    for(int j = 0; j < cnt; j++)
        able[j] = 1;
    for(int i = 0; i < cnt; i++){

        if(f[i]){
            able[i] = 0;
            tmp_min = find_MST(n, cnt);
            if(tmp_min == min){
                flag = 1;
                break;
            }
            able[i] = 1;
        }
    }
    if(judge_connected(n))
        // printf("%d\n", min);
        fprintf(fout, "%d\n", min);
    if(flag)
        // printf("No");
        fprintf(fout, "No");
    else    
        // printf("Yes");
        fprintf(fout, "Yes");
    return 0;
}
int judge_connected(int n){
    int f;
    for(int i = 1; i <= n; i++){
        f = 0;
        for(int j = 1; j <= n; j++){
            if(adjM[i][j]){
                f = 1;
                break;
            }
        }
        if(f == 0)
            return 0;
    }
    return 1;
}
int find_circle(int from, int to, int st, int n){//find a circle in the used edges
    if(find(ans, from) == find(ans, to))
        return 1;
    return 0;
}
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
void union_set(int v1, int v2, int *a){
    int tmp1, tmp2;
    tmp1 = find(a, v1);
    tmp2 = find(a, v2);
    a[tmp2] = tmp1;
    return;
}
int find_MST(int n, int cnt){
    int cnt_link = 0;
    int cnt_ans = 0, ans_L = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            adjM_used[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; i++){
        ans[i] = i;
    }
    for(int i = 0; i < cnt; i++){
        if(find_circle(edges[i].v1, edges[i].v2, edges[i].v1, n) == 0 && able[i] == 1){
            adjM_used[edges[i].v1][edges[i].v2] = edges[i].w;
            adjM_used[edges[i].v2][edges[i].v1] = edges[i].w;
            cnt_ans++;
            path[i] = 1;
            union_set(edges[i].v1, edges[i].v2, ans);
            ans_L += edges[i].w;
        }
        if(cnt_ans == (n - 1))
            break;
    }
    return ans_L;
}
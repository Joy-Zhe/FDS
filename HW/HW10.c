#include<stdio.h>
#define INF 99999999
int adjM[17576][17576];
int path[17576];
int update_graph(int st, int flow, int ed){
    int minf_total, minf;
    if(st == ed)
        return flow;
    path[st] = 1;//runed path
    for(int i = 0; i <= 17575; i++){
        if(path[i] == 0 && adjM[st][i]){
            if(adjM[st][i] > flow)//find a present min flow
                minf = flow;
            else
                minf = adjM[st][i];
            minf_total = update_graph(i, minf, ed);//find the min flow, recursively
            if(minf_total){
                adjM[st][i] -= minf_total;//update the original graph
                adjM[i][st] += minf_total;//update the back path
                return minf_total;
            }
        }
    }
    return 0;
}
void reset_path(){
    for(int i = 0; i <= 17575; i++)
        path[i] = 0;
}
int main (){
    char st[4], ed[4];
    int from = 0, to = 0;
    int n, dis, to_ed, to_st, ans = 0;
    int flow;
    scanf("%s %s %d", st, ed, &n);
    to_st = (st[0] - 'A') * 26 * 26 + (st[1] - 'A') * 26 + (st[2] - 'A');
    to_ed = (ed[0] - 'A') * 26 * 26 + (ed[1] - 'A') * 26 + (ed[2] - 'A');
    for(int i = 1; i <= n; i++){
        scanf("%s %s %d", st, ed, &dis);
        from = (st[0] - 'A') * 26 * 26 + (st[1] - 'A') * 26 + (st[2] - 'A');//change the letters to base 26 number
        to = (ed[0] - 'A') * 26 * 26 + (ed[1] - 'A') * 26 + (ed[2] - 'A');
        adjM[from][to] = dis;//store original graph
        adjM[to][from] = 0;//store the reserve edge
    }
    while(flow){
        reset_path();
        flow = update_graph(to_st, INF, to_ed);
        ans += flow;
    }
    printf("%d", ans);
    return 0;
}
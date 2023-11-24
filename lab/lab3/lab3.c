#include<stdio.h>
#include<time.h>
#include<windows.h>
#include"data.h"
#include"tester.h"
#define INF 99999999
clock_t start, stop;
double duration, total_time;
int min_path[200001], min2_path[200001];
int min_dis[200001], min2_dis[200001];//min_dis[] record the shortest distance from st to end 
                                    //min2_dis[] record the shortest distance from end to st
int flag_toend[200001], flag_tost[200001];//to judge whether the path have been updated(one for go, one for back)
int find_min(int *min_dis, int *f, int n);//find the next shortest vertex, if not exist, return 0, else return the index of the vertex
struct edge{
    int next_V;//store the vertex this edge go to
    int dis;//store distance
    int next;//store the index of the previous edge connected with the same head
}N[500001];
int head[500001], cnt;
void add_edge(int from, int to, int dis){
    cnt++;//the total number of the node of edges
    N[cnt].next_V = to;//store the vertex this edge connect to
    N[cnt].dis = dis;//store the distance of this edge
    N[cnt].next = head[from];//store the index of the previous edge connected with the same head
    head[from] = cnt;//update the index of the last 'from' with the latest 'cnt'
}

//flag == 1 represent st to end, flag == home represent end to st
void dijkstra(int n, int *f, int *dis, int *path, int flag);

int main (){
    int home, total_edge;
    int pre, next, dis;
    int ticks, k;
    int mode;//choose the testing mode
    int ans_min_2nd = INF, min = INF, ansi = 0, ansj = 0;
    FILE *fpin;
    printf("choose the testing mode(0 for by hand, 1 for auto):");
    scanf("%d", &mode);
    printf("run times:");
    scanf("%d", &k);
    printf("type in the number of vertices and edges:");
    if(mode == 0)
        scanf("%d %d", &home, &total_edge);
    else if(mode == 1){
        scanf("%d %d", &home, &total_edge);
        tester(home, total_edge);
        fpin = fopen("data.in", "r");
        fscanf(fpin, "%d %d", &home, &total_edge);
    }
    //initialize the distance and flag
    for(int i = 1; i <= home; i++){
        min_dis[i] = INF;//set to infinite
        min2_dis[i] = INF;//set to infinite
        flag_toend[i] = 0;
        flag_tost[i] = 0;
        min_path[i] = -1;//set to no path(-1)
        min2_path[i] = -1;//set to no path(-1)
    }
    //initialize the edges
    for(int i = 1; i <= total_edge; i++){
        if(mode == 0)
            scanf("%d %d %d", &pre, &next, &dis);
        if(mode == 1)
            fscanf(fpin, "%d %d %d", &pre, &next, &dis);
        add_edge(pre, next, dis);//add (pre, next) to the edges
        //add_edge(next, pre, dis);//no direction, so add (next, pre) to the edges
    }
    start = clock();
    for(int t = 1; t <= k; t++){
        dijkstra(home, flag_toend, min_dis, min_path, 1);//st to end dijkstra
        dijkstra(home, flag_tost, min2_dis, min2_path, home);//end to st dijkstra
    //------------------------------find the 2nd shortest path-------------------------------
        ans_min_2nd = INF;
        min = INF;
        ansi = 0;
        ansj = 0;
        for(int i = 1; i <= home; i++){
            for(int j = head[i]; j; j = N[j].next){
                int next_V = N[j].next_V, w = N[j].dis;
                if(((min_dis[i] + min2_dis[next_V] + w) > min_dis[home] && ((min_dis[i] + min2_dis[next_V] + w) < ans_min_2nd))){
                    ans_min_2nd = min_dis[i] + min2_dis[next_V] + w;
                    ansi = i;
                    ansj = next_V;
                }
            }
        }
    //---------------------------------------------------------------------------------------
    }
    stop = clock();
    ticks = (stop - start);
    total_time = (double)(stop - start)/CLK_TCK;
    duration = (double)(total_time/k);
    printf("iterations = %d\nticks = %d\ntotal time = %lfs\nduration = %.9lfs\n", k, ticks, total_time, duration);//print the information of the runtime
    //---------------------------------------output part--------------------------------------
    int ans_path[5001], pos = 0;
    for(int i = ansi; i != -1; i = min_path[i]){
        pos++;
        ans_path[pos] = i;
    }//push the former part path into the stack
    printf("%d", ans_min_2nd);
    while(pos){
        printf(" %d", ans_path[pos]);
        pos--;
    }
    for(int i = ansj; i != -1; i = min2_path[i]){
        printf(" %d", i);
    }
    //----------------------------------------------------------------------------------------
    if(mode == 1)
        fclose(fpin);
    //system("pause");
    return 0;
} 
int find_min(int *min_dis, int *f, int n){//find the next shortest vertex, if not exist, return 0, else return the index of the vertex
    int min = INF, next = 0;
    for(int i = 1; i <= n; i++){
        if(min > min_dis[i] && f[i] == 0){//ensure the vertex hasn't been enumerated
            min = min_dis[i];
            next = i;
        }
    }
    return next;
}
void dijkstra(int n, int *f, int *dis, int *path, int flag){//flag == 1 represent st to end, flag == home represent end to st
    for(int i = 1; i <= n; i++) {
        dis[i] = INF;
        f[i] = 0;    
    }
    int v_next;
    dis[flag] = 0;//initialize the distance for itself
    while(find_min(dis, f, n)){
        v_next = find_min(dis, f, n);//find the nearest vertex
        if(v_next == 0)//not found(all passed), quit
            break;
        f[v_next] = 1;
        for(int j = head[v_next]; j; j = N[j].next){
            int next = N[j].next_V, w = N[j].dis;
            if((dis[v_next] + w) < dis[next]){//find a shorter path
                dis[next] = dis[v_next] + w;
                path[next] = v_next;
            }
        }
    }
    return;
}
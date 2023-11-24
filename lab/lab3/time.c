#include<stdio.h>
#include<windows.h>
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
}N[500001], Nforback[500001];// the real graph and the virtual one
int head[500001], head_virtual[500001], cnt, cnt_v;
void add_edge(int from, int to, int dis){
    cnt++;//the total number of the node of edges
    N[cnt].next_V = to;//store the vertex this edge connect to
    N[cnt].dis = dis;//store the distance of this edge
    N[cnt].next = head[from];//store the index of the previous edge connected with the same head
    head[from] = cnt;//update the index of the last 'from' with the latest 'cnt'
}
void add_virtualedge(int from, int to, int dis){
    cnt_v++;//the total number of the node of edges
    Nforback[cnt].next_V = to;//store the vertex this edge connect to
    Nforback[cnt].dis = dis;//store the distance of this edge
    Nforback[cnt].next = head_virtual[from];//store the index of the previous edge connected with the same head
    head_virtual[from] = cnt_v;//update the index of the last 'from' with the latest 'cnt'
}
int back_judge(int x, int y){//for (x,y) in the virtual graph, judge if (y,x) is possible in the real graph 
    int next;
    for(int i = head[y]; i; i = N[i].next){
        next = N[i].next_V;
        if(next == x)
            return 1;
    }
    return 0;
}
//flag == 1 represent st to end, flag == home represent end to st
void dijkstra(int n, int *f, int *dis, int *path, int flag);
void dijkstra_back(int n, int *f, int *dis, int *path, int flag);
int main (){
    int ticks, k;
    int home, total_edge;
    int pre, next, dis;
    int mode;//choose the testing mode
    int ans_min_2nd = INF, min = INF, ansi = 0, ansj = 0;
    FILE *fpin;
    printf("choose the testing mode(0 for by hand, 1 for auto):");
    scanf("%d", &mode);
    printf("run times:");
    scanf("%d", &k);
    printf("type in the number of vertices and edges:");
    if(mode == 0)//type by hand
        scanf("%d %d", &home, &total_edge);
    else if(mode == 1){//generate by the tester
        scanf("%d %d", &home, &total_edge);
        tester(home, total_edge);
        fpin = fopen("data.in", "r");//open a file to store the input
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
        add_virtualedge(pre, next, dis);// create a virtual graph with no direction
        add_virtualedge(next, pre, dis);
    }
    start = clock();
    for(int t = 1; t <= k; t++){
        dijkstra(home, flag_toend, min_dis, min_path, 1);//st to end dijkstra
        dijkstra_back(home, flag_tost, min2_dis, min2_path, home);//end to st dijkstra
    //------------------------------find the 2nd shortest path-------------------------------
        ans_min_2nd = INF;
        min = INF;
        ansi = 0;
        ansj = 0;
        for(int i = 1; i <= home; i++){
            for(int j = head[i]; j; j = N[j].next){
                int next_V = N[j].next_V, w = N[j].dis;
                if(((min_dis[i] + min2_dis[next_V] + w) > min_dis[home] && ((min_dis[i] + min2_dis[next_V] + w) < ans_min_2nd))){//if larger than min and shorter than present min2nd, update
                    ans_min_2nd = min_dis[i] + min2_dis[next_V] + w;
                    ansi = i;
                    ansj = next_V;
                }
            }
        }
    }
    //---------------------------------------------------------------------------------------
    //---------------------------------------output part--------------------------------------
    stop = clock();
    ticks = (stop - start);
    total_time = (double)(stop - start)/CLK_TCK;
    duration = (double)(total_time/k);
    printf("iterations = %d\nticks = %d\ntotal time = %lfs\nduration = %.9lfs\n", k, ticks, total_time, duration);//print the information of the runtime
    int ans_path[5001], pos = 0;
    if(ans_min_2nd == INF){
        printf("no answer!");
        return 0;
    }
    for(int i = ansi; i != -1; i = min_path[i]){
        pos++;
        ans_path[pos] = i;
    }//push the former part path into the stack
    printf("%d", ans_min_2nd);
    while(pos){
        printf(" %d", ans_path[pos]);
        pos--;
    }
    for(int i = ansj; i != -1; i = min2_path[i]){//print the latter ones
        printf(" %d", i);
    }
    //----------------------------------------------------------------------------------------
    if(mode)
        fclose(fpin);
    system("pause");
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
//this function is to find the shortest path from st to end
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
            if(((dis[v_next] + w) < dis[next])){//find a shorter path
                dis[next] = dis[v_next] + w;
                path[next] = v_next;
            }
        }
    }
    return;
}
void dijkstra_back(int n, int *f, int *dis, int *path, int flag){//flag == 1 represent st to end, flag == home represent end to st
//this function is to find the shortest path from end to st, need the help of the "virtual graph" 
    for(int i = 1; i <= n; i++) {
        dis[i] = INF;
        f[i] = 0;    
    }
    int v_next, canback = 0;
    dis[flag] = 0;//initialize the distance for itself
    while(find_min(dis, f, n)){
        v_next = find_min(dis, f, n);//find the nearest vertex
        if(v_next == 0)//not found(all passed), quit
            break;
        f[v_next] = 1;
        for(int j = head_virtual[v_next]; j; j = Nforback[j].next){
            int next = Nforback[j].next_V, w = Nforback[j].dis;
            canback = back_judge(v_next, next);//if the back path (V_next, next) have a possible path (next, V_next) in the real graph 
            if(((dis[v_next] + w) < dis[next]) && canback){//find a shorter path and it can be reached in the real graph
                dis[next] = dis[v_next] + w;
                path[next] = v_next;
            }
        }
    }
    return;
}
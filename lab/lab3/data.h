#ifndef _DATA_H_
#define _DATA_H_
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int adjM[5001][5001];
int find_cnt(int n){
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){//enumerate the up triangle
            if(adjM[i][j])//if not zero, edge +1 
                cnt++;
        }
    }
    return cnt;
}
void data(int m, int n){
    srand(time(0));//randomize the seed
    FILE *f;
    f = fopen("data.in","w");
    for(int i = 1; i < n; i++){
        int a = 1 + rand() % m, b = 1 + rand() % m, d = 1 + rand() % 50;
        while (a == b){//if have a way to itself, regenerate
            a = 1 + rand() % m;
            b = 1 + rand() % m;
        }
        adjM[a][b] = d;
        adjM[b][a] = d; 
    }
    int k = find_cnt(m);//the available number of edges
    fprintf(f,"%d ", m);//output m    
    fprintf(f,"%d\n",k);//output n 
    for(int i = 1; i <= m; i++){
        for(int j = i; j <= m; j++){
            if(adjM[i][j]){
                fprintf(f,"%d %d %d\n", i, j, adjM[i][j]);//输出n
            }
        } 
    }
    fclose(f);
    return;
}

#endif

#ifndef _DATA_H_
#define _DATA_H_
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int adjM[5001][5001];
int find_cnt(int n){
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){//enumerate the up triangle
            if(adjM[i][j])//if not zero, edge +1 
                cnt++;
        }
    }
    return cnt;
}
void data(int m, int n){
    srand(time(0));//randomize the seed
    FILE *f;
    FILE *fm;
    f = fopen("data.in","w");
    fm = fopen("matlabdata.txt","w");
    for(int i = 1; i < n; i++){
        int a = 1 + rand() % m, b = 1 + rand() % m, d = 1 + rand() % 50;
        while (a == b){//if have a way to itself, regenerate
            a = 1 + rand() % m;
            b = 1 + rand() % m;
        }
        adjM[a][b] = d;
        adjM[b][a] = d; 
    }
    int k = find_cnt(m);//the available number of edges
    fprintf(f,"%d ", m);//output m    
    fprintf(f,"%d\n",k);//output n 
    for(int i = 1; i <= m; i++){
        for(int j = i; j <= m; j++){
            if(adjM[i][j]){
                fprintf(f,"%d %d %d\n", i, j, adjM[i][j]);//输出n
            }
        } 
    }
    for(int i = 1; i <= m; i++){
        for(int j = i; j <= m; j++){
            if(adjM[i][j]){
                fprintf(fm,"%d ", i);//output i
            }
        } 
    }
    fprintf(fm, "\n");
    for(int i = 1; i <= m; i++){
        for(int j = i; j <= m; j++){
            if(adjM[i][j]){
                fprintf(fm,"%d ", j);//output j
            }
        } 
    }
    fprintf(fm, "\n");
    for(int i = 1; i <= m; i++){
        for(int j = i; j <= m; j++){
            if(adjM[i][j]){
                fprintf(fm,"%d ", adjM[i][j]);//output distance
            }
        } 
    }
    fclose(f);
    fclose(fm);
    return;
}

#endif
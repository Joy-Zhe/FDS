#ifndef _TESTER_H_
#define _TESTER_H_
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
int a[10001], b[10001], d[10001];
void tester(int m, int n){
    srand(time(0));//randomize the seed
    FILE *f;
    f = fopen("data.in","w");    
    fprintf(f,"%d %d\n", m, n);//output m n
    for(int i = 1; i <= n; i++){
        a[i] = 1 + rand() % m;
        b[i] = 1 + rand() % m;
        d[i] = 1 + rand() % 5000;//change this value to change the length of the distances
        fprintf(f, "%d %d %d\n", a[i], b[i], d[i]);
    }
    fclose(f);
    //the following code are going to output a code of a matlab based graph
    FILE *fm;
    fm = fopen("matlab_auto.txt", "w");
    fprintf(fm, "s = [");
    for(int i = 1; i <= n; i++)
        fprintf(fm, "%d ", a[i]);
    fprintf(fm, "];\n");
    fprintf(fm, "t = [");
    for(int i = 1; i <= n; i++)
        fprintf(fm, "%d ", b[i]);
    fprintf(fm, "];\n");
    fprintf(fm, "w = [");
    for(int i = 1; i <= n; i++)
        fprintf(fm, "%d ", d[i]);
    fprintf(fm, "];\n");
    fprintf(fm, "G = graph(s,t,w);\nn = %d;\nplot(G, 'EdgeLabel', G.Edges.Weight, 'linewidth', 2) ;\nset( gca, 'XTick', [], 'YTick', [] );\n[P,d] = shortestpath(G, 1, n);\nmyplot = plot(G, 'EdgeLabel', G.Edges.Weight, 'linewidth', 2);\nhighlight(myplot, P, 'EdgeColor', 'r');\nD = distances(G);\nD(1,n);", m);
    fclose(fm);
    return;
}
#endif
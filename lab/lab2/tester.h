#ifndef _TESTER_H_
#define _TESTER_H_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
typedef struct{
    int pos_A;
    int pos_B; 
}Info;
double a[1001][2], b[1001][2];
void generate_tester(int n_A, int n_B, double ta[][2], double tb[][2], int rotate){
    srand(time(0));
    for(int i = 1; i <= n_A; i++){
        ta[i][0] = rand() % 100 - 50;//generating X_A between [-50, 50)
        ta[i][1] = rand() % 100 - 50;//generating Y_A between [-50, 50)
        if(rotate == 0){//not rotate
            tb[i][0] = ta[i][0] + 50;//set X_B as X_A move 50 right
            tb[i][1] = ta[i][1] + 50;//set Y_B as Y_A move 50 right
        }else{//rotate
            tb[i][0] = (ta[i][0] + 50) * cos(0.3) - (ta[i][1] + 50) * sin(0.3);//have a rotate, times a matrix to accomplish this work
            tb[i][1] = (ta[i][0] + 50) * sin(0.3) + (ta[i][1] + 50) * cos(0.3);
        }  
    }
    for(int i = n_A + 1; i <= n_B; i++){
        tb[i][0] = rand() % 100 - 50;//randomly generate the left points
        tb[i][1] = rand() % 100 - 50;
    }
    return;
}
#endif
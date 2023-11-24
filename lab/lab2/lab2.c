#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"tester.h"
struct Node{
    int pos_A;
    int pos_B;
    struct Node *child;
    struct Node *brother;
};
// typedef struct{
//     int pos_A;
//     int pos_B;   
// }Info;
clock_t start, stop;
double duration, total_time;
int flag[1001][1001];
double a[1001][2], b[1001][2];
int output[1001];
Info stack[1001];
int table[1001][1001];//create table 
int p_stack = 0;//pointer for the stack
typedef struct Node * TreeNode;
int cnt = 0;
int match(Info n1, Info n2, Info n3);//calculate the angle and the scale of the same lines to judge whether it's a possible match
void tree_dfs(Info *selected, int p, int pos_A, int pos_B, int n_A, int n_B, FILE *fpout);//the forest to enumerate all the possible match
Info find_max(int t[][1001], int line, int n_B, int st);//find the current maximum in the table
Info selected[1001];
void Initialize_table(int n_A, int n_B){//Initialize the voting table to be all 0
    for(int i = 1; i <= n_A; i++){
        for(int j = 1; j <= n_B; j++)
            table[i][j] = 0;
    }
}
int main (){
    int m, n, flag = 0, type;
    int ticks, k = 1;
    TreeNode r = NULL;
    FILE *fpout, *fpvote;
    fpout = fopen("out_tree1.txt", "w+");//open a file to store the paths in the tree/forest
    fpvote = fopen("voting table5.txt", "w+");//open a file to store the voting table
    printf("select the testing method:(0 for auto, 1 for type)");
    scanf("%d", &type);
    printf("Input the number of points in A and B:");//prepare for input
    scanf("%d %d", &m, &n);
    if(type == 0){
        printf("whether rotate(0no, 1yes):");//ask whether to rotate, 1 represent yes
        scanf("%d", &flag);
    }
    printf("Input running times(k):");//ask the iteration of the program
    scanf("%d", &k);
    if(type == 0)//if auto, automaticly generate
        generate_tester(m, n, a, b, flag);//generating the test polygons
    else{//if type, type in by hand
        for(int i = 1; i <= m; i++){
            scanf("%lf %lf", &a[i][0], &a[i][1]);
        }
        for(int i = 1; i <= n; i++){
            scanf("%lf %lf", &b[i][0], &b[i][1]);
        }
    }
    start = clock();//start count
    for(int i = 1; i <= k; i++){//run k1 times 
        Initialize_table(m, n);
        tree_dfs(selected, 0, 0, 0, m, n, fpout);
    }
    stop = clock();//stop count
    ticks = (stop - start);
    total_time = (double)(stop - start)/CLK_TCK;
    duration = (double)(total_time / k);
    Info tmp;
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            fprintf(fpvote, "%d ", table[i][j]);//write the voting result
        }
        fprintf(fpvote, "\n");
    }
    for(int i = 1; i <= m; i++){//out put the best matches
        tmp = find_max(table, i, n, output[i - 1]);//find max number of vote for this A
        output[tmp.pos_A] = tmp.pos_B;//store position of B
    }
    for(int i = 1; i <= m; i++){
        printf("(%d,%d):A(%2.2lf,%2.2lf) B(%2.2lf,%2.2lf)\n", i, output[i], a[i][0], a[i][1], b[i][0], b[i][1]);//print the answer
    }
    printf("iterations = %d\nticks = %d\ntotal time = %lfs\nduration = %.9lfs\n", k, ticks, total_time, duration);//print the information of the runtime
    fclose(fpout);
    fclose(fpvote);//close the files
    return 0;
}

int match(Info n1, Info n2, Info n3){//calculate the angle and the scale of the same lines to judge whether it's a possible match
    double p1, p2, angle1, angle2;
    double ma1, ma2, ma3, mb1, mb2, mb3;
    ma1 = sqrt((a[n1.pos_A][1] - a[n2.pos_A][1]) * (a[n1.pos_A][1] - a[n2.pos_A][1]) + (a[n1.pos_A][0] - a[n2.pos_A][0]) * (a[n1.pos_A][0] - a[n2.pos_A][0]));//calculate side 1 of A
    mb1 = sqrt((b[n1.pos_B][1] - b[n2.pos_B][1]) * (b[n1.pos_B][1] - b[n2.pos_B][1]) + (b[n1.pos_B][0] - b[n2.pos_B][0]) * (b[n1.pos_B][0] - b[n2.pos_B][0]));//calculate side 1 of B
    ma2 = sqrt((a[n3.pos_A][1] - a[n2.pos_A][1]) * (a[n3.pos_A][1] - a[n2.pos_A][1]) + (a[n3.pos_A][0] - a[n2.pos_A][0]) * (a[n3.pos_A][0] - a[n2.pos_A][0]));//calculate side 2 of A
    mb2 = sqrt((b[n3.pos_B][1] - b[n2.pos_B][1]) * (b[n3.pos_B][1] - b[n2.pos_B][1]) + (b[n3.pos_B][0] - b[n2.pos_B][0]) * (b[n3.pos_B][0] - b[n2.pos_B][0]));//calculate side 2 of B
    ma3 = sqrt((a[n3.pos_A][1] - a[n1.pos_A][1]) * (a[n3.pos_A][1] - a[n1.pos_A][1]) + (a[n3.pos_A][0] - a[n1.pos_A][0]) * (a[n3.pos_A][0] - a[n1.pos_A][0]));//calculate side 3 of A
    mb3 = sqrt((b[n3.pos_B][1] - b[n1.pos_B][1]) * (b[n3.pos_B][1] - b[n1.pos_B][1]) + (b[n3.pos_B][0] - b[n1.pos_B][0]) * (b[n3.pos_B][0] - b[n1.pos_B][0]));//calculate side 3 of B
    p1 = ma1 / mb1;//the proportion between side 1 in A and B
    p2 = ma2 / mb2;//the proportion between side 2 in A and B
    angle1 = acos((ma1 * ma1 + ma2 * ma2 - ma3 * ma3) / (2 * ma1 * ma2));//The Law of Cosines to calculate angle between side 1 and 2 in A
    angle2 = acos((mb1 * mb1 + mb2 * mb2 - mb3 * mb3) / (2 * mb1 * mb2));//The Law of Cosines to calculate angle between side 1 and 2 in B
    if(fabs(p1 - p2) < 0.01 && fabs(angle1 - angle2) < 0.01)
        return 1;//simular return 1
    else
        return 0;//not simular return 0
}

void tree_dfs(Info *selected, int p, int pos_A, int pos_B, int n_A, int n_B, FILE *fpout){
    int f = 0;
    if(p == n_A){//stack is full, start voting, and then pop all the 
        for(int i = 1; i <= p; i++){
            table[selected[i].pos_A][selected[i].pos_B]++;//vote all the match in the path
        }
        p--;//pop the last one match to enumerate the next possible match
        return;
    }
    for(int i = pos_A + 1; i <= n_A; i++){//enumerate A
        f = 0;//f = 0 represent going on this loop
        for(int k = 1; k <= p; k++){
            if(selected[k].pos_A >= i || p != (i - 1)){//if this point in A has existed or it's not ascending for A
                f = 1;//if so, skip this A
                break;
            }
        }
        if(f == 1)//skip this A
            continue;
        for(int j = pos_B + 1; j <= n_B; j++){//enumerate point in B
            f = 0;
            for(int k = 1; k <= p; k++){
                if(selected[k].pos_B >= j){//if this point in B is not ascending
                    f = 1;
                    break;
                }
            }
            if(f == 1)//skip this B
                continue;
            p++;//if A and B is possible at present, prepare for push
            selected[p].pos_A = i;//push the horizontal coordinate
            selected[p].pos_B = j;//push the vertical coordinate
            for(int t = 1; t <= p; t++)
                fprintf(fpout, "(%d,%d)", selected[t].pos_A, selected[t].pos_B);
            fprintf(fpout, "\n");
            if(p >= 3){//if 3 matches already exists, judge if they are similar 
                if(match(selected[p - 2], selected[p - 1], selected[p]) == 0){//if not similar, cut the path and change to another child of the parent
                    selected[p].pos_A = 0;
                    selected[p].pos_B = 0;
                    p--;//pop the last match
                    continue;//skip this B to enumerate its "brother"
                }
            }
            tree_dfs(selected, p, i, j, n_A, n_B, fpout);//recursively enumerate
            p--;//pop the no use match
        }
    }
    return;
}

Info find_max(int t[][1001], int line, int n_B, int st){//find the current maximum in the table
    int max = -1;
    Info ans;
    // for(int i = 1; i <= n_A; i++){
        for(int j = st + 1; j <= n_B; j++){
            if(t[line][j] > max){//record the (A,B) match when there is a larger voting
                max = t[line][j];
                ans.pos_A = line;
                ans.pos_B = j;
            }
        }
    // }
    t[line][ans.pos_B] = 0;//set this match to 0 to prevent from selecting it again
    return ans;
}
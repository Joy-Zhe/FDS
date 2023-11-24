#include<stdlib.h>
#include<stdio.h>
#include<time.h>
typedef struct{
    char level;//store the level
    int site_num;//store the site number
    int date;//store the date
    int testee_num;//store the testee number
    int score;//store the score of this person
}info;
int a[10001], b[10001], d[10001];
int main (){
    srand(time(0));//randomize the seed
    FILE *f;
    info tmp;
    int m = rand() % 500 + 1, n = rand() % 500 + 1;
    f = fopen("data.in","w");    
    fprintf(f,"%d %d\n", m, n);//output m n
    for(int i = 1; i <= m; i++){
        tmp.level = rand() % 26 + 65;
        tmp.site_num = rand() % 900 + 100;
        tmp.date = rand() % 10000 + 180000;
        tmp.testee_num = rand() % 1000;
        tmp.score = rand() % 100 + 1;
        fprintf(f ,"%c%d%06d%03d %d\n", tmp.level, tmp.site_num, tmp.date, tmp.testee_num, tmp.score);
    }
    for(int i = 1; i <= n; i++){
        int type = rand() % 3 + 1;
        if(type == 1){
            char c = rand() % 26 + 65;
            fprintf(f, "%d %c\n", type, c);
        }else if(type == 2){
            int site = rand() % 900 + 100;
            fprintf(f, "%d %d\n", type, site);
        }else if(type == 3){
            int date = rand() % 200000;
            fprintf(f, "%d %06d\n", type, date);
        }
    }
    fclose(f);
    return 0;
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//save the string as separate info
typedef struct{
    char level;//bit1
    int num_site;//test site number, bit2-4
    char date[10];//test date, bit5-10
    int num_testee;//testee's number. bit11-13
    int score;//score
    //int out_flag;//whether to output
}info;
typedef struct{
    int type;
    char level;
    char date[10];//test date
    int num_site;//site's number
}out;
int cmp1(const void *a, const void *b){
    info *tmp1 = (info *)a;
    info *tmp2 = (info *)b;
    if(tmp1->score != tmp2->score)
        return (tmp2->score - tmp1->score);//if score is different, return the bigger one
    if(tmp1->level != tmp2->level)
        return (tmp1->level - tmp2->level);//if the scores are the same, compare the level
    if(tmp1->num_site != tmp2->num_site)
        return (tmp1->num_site - tmp2->num_site);//if score and levels are both the same, compare the site number
    if(strcmp(tmp1->date, tmp2->date))
        return (strcmp(tmp1->date, tmp2->date));//if all the score and the site and the levels are the same, compare the date
    if(tmp1->num_testee != tmp2->num_testee)
        return (tmp1->num_testee - tmp2->num_testee);//if the befpre ones are all the same, compare the testee's number
} 
int main (){
    int ans_3[1000] = {0};
    int N, M;
    char tmp[15];
    out out_info[101];
    info DATA[10001];
    info out[101];
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++){
        scanf("%s", tmp);
        scanf("%d", &DATA[i].score);
        DATA[i].level = tmp[0];
        DATA[i].num_site = 100 * (tmp[1] - '0') + 10 * (tmp[2] - '0') + (tmp[3] - '0');
        for(int j = 0; j < 6; j++)
            DATA[i].date[j] = tmp[j + 4];
        DATA[i].date[6] = '\0';
        DATA[i].num_testee = 100 * (tmp[10] - '0') + 10 * (tmp[11] - '0') + (tmp[12] - '0');
    }
    for(int i = 1; i <= M; i++){
        scanf("%d", &out_info[i].type);
        switch (out_info[i].type){
            case 1:
                getchar();//skip space
                scanf("%c", &out_info[i].level);
                break;
            case 2:
                scanf("%d", &out_info[i].num_site);
                break;
            case 3:
                scanf("%s", out_info[i].date);
                break;
            default:
                break;
        } 
    }
    // qsort(DATA, N, sizeof(info), cmp1);
    for(int i = 1; i <= M; i++){
        for(int j = 100; j < 1000; j++)
            ans_3[j] = 0;
        int max = 0, ans = 0, k = 0;
        if(out_info[i].type == 1){
            // qsort(DATA, N, sizeof(info), cmp);
            printf("Case %d: 1 %c\n", i, out_info[i].level);
            for(int j = 0; j < N; j++){
                if(DATA[j].level == out_info[i].level){
                    //DATA[j].out_flag = 1;
                    //printf("%c%d%s%s %d\n", DATA[j].level, DATA[j].num_site, DATA[j].date, DATA[j].num_testee, DATA[j].score);
                    out[k].level = DATA[j].level;
                    out[k].num_site = DATA[j].num_site;
                    strcpy(out[k].date, DATA[j].date);
                    out[k].num_testee = DATA[j].num_testee;
                    out[k].score = DATA[j].score;
                    k++;
                    ans = 1;
                }
            }
            qsort(out, k, sizeof(info), cmp1);
            for(int j = 0; j < k; j++){
                printf("%c%d%s%03d %d\n", out[j].level, out[j].num_site, out[j].date, out[j].num_testee, out[j].score);
            }
            if(ans == 0)
                printf("NA\n");
        }else if(out_info[i].type == 2){
            int cnt = 0, sum = 0;
            printf("Case %d: 2 %d\n", i, out_info[i].num_site);
            for(int j = 0; j < N; j++){
                if(DATA[j].num_site == out_info[i].num_site){
                    cnt++;
                    sum += DATA[j].score;
                }
            }
            if(cnt)
                printf("%d %d\n", cnt, sum);
            else
                printf("NA\n");
        }
        else if(out_info[i].type == 3){
            printf("Case %d: 3 %s\n", i, out_info[i].date);
            for(int j = 0; j < N; j++){
                if(strcmp(DATA[j].date, out_info[i].date) == 0){
                    ans_3[DATA[j].num_site]++;
                    if(ans_3[DATA[j].num_site] > max)
                        max = ans_3[DATA[j].num_site];
                }
            }
            for(int t = max; t > 0; t--){   
                for(int j = 100; j < 1000; j++){
                    if(ans_3[j] == t){
                        printf("%d %d\n", j, ans_3[j]);
                        ans = 1;
                    }
                }
            }
            if(ans == 0)
                printf("NA\n");
        }
    }
    return 0;
}

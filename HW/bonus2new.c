#include<stdio.h>
#include<stdlib.h>
typedef struct{
    char level;//store the level
    int site_num;//store the site number
    int date;//store the date
    int testee_num;//store the testee number
    int score;//store the score of this person
}info;
int rank[10001];//bottle rank for type 3
int cmp(const void *a, const void *b){//compare funtion for type1
    info *tmp1 = (info *)a;
    info *tmp2 = (info *)b;
    if(tmp1->score != tmp2->score)
        return (tmp2->score - tmp1->score);//if score is different, return the bigger one
    if(tmp1->level != tmp2->level)
        return (tmp1->level - tmp2->level);//if the scores are the same, compare the level
    if(tmp1->site_num != tmp2->site_num)
        return (tmp1->site_num - tmp2->site_num);//if score and levels are both the same, compare the site number
    if(tmp1->date != tmp2->date)
        return (tmp1->date - tmp2->date);//if all the score and the site and the levels are the same, compare the date
    if(tmp1->testee_num != tmp2->testee_num)
        return (tmp1->testee_num - tmp2->testee_num);//if the befpre ones are all the same, compare the testee's number
}
info DATA[10001];//store the informations
int main (){
    int n, m;
    char tmp[101];
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        scanf("%s", tmp);
        scanf("%d", &DATA[i].score);
        DATA[i].level = tmp[0];//get bit0 for level
        DATA[i].site_num = 100 * (tmp[1] - '0') + 10 * (tmp[2] - '0') + tmp[3] - '0';//get bit1-3 for site num
        DATA[i].date = 100000 * (tmp[4] - '0') + 10000 * (tmp[5] - '0') + 1000 * (tmp[6] - '0') + 100 * (tmp[7] - '0') + 10 * (tmp[8] - '0') + tmp[9] - '0';//get bit4-9 for date
        DATA[i].testee_num = 100 * (tmp[10] - '0') + 10 * (tmp[11] - '0') + tmp[12] - '0';//get bit10-12 for testee num
    }
    int cnt_n = 0, cnt = 0, f = 0;//cnt_n store the number of answers in type 2, cnt store the sum of the score
    //f is used to judge if there is any answers
    int type;//the type number
    char l;
    int max_3 = -1, min_3 = 110;
    int site, date;
    qsort(DATA, n, sizeof(info), cmp);//sort the total array by qsort
    for(int i = 0; i < m; i++){
        scanf("%d", &type);
        if(type == 1){
            f = 0;//set the state to "no answer"
            getchar();//skip the space
            l = getchar();//get level to compare
            printf("Case %d: %d %c\n", i + 1, type, l);
            for(int j = 0; j < n; j++){
                if(DATA[j].level == l){//because the array is sorted for type1, here we only need to output
                    printf("%c%d%06d%03d %d\n", DATA[j].level, DATA[j].site_num, DATA[j].date, DATA[j].testee_num, DATA[j].score);
                    //add 0 before date and testee number
                    f = 1;//set the state to "have answer"
                }
            }
            if(f == 0)//no answer, output NA
                printf("NA\n");
        }
        else if(type == 2){
            cnt = 0;
            cnt_n = 0;
            scanf("%d", &site);
            printf("Case %d: %d %d\n", i + 1, type, site);
            for(int j = 0; j < n; j++){
                if(DATA[j].site_num == site){
                    cnt += DATA[j].score;//add sum
                    cnt_n++;//add answer number
                }
            }
            if(cnt_n){
                printf("%d %d\n", cnt_n, cnt);
            }else{//no answer
                printf("NA\n");
            }
        }else if(type == 3){
            f = 0;
            scanf("%d", &date);
            printf("Case %d: %d %06d\n", i + 1, type, date);//add 0 before date
            for(int j = 0; j < n; j++){
                if(DATA[j].date == date)// the number of the site ++
                    rank[DATA[j].site_num]++;
                if(rank[DATA[j].site_num] > max_3)
                    max_3 = rank[DATA[j].site_num];//record the max exist time
            }
            for(int j = max_3; j > 0; j--){//output in a non-increasing order of the exist time
                for(int k = 100; k < 1000; k++){//output in a non-decreasing order of the site number of the answer 
                    if(rank[k] == j){
                        printf("%d %d\n", k, rank[k]);
                        rank[k] = 0;//set to 0 for next time's use
                        f = 1;//set the state to "have answer"
                    }
                }
            }
            if(f == 0)//no answer, output NA
                printf("NA\n");
        }
    }
    return 0;
}
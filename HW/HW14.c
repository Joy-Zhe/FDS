/*
思路：对给定输出序列进行扫描，若与下标相同则为第一批输入
    若与下标不同且前一位不在对应位置，则插入对应x%n的后一位
    若与下标不同且前一位在对应位置，则将序设为当前的最后
*/
#include<stdio.h>
int output[1001][2];//output[][0] store number, output[][1] store xmodn
int end;//record the present end order
// int table[1001][1001];
struct table{
    int order[1001];//bucket members
    int tail;//tail of present bucket
}ans[1001];
int main (){
    int n;
    for(int i = 0; i < n; i++){
        scanf("%d", &output[i][0]);
        if(output[i][0] >= 0)
            output[i][1] = output[i][0] % n;
        else
            output[i][1] = -1;
    }
    for(int i = 0; i < n; i++){
        if(output[i][0] < 0)
            continue;
        if(output[i][1] == i){
            ans[i].order[ans[i].tail] = output[i][0];
            ans[i].tail++;
            if(ans[i].tail >= end)
                end = ans[i].tail;
        }else{
            if(i == 0){
                ans[output[i][1]].order[ans[output[i][1]].tail] = output[i][0];
                ans[i].tail++;
                if(ans[i].tail >= end)
                    end = ans[i].tail;
            }else if(i - 1 == output[i - 1][1]){
                ans[output[i][1]].order[ans[output[i][1]].tail] = output[i][0];
                ans[i].tail++;
                if(ans[i].tail >= end)
                    end = ans[i].tail;
            }else{
                ans[output[i][1]].tail = end + 1;
                ans[output[i][1]].order[ans[output[i][1]].tail] = output[i][0];
                ans[i].tail++;
                if(ans[i].tail >= end)
                    end = ans[i].tail;
            }
        }
    }
}
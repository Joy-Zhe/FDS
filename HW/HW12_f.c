#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
    int p1, p2, pos = 0, f;
    for(int t = 0; t < N; t += length * 2){
        p1 = t;
        p2 = t + length;
        if(p2 + length >= N)
            f = N - p2;
        else 
            f = length;
        int i = 0;
        int j = 0;
        while(i < length && j < f){
            if(list[p1 + i] < list[p2 + j]){
                sorted[pos] = list[p1 + i];
                i++;
                pos++;
            }else{
                sorted[pos] = list[p2 + j];
                j++;
                pos++;
            }
        }
        while(i < length){
            sorted[pos] = list[p1 + i];
            i++;
            pos++;
        }
        while(j < f){
            sorted[pos] = list[p2 + j];
            j++;
            pos++;
        }
    }
    // int i = 0, j = 0;
    // if(p2 < N){
    //     int left = N - p2;
    //     while(i < length && j < left){
    //         if(list[p1 + i] < list[p2 + j]){
    //             sorted[pos] = list[p1 + i];
    //             i++;
    //             pos++;
    //         }else{
    //             sorted[pos] = list[p2 + j];
    //             j++;
    //             pos++;
    //         }
    //     }
    //     while(i < length){
    //         sorted[pos] = list[p1 + i];
    //         i++;
    //         pos++;
    //     }
    //     while(j < left){
    //         sorted[pos] = list[p2 + j];
    //         j++;
    //         pos++;
    //     }
    // }else if(p1 < N){
    //     while(p1 + i < N){
    //         sorted[pos] = list[p1 + i];
    //         i++;
    //         pos++;
    //     }
    // }
    return;
}
#include<stdio.h>
#include<stdlib.h>
int size_heap, pos;
int heap[2001], sorted[2001], now[2001];
int origin[2001], next[2001];
int is_heap_sort(int *first, int *next, int n);
int is_insertion_sort(int *first, int *next, int n);
void deleteMax(int *ori);
void down(int p, int *ori);
void gen_now(){
    for(int i = 1; i <= size_heap; i++)
        now[i] = heap[i];
    int p = size_heap + 1, tmp = pos;
    while(tmp >= 0){
        tmp--;
        now[p] = sorted[tmp];
        p++;
    }
    return;
}
int compare(int *a, int *b, int n){
    for(int i = 1; i <= n; i++){
        if(a[i] != b[i])
            return 0;
    }
    return 1;
}
void print_arr(int *a, int n){
    printf("%d", a[1]);
    for(int i = 2; i <= n; i++)
        printf(" %d", a[i]);
    printf("\n");
    return;
}
int main(){
    int n;
    scanf("%d", &n);
    size_heap = n;
    for(int i = 1; i <= n; i++)
    scanf("%d", &origin[i]);
    for(int i = 1; i <= n; i++)
    scanf("%d", &next[i]);
    if(is_heap_sort(origin, next, n))
        return 0;
    if(is_insertion_sort(origin, next, n))
        return 0;
}
void down(int p, int *ori){
    int n, cmp1, cmp2;
    if(p * 2 > size_heap)
        return;
    n = ori[p];
    cmp1 = ori[p * 2];
    cmp2 = ori[p * 2 + 1];
    if(n < cmp1 && cmp1 > cmp2){
        ori[p] = cmp1;
        ori[p * 2] = n;
        down(p * 2, ori);
    }else if(n < cmp2 && cmp1 < cmp2){
        ori[p] = cmp2;
        ori[p * 2 + 1] = n;
        down(p * 2 + 1, ori);
    }
    return;
}
void deleteMax(int *ori){
    int max = ori[1];
    sorted[pos] = max;
    pos++;
    ori[1] = ori[size_heap];
    down(1, ori);
    size_heap--;
    return;
}
int is_heap_sort(int *first, int *next, int n){
    //initialize heap
    for(int i = 1; i <= n; i++)
        heap[i] = first[i];
    int p = n / 2;
    for(int i = p; i > 0; i--){
        int father = i, num = heap[father];
        int cmp1 = 2 * i, cmp2 = 2 * i + 1;
        down(father, heap);
    }
    while(size_heap){
        deleteMax(heap);
        gen_now();
        // print_arr(now, n);
        if(compare(now, next, n)){
            printf("Heap Sort\n");
            deleteMax(heap);
            gen_now();
            print_arr(now, n);
            return 1;
        }
    }
    // for(int i = pos - 1; i >= 0; i--)
    //     printf("%d ", sorted[i]);
    return 0;
}
int is_insertion_sort(int *ori, int *next, int n){
    int j;
    for(int i = 2; i <= n; i++){
        int tmp = origin[i];
        for(j = i; j >= 2; j--){
            if(tmp <= origin[j - 1])
                origin[j] = origin[j - 1]; 
            else 
                break;
        }
        origin[j] = tmp;
        // print_arr(origin, n);
        if(compare(origin, next, n)){
            tmp = origin[i + 1];
            for(j = i + 1; j >= 2; j--){
            if(tmp <= origin[j - 1])
                origin[j] = origin[j - 1]; 
            else 
                break;
            }
            origin[j] = tmp;
            printf("Insertion Sort\n");
            print_arr(origin, n);
            return 1;
        } 
    }
    return 0;
}
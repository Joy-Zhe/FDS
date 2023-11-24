#include<stdlib.h>
struct Node{
    int n;
    struct Node *Next;
};
typedef struct Node* List;


List Reverse( List L ){
    List tail, ans, saved_next;
    saved_next = (List)malloc(sizeof(struct Node));
    ans = L->Next;
    tail = NULL;
    saved_next = NULL;
    ans->Next = NULL;
    while(ans){
        saved_next = ans->Next;
        ans->Next = tail;
        tail = ans;
        ans = saved_next;
    }
    List tmp;
    ans = tail;
    tmp = L;
    while(ans){
        tmp->Next = ans;
        ans = ans->Next;
        tmp = tmp->Next;
    }
    return L;
}
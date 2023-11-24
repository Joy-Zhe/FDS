int Isomorphic(Tree T1, Tree T2){
    int cnt = 0;
    if(T1 == NULL && T2 == NULL)
        return 1;
    if(T1 == NULL || T2 == NULL)
        return 0;
    if(Isomorphic(T1->Left, T2->Left)) 
        cnt++;
    if(Isomorphic(T1->Left, T2->Right))
        cnt++;
    if(Isomorphic(T1->Right, T2->Left))
        cnt++;
    if(Isomorphic(T1->Right, T2->Right))
        cnt++;
    if(cnt >= 2){
        if(T1->Element == T2->Element)
            return 1;
        else
            return 0;
    }else
        return 0;
}

int Isomorphic(Tree T1, Tree T2){
    if(T1 == NULL && T2 == NULL)
        return 1;
    if(T1 == NULL || T2 == NULL)
        return 0;
    if(Isomorphic(T1->Left, T2->Left) && Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left) && Isomorphic(T1->Right, T2->Right)){
        if(T1->Element == T2->Element)
            return 1;
        else
            return 0;
    }else
        return 0;
}
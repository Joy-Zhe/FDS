#include<stdio.h>
#include<math.h>
int inorder[1001], postorder[1001], tree[210000000];
int depth;
void findroot(int st_in, int end_in, int *in, int st_post, int end_post, int *post, int layer, int label);
int main (){
    int n, flag, layer = 0;
    for(int i = 0; i < 1000; i++)
        tree[i] = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);
    for(int i = 0; i < n; i++)
        scanf("%d", &postorder[i]);
    findroot(0, n - 1, inorder, 0, n - 1, postorder, 0, 0);
    // for(int i = 0; i < 20; i++){
    //     printf("%d\n", tree[i]);
    // }
    for(int i = 0; i <= depth; i++){
        if(i % 2 == 0){
            for(int j = pow(2, i + 1) - 2; j >= pow(2, i) - 1; j--){
                if(j == 0)
                    printf("%d", tree[j]);
                else if(tree[j]) 
                    printf(" %d", tree[j]);
            }
        }else{
            for(int j = pow(2, i) - 1; j <= pow(2, i + 1) - 2; j++){
                if(j == 0)
                    printf("%d", tree[j]);
                else if(tree[j])
                    printf(" %d", tree[j]);
            }
        }
    }
    printf("\n");
    return 0;
}
void findroot(int st_in, int end_in, int *in, int st_post, int end_post, int *post, int layer, int label){//label存储下一个的编号, layer记录层数，从0开始
    int root;
    int new_st_inl, new_end_inl, new_post_stl, new_post_endl;
    int new_st_inr, new_end_inr, new_post_str, new_post_endr;
    int i, f_l = 1, f_r = 1;
    printf("%d %d\n", st_post, end_post);
    if(depth < layer)
        depth = layer;
    for(i = st_post; i <= end_post; i++);
    //printf("%d\n", i - 1);
    root = post[end_post];
    tree[label] = root;
    if(i - 2 >= st_post)//更新后序的右子树终点
        new_post_endr = i - 2;
    else{//超过
        f_l = 0;
        f_r = 0;
    }
    for(i = st_in; in[i] != root; i++);
    if(i - 1 >= st_in){
        new_end_inl = i - 1;
        new_post_endl = st_post + new_end_inl - st_in;
        f_l = 1;
    }else{
        new_post_endl = st_post;
        f_l = 0;
    }
    if((i + 1) <= end_in){    
        new_st_inr = i + 1;
        if(f_l == 1)
            new_post_str = new_post_endl + 1;
        else
            new_post_str = st_post;
        f_r = 1;
    }else{
        f_r = 0;
    }
    //左
    if(f_l == 1)
        findroot(st_in, new_end_inl, in, st_post, new_post_endl, post, layer + 1, label * 2 + 1);
    //右
    if(f_r == 1) 
        findroot(new_st_inr, end_in, in, new_post_str, new_post_endr, post, layer + 1, label * 2 + 2);
    return;
}

// #include<stdio.h>
// #include<math.h>
// int inorder[30], postorder[30], tree[2100000000];
// int depth;
// void findroot(int st_in, int end_in, int *in, int st_post, int end_post, int *post, int layer, int label);
// int main (){
//     int n, flag;
//     scanf("%d", &n);
//     for(int i = 0; i < n; i++)
//         scanf("%d", &inorder[i]);
//     for(int i = 0; i < n; i++)
//         scanf("%d", &postorder[i]);
//     findroot(0, n - 1, inorder, 0, n - 1, postorder, 0, 0);
//     // for(int i = 0; i < 20; i++){
//     //     printf("%d\n", tree[i]);
//     // }
//     for(int i = 0; i <= depth; i++){
//         if(i % 2 == 0){
//             for(int j = pow(2, i + 1) - 2; j >= pow(2, i) - 1; j--){
//                 if(j == 0)
//                     printf("%d", tree[j]);
//                 else if(tree[j]) 
//                     printf(" %d", tree[j]);
//             }
//         }else{
//             for(int j = pow(2, i) - 1; j <= pow(2, i + 1) - 2; j++){
//                 if(j == 0)
//                     printf("%d", tree[j]);
//                 else if(tree[j])
//                     printf(" %d", tree[j]);
//             }
//         }
//     }
//     printf("\n");
//     return 0;
// }
// void findroot(int st_in, int end_in, int *in, int st_post, int end_post, int *post, int layer, int label){//label存储下一个的编号, layer记录层数，从0开始
//     int root;
//     int new_st_inl, new_end_inl, new_post_stl, new_post_endl;
//     int new_st_inr, new_end_inr, new_post_str, new_post_endr;
//     int i, f_l = 1, f_r = 1;
//     if(depth < layer)
//         depth = layer;
//     for(i = st_post; i <= end_post; i++);
//     //printf("%d\n", i - 1);
//     root = post[i - 1];
//     tree[label] = root;
//     if(i - 2 >= st_post)
//         new_post_endr = i - 2;
//     else{
//         f_l = 0;
//         f_r = 0;
//     }
//     for(i = st_in; in[i] != root; i++);
//     if(i - 1 >= st_in){
//         new_end_inl = i - 1;
//         new_post_endl = st_post + new_end_inl - st_in;
//         f_l = 1;
//     }else{
//         f_l = 0;
//     }
//     if((i + 1) <= end_in){    
//         new_st_inr = i + 1;
//         new_post_str = new_post_endl + 1;
//         f_r = 1;
//     }else{
//         f_r = 0;
//     }
//     //左
//     if(f_l == 1)
//         findroot(st_in, new_end_inl, in, st_post, new_post_endl, post, layer + 1, label * 2 + 1);
//     //右
//     if(f_r == 1) 
//         findroot(new_st_inr, end_in, in, new_post_str, new_post_endr, post, layer + 1, label * 2 + 2);
//     return;
// }
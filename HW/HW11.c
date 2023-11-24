#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
int stack[20], ptr;
int time[20], label[20], present;
int path(int from, int to, Graph G){//if from is directly linked to to
    for(PtrToVNode i = G->Array[from]; i; i = i->Next){
        if(i->Vert == to)
            return 1;
    }
    return 0;
}
int in_stack(int v){//if v is in the stack
    for(int i = 1; i <= ptr; i++){
        if(stack[i] == v)
            return 1;
    }
    return 0;
}
int min(int a, int b){
    if(a > b)
        return b;
    return a;
}
void update_label(Graph G, int v){
    ptr++;
    stack[ptr] = v;//push v
    present++;//update the present time
    time[v] = present;
    label[v] = present;
    for(PtrToVNode i = G->Array[v]; i; i = i->Next){
        if(time[i->Vert] == 0){//haven't enumerated yet
            update_label(G, i->Vert);
            label[v] = min(label[v], label[i->Vert]);
        }
        else if(in_stack(i->Vert)){//have enumerate but still not printed
            label[v] = min(label[v], time[i->Vert]);
        }
    }
    if(time[v] == label[v]){//find the end point of a strongly connected component
        while(stack[ptr] != v){//pop all the vertices which have the same label
            PrintV(stack[ptr]);
            stack[ptr] = 0;
            ptr--;
        }
        PrintV(stack[ptr]);//pop v
        stack[ptr] = 0;
        ptr--;
        printf("\n");
    }
    return;
}
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
    for(int i = 0; i < G->NumOfVertices; i++){
        if(time[i] == 0)//haven't enumerated yet
            update_label(G, i);
    }
    return;
}
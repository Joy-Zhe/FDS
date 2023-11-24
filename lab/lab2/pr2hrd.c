#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 32
#define TOL 0.85 /*the tolerance of similarity*/
#define Max(a,b) (a>b?a:b)
#define pi 3.1415926535
/*gobal varaiables*/
double a[MAX_SIZE][2], b[MAX_SIZE][2];/*store information of points*/
double votem[MAX_SIZE][MAX_SIZE];
struct tree_node{
	int ai;/*index in matrix a*/
	int bi;/*index in matrix b*/
	int closed;/*whether it is closed*/
	struct tree_node *children[MAX_SIZE];/*it's children*/
	struct tree_node *parent;/*its'parent*/
};
typedef struct tree_node *NODE;
/*function used*/
NODE newnode(void);
int construct(int n, int m, NODE parent, int bini);
int optimize(int n, int m, NODE parent,int ai[], int bi[], int *si);
double length(int ai, int bi, double x[][2]);
double sim(int a[], int b[],int m, int n);
double angle(double a, double b, double c);
int vote(NODE parent,int m, int n);
void select(int re[][2],int m,int n);
/*codes*/
int main()
{
	/*scan the max size of graph a and b*/
	int m, n;
	scanf("%d %d",&m,&n);
	/*scan the 2-dementional point sets of a&b*/
	int i, j;
	for(i=0;i<m;i++) scanf("%lf %lf",&a[i][0],&a[i][1]);
	for(i=0;i<n;i++) scanf("%lf %lf",&b[i][0],&b[i][1]);
	/*generetate tree*/
	NODE root[n];
	for(i=0;i<n;i++)
	{
		root[i] = newnode();root[i]->ai = 0;root[i]->bi = i;root[i]->closed = 0;
		construct(n,m,root[i],root[i]->bi);
		/*optimize the tree*/
		int sa[m], sb[m];/*stack used in function to store the path*/
		int si=0;/*stack pointer*/
		if(optimize(n,m,root[i],sa,sb,&si)) root[i]->closed = 1;
	}
	
	/*vote for the path*/
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			votem[i][j] = 0;/*initialzie the vote matrix*/
	for(i=0;i<n;i++) vote(root[i],m,n);
	
	/*select the final result*/
	int re[MAX_SIZE][2];/*store the result*/ 
	select(re,m,n);
	/*print the result*/
	for(i=0;i<m;i++) printf("(%d,%d)\n",re[i][0],re[i][1]);
	
	return 0;
}

/*
* input: NULL;
* output: an address of an blank node of binary tree
* 
*/
NODE newnode(void)
{
	//initialize the node
	NODE n;
	n = (NODE)malloc(sizeof(*(NODE)NULL));	//call the space
	n->ai = n->bi = n->closed = 0;
	int i;
	for(i=0;i<MAX_SIZE;i++) n->children[i] = NULL;/*initialize the whole array*/
	n->parent = NULL;
	
	return n;
}
/*
*construct the voting tree
*input max n, max m, parent node;
*return wether the tree construct successfully or not 0 or 1
*/
int construct(int n, int m, NODE parent, int bini)
{
	//exit
	if(parent->ai == m-1) return 0;/*graph point in a is run out which mean construct successfully*/
	if(parent->bi==n+bini-1) return 1;/* graph point in b is run out*/
	//constructor
	int i,j;
	NODE child[MAX_SIZE];
	/*i is the step that gb procceed*/
	int remainder = (n-(parent->bi-bini))-(m-parent->ai);
	for(j=0,i=0;i<=remainder;j++,i++)
	{
		/*initialzie*/
		child[i] = newnode();
		child[i]->parent = parent;
		parent->children[j] = child[i];
		child[i]->ai = parent->ai+1;
		/*graph b*/
		child[i]->bi = parent->bi+i+1;
		if(construct(n,m,child[i],bini)) break;/*recursive step*/
	}
	
	return 0;
}

/*
*optimize the voting tree, in other word delete the unessessary node;
*/
int optimize(int n, int m, NODE parent,int ai[], int bi[], int *si)
{
	int i;
	int flag_close = 1;
	NODE child;
	/*push*/
	ai[*si] = parent->ai;bi[*si] = parent->bi;
	*si+=1;
	if(parent->children[0]==NULL)/*leaf node*/
	{
		if(sim(ai,bi,m,n)<TOL) return 1;/*exit*/
		return 0;/*dose not delete*/
	}
	for(i=0;parent->children[i]!=NULL;i++)
	{
		child = parent->children[i];
		if(optimize(n,m,child,ai,bi,si)) child->closed = 1;
		*si-=1;/*pop*/
		if(child->closed==0) flag_close = 0;/*if there is a child node unclosed*/
	}
	if(flag_close) return 1;/*the parent will close if there are no unclosed child*/
	return 0;
}

/*
*determine the similarity between ga and gb
*/
double sim(int ai[], int bi[], int m, int n)
{
	double similarity;
	double sim_degree, sim_edge;
	double la,lb,lc;
	double da,db;
	int i;
	
	if(n<3) return 1;/*line and point for no use to compare*/
	sim_degree = sim_edge = 0;
	/*elimate the case of i=n-1*/
	for(i=0;i<m;i++)
	{
		/*get the two length*/
		la = length(ai[i],ai[(i+1)%m],a);
		lb = length(bi[i]%n,bi[(i+1)%m]%n,b);
		sim_edge += fabs(la-lb)/Max(la,lb);/*calc the sim_edge of two correspondenc edge*/
	}
	sim_edge = 1-sim_edge/m;/*calc the total sim_edge*/
	
	for(i=0;i<m;i++)
	{
		/*generate triangel A to get the angle*/
		la = length(ai[i],ai[(i+1)%m],a);
		lb = length(ai[(i+1)%m],ai[(i+2)%m],a);
		lc = length(ai[(i+2)%m],ai[i],a);
		da = angle(la,lb,lc);/*get angle*/
		/*generate triangel B to get the angle*/
		la = length(bi[i]%n,bi[(i+1)%m]%n,b);
		lb = length(bi[(i+1)%m]%n,bi[(i+2)%m]%n,b);
		lc = length(bi[(i+2)%m]%n,bi[i]%n,b);
		db = angle(la,lb,lc);/*get angle*/
		sim_degree+= fabs(da-db)/180;/*calc the similarity of two correspondence angle*/
	}
	sim_degree = 1-sim_degree/m;/*calc the total*/
	similarity = 0.4*sim_edge+0.6*sim_degree;/*weighed average*/
	return similarity;
}
/*
*get length 
*input the index of ai and bi in x and x itself
*output the Euclid distance of two point 
*/
double length(int ai, int bi, double x[][2])
{
	double dx, dy;
	dx = x[ai][0] - x[bi][0];
	dy = x[ai][1] - x[bi][1];
	return sqrt(dx*dx+dy*dy);
}
/*
* use cosine law and return the angle
*input the length of three edge of triangle
*output the degree of the angle
*/
double angle(double a, double b, double c)
{
	return acos((b*b+c*c-a*a)/(2*b*c))*180/pi;
}

/*
*return the value of valid children
*/
int vote(NODE parent,int m,int n)
{
	int i,ai,bi;
	if(parent->closed) return 1; /* if parent is closed then skip the node*/
	ai = parent->ai;bi = parent->bi%n;/* get the location in votematrix*/
	NODE child;
	/*traverse all it's children*/
	for(i=0;parent->children[i]!=NULL;i++)
	{
		child = parent->children[i];
		if(vote(child,m,n)) continue;
		votem[ai][bi]++;/*if it has a child then it has a vote*/
	}
	if(parent->children[0]==NULL) votem[ai][bi]++;/*if it has no child it's a leaf and it has a vote*/
	return 0;
}
/*
*return the selected result form the voting table
*/
void select(int re[][2],int m,int n)
{
	int i, j, max;
	max = 0;
	/*special case i=0*/
	for(j=0;j<n;j++)
		if(votem[0][j]>votem[0][max]) max = j;
	re[0][0]=1;re[0][1]=max+1;
	/*other cases*/
	for(i=1;i<m;i++)
	{
		max = re[i-1][1]+1;
		/*get the max of each row*/
		for(j=re[i-1][1];j<re[0][1]+n;j++)
		{
			if(votem[i][j]>votem[i][max]) max = j;
		}
		re[i][0]=i+1;re[i][1]=max%n+1;
	}
}

# Algorithm
+ input
+ output (at least one output)
+ definitness
+ finiteness
+ effectiveness

# Compare the algotithms



# 数据
+ 数据规模不同有不同的组织方式
+ 解决问题的效率和数据的组织方式有关
+ 解决问题的效率与空间的效率有关

# 数据结构
+ 定义： 数据对象在计算机中的组织方式
	1) **逻辑结构**
	2) **物理存储结构**
+ 与一系列加在其上的**操作**相关联
+ 如何实现这些操作称之为**算法**
## 抽象数据类型（Abstract Data Type）
+ 数据类型
	1) 数据对象集
	2) 数据集合相关联的操作集
+ 抽象：
	1) 描述数据结构与实现形式无关
+ e,g, “矩阵”的抽象数据类型定义
+ `#define ElementType int` 将某种数据类型抽象为ElementType可以防止数据类型更改的繁琐
## 算法（Algorithm）
+ 有限指令集
+ 接受输入
+ 一定产生输出
+ 一定在有限步骤后终止
## 算法好坏的评定
+ 空间复杂度S(n)
+ 时间复杂度T(n)
+ $2^n > n^2 > nlogn > n > logn$
+ 分析效率时， 关注两种复杂度
	1) 最坏情况复杂度$T_{worst}(n)$
	2) 平均复杂度$T_{avg}(n)$
+ for复杂度： $循环层数*循环体复杂度$
+ if-else复杂度：取max
## 线性结构
### 线性表
1) 抽象数据类型描述
+ 类型名称：线性表(List)
+ 数据对象集：线性表是$n(\geq 0)$ 个元素构成的有序序列
+ 操作集：线性表$L \in List$， 整数$i$ 表示位置，元素$X\in ElementType$
	+ 基本操作：
		1) `List MakeEmpty()`初始化一个空线性表L
		2) `ElementType FindKth(int K, List L)`根据位序K，返回相应元素
		3) `int FInd(ElementType X, List L)`在线性表L中查找X第一次出现的位置
		4) `void Insert(ElemntType X, int i, List L)`在位序i前插入一个新元素X
		5) `void Delete(int i, List L)`删除指定位序i的元素
		6) `int Length(List L)`返回线性表L的长度n
2) 存储方法
	1) 顺序存储实现
		1) 数组
		2) 链表
+ 求表长
``` C
		int Length(List PtrL){
			List p = PtrL;
			int i = 0;
			while(p){
				p = p->next;
				i++;
			}
			return i;
		}
```
+ 返回相应元素
``` C
		List FindKth(int k, List PtrL){//按序号
			List p = PtrL;
			int i = 1;
			while(p != NULL && i < k){
				p = p->next;
				i++;
			}
			if(i == k)
				return p;
			else 
				return NULL;
		}
```

``` C
		List FindKth(ElementType X, List PtrL){//按值
			List p = PtrL;
			int i = 1;
			while(p != NULL && p->Data != X)
				p = p->next;
			return p;
		}
```
+ 插入
``` C
		List Insert(ElementType X, int i, List PtrL){
			List p, s;
			if(i == 1){
				s = (List)malloc(sizeof(struct LNode));
				s->Data = X;
				s->next = PtrL;
				return s;
			}
			p = FIndKth(i - 1, PtrL);
			if(p == NULL){//结点i-1不存在，无法插入
				printf("error i");
				return NULL;
			}else{
				s = (List)malloc(sizeof(struct LNode));
				s->Data = X;
				s->next = p->next;
				p->next = s;
				return PtrL;
			}
		}
```
+ 删除
``` C
		//malloc申请的空间需要free
		List Delete(int i, List PtrL){
			List p, s;
			if(i == 1){//删除第一个结点
				s = PtrL;
				if(PtrL != NULL)
					PtrL = PtrL->next;
				else
					return NULL;
				free(s);
				return PtrL;
			}
			p = FindKth(i - 1, PtrL);
			if(p == NULL){
				printf("nonexist i-1");
				return NULL;
			}else if(p->next == NULL){
				printf("nonexist i");
				return NULL;
			}else{
				s = p->next;//指向需删除结点
				p->next = s->next;//删除
				free(s);//释放空间
				return PtrL;
			}
		}
```
+ 广义表(Generalized List)：(多重链表的一种)
	+ 广义表是线性表的推广
	+ 对于线性表而言， n个元素都是基本的单元素
	+ 广义表中，这些元素可以是氮元素也可以是另一个广义表
``` C
		typedef struct GNode *GList;
		struct GNode{
			int Tag;//标志域，0表示结点为单元素，1表示结点是广义表；
			union{//子表指针域SubList与单元素数据域Data复用，即共用存储空间
				ElementType Data;
				GList SubList;
			}URegion;
			GList next;//指向下一个结点
		};
```
+ 多重链表：
	+ 链表中的结点可能同时隶属于多个链
	+ 结点的**指针域会有多个**
	+ **包含两个指针域的链表不一定是多重链表**，如双向链表就不是多重链表
	+ 树、图都可用多重链表表示
### 矩阵的表示
+ 矩阵可用二维数组表示，但有缺陷：
	1) 数组的大小需要提前确定
	2) 对于“稀疏矩阵”，造成大量空间浪费
+ 多重链表——十字链表
	1) 只存储矩阵非0元素项
		+ 结点的数据域： 行坐标Row、列坐标Col、数值Value
	2) 每个结点通过两个指针域，把同行、同列串起来
		+ 行指针Right
		+ 列指针Down
	如图:
	[cross list](D:\code\Learning\DS\DS\cross_list.png)
### 堆栈
1. 数组实现
``` C
#define MaxSize 80//the max number of element
#define ElementType int//the data type
typedef struct SNode *stack{
	ElementType Data[MaxSize];//元素
	int Top;//栈顶, Top = -1代表栈空
};
//入栈
void push(stack PtrS, ElementType item){
	if(PtrS->Top == MaxSize - 1){
		printf("full stack");
		return;
	}else{
		PtrS->Data[++(PtrS->Top)] = item;//入栈
		return;
	}
}
//出栈
ElementType pop(stack PtrS){
	if(PtrS->Top == -1){
		printf("NULL");
		return -1;//错误
	}
	else{
		return PtrS->Data[(PtrS->Top)--];
	}
}
```
2. 链表实现
``` C
#define MaxSize 80
#define ElementType int
typedef struct SNode *stack{
	ElementType Data;
	struct SNode *next;
};
stack CreateStack(){
	stack S;
	S = (stack)malloc(sizeof(struct SNode));
	S->next = NULL;
	return S;
}
int IsEmpty(stack S){
	return (S->next == NULL);//next = NULL即为栈空
}
//入栈
void push(ElementType item, stack S){//链表实时申请，无需判断“满”
	struct SNode *tmp;
	tmp = (stack)malloc(sizeof(struct SNode));
	tmp->Data = item;
	tmp->next = s->next;
	s->next = tmp;//插入链表头
}
//出栈
ElementType Pop(stack S){//pop头指针的后一个(头指针为空预留给下一个数据)
	struct SNode *delete;
	ElementType TopElem;
	if(IsEmpty(S)){
		printf("NULL");
		return NULL;
	}else{
		delete = S->next;
		S->next = delete->next;
		TopElem = delete->Data;
		free(delete);
		return TopElem;
	}
}
```
## 队列
1. 循环队列
``` C
#define
```

## 树
+ degree of a tree: $max_{node\in tree} \{ degree(node)\}$
+ path from $n_i$ to $n_k$
+ length of path
+ depth of $n_i$ : from root to $n_i$
+ height of $n_i$ : length of the longest path from $n_i$ to a leaf
## Tree Traversals——visit each node exactly once
+ preorder
+ postorder
+ inorder
### 查找
1. 静态查找：集合中的记录是固定的(没有插入和删除，只有插入)
	1) 顺序查找
		+ 放置“哨兵”（将查找值作为`Element[0]`，用于查不到时退出循环）
	``` C
	int SequentialSearch(List Tb1, ElementType K){
		int i;
		Tb1->Element[0] = K;//建立哨兵
		for(i = Tb1->length; Tb1->Element[i] != K; i--);
		return i;
	}
```
	2) 二分查找
2. 动态查找：集合中的记录是动态变化的(可能会有插入和删除)

+ 树的定义： n个结点构成的有限集合
+ $n=0$称为空树
+ 非空树($n>0$),具有如下性质：
	1) 树具有根（root）
	2) 其余结点可分为多个**互不相交**的有限集，这些有限集是子树
### 儿子-兄弟表示法
+ 第一个指针域指向长子，第二个指针域指向下一个兄弟（优点：结构统一）
+ 于是次子-次子经过的结点数和长子-长子-长子-长子相同
### 二叉树
1. 斜二叉树
2. 完美二叉树（满二叉树）
3. 完全二叉树（满二叉树缺右下侧结点）
+ 存储结构
1) 顺序存储结构
	1) 数组：对满二叉树好使，对普通二叉树空间浪费严重
	2) 链表：如儿子-兄弟表示法
+ 遍历方法
	+ 先序（preorder）：根-左-右
	+ 中序（inorder）：左-根-右
	+ 后序（postorder）：左-右-根
	+ 递归 与 非递归（stack）
	+ stack：遇到可能为子树的先压栈，不满足子树条件则出栈
### 二叉搜索树
+ 可以为空，非空则有以下性质：
1. 非空左子树的所有键值小于其根节点的键值
2. 非空右子树的所有键值大于其根节点的键值
3. 左、右子树都是二叉搜索树
+ 函数
``` C
typedef struct BT *BinTree{
	ElementType Data;
	struct BT *Left;
	struct BT *Right;
}; 
```
1. Find(查找效率取决于树的高度)
+ 最大元素一定在最右侧
+ 最小元素一定在最左侧
``` C
	Position Find(ElementType X, BinTree BST){
		if(!BST) 
			return NULL;
		if(X > BST->Data)//小了，往右继续找
			return Find(X, BST->Right);
		else if(X < BST->Data)
			return Find(X, BST->Left); 
		else
			return BST;
	}

	//循环
	Position Find(ElementType X, BinTree BST){
		while(BST){
			if(X > BST->Data)
				BST = BST->Right;
			else if(X < BST->Data)
				BST = BST->Left;
			else
				return BST;
		}
		return NULL;
	}
```

# 前缀和
## 一维数组前缀和
+ 对数组`a[10] = {1, 3, 4, 6, 3, 7, 9, 2, 10, 5}`进行前缀和操作得到
+ `sum[10] = {1, 4, 8, 14, 17, 24, 33, 35, 45, 50}`
+ O(1)提前处理和
## 二维数组前缀和
+ 对数组`a[5][5] = {1, 2, 3, 5, 4, 7, 8, 9, 10, 13, 12, 15, 14, 11, 16, 17, 18, 19, 20, 24, 23, 21, 25, 22` 进行三次前缀和操作

## Priority Queues(Heaps)
+ 定义：
1) 是完全二叉树
2) 任意节点到叶节点都必须是递增（最小堆）或递减（最大堆）的
+ delete the element with the highest/lowest priority
+ Oprerations:
3) Initialize
4) Insert
5) Deletemin
6) Findmin
+ data structure
	+ linked list
	+ array
+ AVL tree
### binary heap
+ definition: a binary tree with N node and height h is complete iff its nodes correspnond to the nodes from 1 to n int the perfect binnary tree(not must to be a full binary tree)
### Heap order property
### 最大堆的最小元
+ 必须位叶节点中的一个
+ e.g. In a max-heap with n (>1) elements, the array index of the minimum key may be __. A.1 B.⌊n/2⌋−1 C.⌊n/2⌋ D.⌊n/2⌋+2
+ 由于n/2为叶节点的父节点，故只有往右找（直至下一行）才有可能出现最小元素


### The disjoint set ADT
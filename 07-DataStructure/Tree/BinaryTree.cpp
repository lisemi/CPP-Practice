/*
1）在二叉树的第i层上最多有2i-1 个节点 。（i>=1）
2）二叉树中如果深度为k,那么最多有2k-1个节点。(k>=1）
3）n0=n2+1 n0表示度数为0的节点数，n2表示度数为2的节点数。
4）在完全二叉树中，具有n个节点的完全二叉树的深度为[log2n]+1，其中[log2n]是向下取整。
5）若对含 n 个结点的完全二叉树从上到下且从左至右进行 1 至 n 的编号，则对完全二叉树中任意一个编号为 i 的结点有如下特性：
	1) 若 i=1，则该结点是二叉树的根，无双亲, 否则，编号为 [i/2] 的结点为其双亲结点;
	2) 若 2i>n，则该结点无左孩子， 否则，编号为 2i 的结点为其左孩子结点；
	3) 若 2i+1>n，则该结点无右孩子结点， 否则，编号为2i+1 的结点为其右孩子结点。
遍历：
	前序遍历通俗的说就是从二叉树的根结点出发，当第一次到达结点时就输出结点数据，按照先向左在向右的方向访问。
	中序遍历就是从二叉树的根结点出发，当第二次到达结点时就输出结点数据，按照先向左在向右的方向访问。
	后序遍历就是从二叉树的根结点出发，当第三次到达结点时就输出结点数据，按照先向左在向右的方向访问。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define SUCCESS 1
#define UNSUCCESS 0
#define dataNum 5
int i = 0;
char data[dataNum] = { 'A', 'B', 'C', 'D', 'E' };

typedef int Status;
typedef char TElemType;

// 二叉树结构
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

// 初始化一个空树
void InitBiTree(BiTree &T){
	T = NULL;
}

// 构建二叉树
BiTree MakeBiTree(TElemType e, BiTree L, BiTree R){
	BiTree t;
	t = (BiTree)malloc(sizeof(BiTNode));
	if (NULL == t) return NULL;
	t->data = e;
	t->lchild = L;
	t->rchild = R;
	return t;
}

// 替换左子树
Status ReplaceLeft(BiTree &T, BiTree &LT) {
	BiTree temp;
	if (NULL == T) return ERROR;
	temp = T->lchild;
	T->lchild = LT;
	LT = temp;
	return OK;
}

// 替换右子树
Status ReplaceRight(BiTree &T, BiTree &RT) {
	BiTree temp;
	if (NULL == T) return ERROR;
	temp = T->rchild;
	T->rchild = RT;
	RT = temp;
	return OK;
}

// 访问结点
Status visit(TElemType e){
	printf("%c", e);
	return OK;
}

// 对二叉树T求叶子结点数目
int countLeaves(BiTree T){
	int l = 0, r = 0;
	if (NULL == T) return 0;
	if (NULL == T->lchild && NULL == T->rchild) return 1;

	// 求左子树叶子数目
	l = countLeaves(T->lchild);
	// 求右子树叶子数目
	r = countLeaves(T->rchild);
	// 组合
	return r + l;
}

// 1、2、3次序无关，因为二叉树遍历的路径总是一样的。
void countLeaves_v2(BiTree T, int* num){
	if (NULL == T) return;
	if (NULL == T->lchild && NULL == T->rchild) {   //#1
		(*num)++;
	}
	countLeaves_v2(T->lchild, num);  // #2
	countLeaves_v2(T->rchild, num);  // #3
}

// 层次遍历：树的高度
int depTraverse(BiTree T, int& dep){
	if (NULL == T) return ERROR;

	dep = 1+ ((depTraverse(T->lchild, dep) > depTraverse(T->rchild, dep)) ? depTraverse(T->lchild, dep) : depTraverse(T->rchild, dep));
	return dep;
}

// 遍历层次
void levTraverse(BiTree T, Status(*visit)(TElemType e), int lev){
	if (NULL == T) return;
	visit(T->data);
	printf("的层次是%d\n", lev);

	levTraverse(T->lchild, visit, ++lev);
	levTraverse(T->rchild, visit, lev);
}

// 二叉树判空
Status BiTreeEmpty(BiTree T){
	if (NULL == T) return TRUE;
	return FALSE;
}

// 打断二叉树：置空二叉树的左右子树
Status BreakBiTree(BiTree &T, BiTree &L, BiTree &R){
	if (NULL == T) return ERROR;
	L = T->lchild;
	R = T->rchild;
	T->lchild = NULL;
	T->rchild = NULL;
	return OK;
}

// 合并二叉树
void UnionBiTree(BiTree &Ttemp)
{
	BiTree L = NULL, R = NULL;
	L = MakeBiTree(data[i++], NULL, NULL);
	R = MakeBiTree(data[i++], NULL, NULL);
	//ReplaceLeft(Ttemp, L);
	//ReplaceRight(Ttemp, R);
	Ttemp->lchild = L;
	Ttemp->rchild = R;
}

// 前序遍历
void preOrderTraverse(BiTree T, Status(*visit)(TElemType e)) {
	if (NULL == T) return;
	visit(T->data);
	preOrderTraverse(T->lchild, visit);
	preOrderTraverse(T->rchild, visit);
}

// 中序遍历
void inOrderTraverse(BiTree& T, Status(*visit)(TElemType e)) {
	if (NULL == T) return;
	inOrderTraverse(T->lchild, visit);
	visit(T->data);
	inOrderTraverse(T->rchild, visit);
}

// 后序遍历
void postOrderTraverse(BiTree& T, Status(*visit)(TElemType e)) {
	if (NULL == T) return;
	postOrderTraverse(T->lchild, visit);
	postOrderTraverse(T->rchild, visit);
	visit(T->data);
}

// 复制树
BiTree copyTree(BiTree& T) {
	if (NULL == T)	return NULL;
	BiTNode* newTl = NULL;
	BiTNode* newTr = NULL;
	if (T->lchild)
		newTl = copyTree(T->lchild);
	else
		newTl = NULL;
	if (T->rchild)
		newTr = copyTree(T->rchild);
	else
		newTr = NULL;
	// 给树节点分配空间
	BiTree newTree = (BiTree)malloc(sizeof(BiTNode));
	if (NULL == newTree)	return NULL;
	newTree->lchild = newTl;
	newTree->rchild = newTr;
	newTree->data = T->data;

	return newTree;
}

/*
非递归中序遍历方法：
步骤1：
如果结点有左子树，该结点入栈；
如果结点没有左子树，访问该结点；
步骤2：
如果结点有右子树，重复步骤1；
如果结点没有右子树（结点访问完毕），根据栈顶指示回退，访问栈顶元素，并访问右子树，重复步骤1
如果栈为空，表示遍历结束。
*/

// 步骤1
// 获取中序遍历的首次访问内容的节点（访问内容起点）
BiTNode* getStartNode(BiTree T, std::stack<BiTNode*>& s) {
	if (NULL == T)	return NULL;
	while (T->lchild  != NULL) {
		s.push(T);
		T = T->lchild;
	}
	return T;
}

void inOrder_nonRecu(BiTree& T, Status(*visit)(TElemType e)) {
	if (NULL == T)	return;
	std::stack<BiTNode*> s;
	BiTree t = getStartNode(T, s);
	while (t != NULL) {
		//visit(t->data);
		printf(" %c", t->data);
		if (t->rchild != NULL) {  // 如果结点有右子树，重复步骤1；
			t = getStartNode(t->rchild, s);
		}
		else if (!s.empty()) { // 如果结点没有右子树（结点访问完毕），根据栈顶指示回退，访问栈顶元素，并访问右子树，重复步骤1
			t = s.top();
			s.pop();
		}
		else {   // 如果t没有右子树 并且栈为空  
			t = NULL;
		}
	}
	printf("\n");
}

// #号树创建方法（让节点都变成度数为2的树）#对应35，属于先序
BiTree createTree_35() {
	BiTree T=NULL;
	BiTNode* pL = NULL;
	BiTNode* pR = NULL;
	char ch;
	scanf_s("%c", &ch);  // c++ cin >> ch;
	if (ch == '#')
		return NULL;
	else {
		T = (BiTree)malloc(sizeof(BiTNode));
		if (NULL == T)	return NULL;
		memset(T, 0, sizeof(BiTNode));
		T->data = ch;
		// method one
		T->lchild = (pL = createTree_35())==NULL ? NULL : pL;
		T->rchild = (pR = createTree_35())==NULL ? NULL : pR;
		// method two，因为函数上面已经判断是否返回NULL了，其实这里不需要再判断了。
		//T->lchild = createTree_35();
		//T->rchild = createTree_35();
		return T;
	}
}

// 释放树，使用后续方法；
void freeTree(BiTree T) {
	if (NULL == T)	return;
	if (T->lchild) {
		freeTree(T->lchild);
		T->lchild = NULL;
	}
	if (T->rchild) {
		freeTree(T->rchild);
		T->rchild = NULL;
	}
	if (T == NULL) {
		free(T);
		T = NULL;
	}
}

int main1()
{
	Status(*visit1)(TElemType);
	visit1 = visit;

	// #号创建二叉树
	{
		BiTree newT = NULL;
		newT = createTree_35();
		printf("#号 == inOrderTraverse:\n");
		inOrderTraverse(newT, visit1);
	}

	BiTree T = NULL, Ttemp = NULL;
	InitBiTree(T);
	if (TRUE == BiTreeEmpty(T)) printf("\n初始化T为空\n");
	else printf("初始化T不为空\n");

	T = MakeBiTree(data[i++], NULL, NULL);
	Ttemp = T;
	UnionBiTree(Ttemp);
	Ttemp = T->lchild;
	UnionBiTree(Ttemp);

	// 非递归遍历
	{
		printf("non-recursive ninOrder\n");
		inOrder_nonRecu(T, visit1);
	}
	// 递归遍历
	{
		printf("\npreOrderTraverse:\n");
		preOrderTraverse(T, visit1);
		printf("\ninOrderTraverse:\n");
		inOrderTraverse(T, visit1);
		printf("\npostOrderTraverse:\n");
		postOrderTraverse(T, visit1);
	}
	// copy
	{
		BiTree temp = NULL;
		temp = copyTree(T);
		printf("\nafter copy preOrderTraverse:\n");
		preOrderTraverse(temp, visit1);
	}
	// 其他
	{
		int num = 0;
		countLeaves_v2(T, &num);
		printf("\nLeaves 叶子节点是：%d\n", countLeaves(T));
		printf("Leaves_v2 叶子结点是：%d\n", num);
		printf("树高度：%d\n", depTraverse(T, num));
	}
	while (1);
	getchar();
	return 0;
}
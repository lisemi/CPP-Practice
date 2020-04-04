﻿/**
* @author huihut
* @E-mail:huihut@outlook.com
* @version 创建时间：2016年9月18日
* 说明：本程序实现了一个单链表。
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//5个常量定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

//类型定义
typedef int Status;
typedef int ElemType;

//测试程序长度定义
#define LONGTH 5

//链表的类型
typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

//创建包含n个元素的链表L，元素值存储在data数组中
Status createListR(LinkList &L, ElemType *data, int n) {
	LNode *p, *q;
	int i;
	if (n < 0) return ERROR;
	L = NULL;
	p = L;
	for (i = 0; i < n; i++){
		q = (LNode *)malloc(sizeof(LNode));
		if (NULL == q) return OVERFLOW;
		q->data = data[i];
		q->next = NULL;
		if (NULL == p) L = q;  	// 首次进入时,把L指向链表的头节点q
		else p->next = q;      	// 尾部插入节点
		p = q;					// 链表后移到最后节点
	}
	return OK;
}

//e从链表末尾插入链表
Status insertR(LinkList &L, ElemType &e) {
	LinkList p, q;

	if (NULL == (q = (LNode *)malloc(sizeof(LNode)))) return OVERFLOW;
	q->data = e;
	q->next = NULL;
	if (NULL == L) L = q;
	else{
		p = L;
		while (p->next != NULL){
			p = p->next;
		}
		p->next = q;
	}
	return OK;
}


//从链表头节点出链表到e
Status deleteL(LinkList &L, ElemType &e) {
	if (NULL == L) return ERROR;
	LinkList p;
	p = L;
	e = p->data;
	L = L->next;
	free(p);
	return OK;
}

Status lenght(LinkList &L) {
	LinkList p;
	p = L;
	int len = 0;
	while (p != NULL) {
		len++;
		p = p->next;
	}
	return len;
}

Status getData(LinkList &L, const int pos) {
	int step = 0;
	LinkList p = L;
	while (p != NULL) {
		if (step == pos)
			return p->data;
		step++;
		p = p->next;
	}
	return -1;
}

//遍历调用
Status visit(ElemType e) {
	printf("%d\t", e);
	return OK;
}

//遍历单链表
void ListTraverse_L(LinkList L, Status(*visit)(ElemType e)){
	if (NULL == L) return;
	for (LinkList p = L; NULL != p; p = p->next) {
		visit(p->data);
	}
}

int main() {
	int i;
	ElemType e, data[LONGTH] = { 1, 2, 3, 4, 5 };
	LinkList L;

	//显示测试值
	printf("---【单链表】---\n");
	printf("待测试元素为：\n");
	for (i = 0; i < LONGTH; i++) printf("%d\t", data[i]);
	printf("\n");

	//创建链表L
	printf("创建链表L\n");
	if (ERROR == createListR(L, data, LONGTH))
	{
		printf("创建链表L失败\n");
		return -1;
	}
	printf("成功创建包含%d个元素的链表L\n元素值存储在data数组中\n", LONGTH);

	//遍历单链表
	printf("此时链表中元素为：\n");
	ListTraverse_L(L, visit);

	printf("\n获取指定pos节点的数据\n");
	printf("pos data: %d\n", getData(L, 2));

	//从链表头节点出链表到e
	printf("\n出链表到e\n");
	deleteL(L, e);
	printf("出链表的元素为：%d\n", e);
	printf("此时链表中元素为：\n");

	//遍历单链表
	ListTraverse_L(L, visit);

	//e从链表末尾入链表
	printf("\ne入链表\n");
	insertR(L, e);
	printf("入链表的元素为：%d\n", e);
	printf("此时链表中元素为：\n");

	//遍历单链表
	ListTraverse_L(L, visit);
	printf("\n");

	getchar();
	return 0;
}
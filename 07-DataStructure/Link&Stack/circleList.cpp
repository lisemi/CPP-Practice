#include <stdio.h>
#include <malloc.h>
#include "circleList.h"

// 业务节点。
typedef struct _tag_CircleList{
	CircleListNode header;    // CircleListNode结构体next指针。
	CircleListNode* slider;   // 在非循环单链表里面没有个参数。
	int length;
} TCircleList;

CircleList* CircleList_Create() {// O(1)
	TCircleList* ret = (TCircleList*)malloc(sizeof(TCircleList));
	if (ret == NULL){
		return NULL;
	}

	ret->length = 0;
	ret->header.next = NULL;
	ret->slider = NULL;
	return ret;
}

void CircleList_Destroy(CircleList* list) {// O(1)
	if (list == NULL){
		return;
	}
	free(list);
}

void CircleList_Clear(CircleList* list) {// O(1)
	TCircleList* sList = (TCircleList*)list;
	if (sList == NULL){
		return;
	}
	sList->length = 0;
	sList->header.next = NULL;
	sList->slider = NULL;
}

int CircleList_Length(CircleList* list) {// O(1)
	TCircleList* sList = (TCircleList*)list;
	int ret = -1;
	if (list == NULL){
		return ret;
	}
	ret = sList->length;
	return ret;
}

int CircleList_Insert(CircleList* list, CircleListNode* node, int pos) {// O(n)
	int i = 0;
	TCircleList* sList = (TCircleList*)list;   // 辅助指针

	if (list == NULL || node == NULL || pos<0){
		return -1;
	}

	CircleListNode* current = (CircleListNode*)sList;   // 把业务节点转换成链节点，获得当前指针；当前指针一开始指向链表头部
	// 等同于：CircleListNode* current = (CircleListNode*)(&sList->header);
	// 指针跳转到指定位置，pos=0头插入下面不跳步
	for (i = 0; (i<pos) && (current->next != NULL); i++) {
		current = current->next;
	}

	//插入动作，current->next 0号节点的地址
	node->next = current->next;  //1
	current->next = node;        //2

	//若第一次插入节点，让游标指向0号节点。
	if (sList->length == 0){
		sList->slider = node;
	}

	sList->length++;

	// 若头插法 current仍然指向头部，因为头插入法pos等于0 ，因此前面的next没有执行。
	//（原因是：跳0步，没有跳走）
	if (current == (CircleListNode*)sList){
		//获取最后一个元素
		CircleListNode* last = CircleList_Get(sList, sList->length - 1);
		last->next = current->next; //3
	}

	return 0;
}

CircleListNode* CircleList_Get(CircleList* list, int pos) {// O(n)
	TCircleList* sList = (TCircleList*)list;   // 辅助指针
	CircleListNode* ret = NULL;                // 用于保存查找的节点
	int i = 0;

	if (list == NULL || pos<0){
		return NULL;
	}
	CircleListNode* current = (CircleListNode*)sList;
	//CircleListNode* current = (CircleListNode*)(&sList->header);  // 同上

	for (i = 0; i<pos; i++){
		current = current->next;
	}
	ret = current->next;

	return ret;
}

CircleListNode* CircleList_Delete(CircleList* list, int pos) {// O(n)
	TCircleList* sList = (TCircleList*)list;   // 辅助指针
	CircleListNode* ret = NULL;                // 保存删除节点，返回给用户释放空间
	int i = 0;

	if ((sList != NULL) && (pos >= 0) && (sList->length > 0)){
		CircleListNode* current = (CircleListNode*)sList;       // 辅助指针，转换指针。
		CircleListNode* last = NULL;
		// 当前指针移动
		for (i = 0; i<pos; i++){
			current = current->next;
		}

		//若删除第一个元素（头结点）
		if (current == (CircleListNode*)sList){
			last = (CircleListNode*)CircleList_Get(sList, sList->length - 1);
		}

		//求要删除的元素
		ret = current->next;
		current->next = ret->next;

		sList->length--;

		//判断链表是否为空，删除第一个元素（头节点）时需要
		if (last != NULL){
			sList->header.next = ret->next;  // 第一个节点被删除，游标节点的头部要后移
			last->next = ret->next;          // 头节点删除第二步
		}

		//若删除的元素为游标所指的元素
		if (sList->slider == ret){
			sList->slider = ret->next;       // 游标后移，因为原来的第一个节点已经被删除。
		}

		//若删除元素后，链表长度为0
		if (sList->length == 0){
			sList->header.next = NULL;
			sList->slider = NULL;
		}
	}
	return ret;
}
// 以上操作与非循环单链表大体相同。

// 以下函数与游标有关
CircleListNode* CircleList_DeleteNode(CircleList* list, CircleListNode* node) {// O(n)
	TCircleList* sList = (TCircleList*)list;
	CircleListNode* ret = NULL;
	int i = 0;

	if (sList != NULL){
		CircleListNode* current = (CircleListNode*)sList;

		//查找node在循环链表中的位置i
		for (i = 0; i<sList->length; i++){
			if (current->next == node){
				ret = current->next;
				break;
			}
			current = current->next;
		}

		//如果ret找到，根据i去删除	
		if (ret != NULL){
			CircleList_Delete(sList, i);
		}
	}

	return ret;
}

CircleListNode* CircleList_Reset(CircleList* list){ // O(1)
	TCircleList* sList = (TCircleList*)list;
	CircleListNode* ret = NULL;

	if (sList != NULL)
	{
		sList->slider = sList->header.next;
		ret = sList->slider;
	}

	return ret;
}

CircleListNode* CircleList_Current(CircleList* list){ // O(1)
	TCircleList* sList = (TCircleList*)list;
	CircleListNode* ret = NULL;

	if (sList != NULL)
	{
		ret = sList->slider;
	}

	return ret;
}

//把当前位置返回，并且游标下移
CircleListNode* CircleList_Next(CircleList* list) { // O(1)
	TCircleList* sList = (TCircleList*)list;
	CircleListNode* ret = NULL;

	if ((sList != NULL) && (sList->slider != NULL)){
		ret = sList->slider;
		sList->slider = ret->next;
	}

	return ret;
}

struct Value{
	CircleListNode circlenode;
	int v;
};

struct Value2{
	CircleListNode circlenode;
	int v;
	int v2;
};

int main(int argc, char *argv[]){
	CircleList* list = CircleList_Create();

	struct Value v1;
	struct Value v2;
	struct Value v3;
	struct Value v4;
	struct Value v5;
	struct Value v6;
	struct Value v7;
	struct Value v8;
	struct Value2 vv1;

	int i = 0;

	v1.v = 1;
	v2.v = 2;
	v3.v = 3;
	v4.v = 4;
	v5.v = 5;
	v6.v = 6;
	v7.v = 7;
	v8.v = 8;

	vv1.v = 11;
	vv1.v2 = 21;

	CircleList_Insert(list, (CircleListNode*)&vv1, 0);
	CircleList_Insert(list, (CircleListNode*)&v2, 0);
	CircleList_Insert(list, (CircleListNode*)&v3, 0);
	CircleList_Insert(list, (CircleListNode*)&v4, 0);

	for (i = 0; i<2 * CircleList_Length(list); i++) {//怎么样证明是循环链表
		struct Value* pv = (struct Value*)CircleList_Get(list, i);

		printf("%d\n", pv->v);
	}

	while (CircleList_Length(list) > 0){
		CircleList_Delete(list, 0);
	}
	printf("\n");
	CircleList_Destroy(list);
	getchar();

	return 0;
}

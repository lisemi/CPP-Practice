#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>


typedef int ElemType;

typedef struct Node {
	ElemType data;//数据域
	int length;
	struct Node *next;//节点
}CircleList;

CircleList* GetNode(CircleList* list, int pos);

CircleList* CircleList_Create() {
	CircleList* L = (CircleList*)malloc(sizeof(CircleList));
	if (L == NULL) {
		return NULL;
	}
	L->next = NULL;
	L->data = 0;
	L->length = 0;
	return L;
}

 int Head_CircleList_Create(CircleList** L, ElemType e) {
	*L = (CircleList*)malloc(sizeof(CircleList));
	if (*L == NULL){
		return -1;
	}
	(*L)->next = *L;         // 指向自己

	CircleList* node = (CircleList*)sizeof(CircleList);
	if (NULL == node)	return -2;
	node->data = e;
	node->next = (*L)->next;
	(*L)->next = node;
	return 0;
}

 int Tail_CircleList_Create(CircleList** L, ElemType e) {
	 *L = (CircleList*)malloc(sizeof(CircleList));
	 if (*L == NULL) {
		 return -1;
	 }
	 CircleList* tail = *L;      // 指定尾节点。

	 CircleList* node = (CircleList*)sizeof(CircleList);
	 if (NULL == node)	return -2;
	 node->data = e;
	 tail->next = node;
	 tail = node;                // 尾节点指向新插入节点。
	 tail->next = *L;            // 循环链表尾节点指向head；
	 return 0;
 }


/**
* 功能：初始化链表
*/
void Init_List(CircleList* head) {
	head->next = head;
}

/**
* 功能：判断链表是否是空表
* 参数：链表头指针
* 返回值：true 是  false 否
*/
bool IsEmpty(CircleList *head) {
	if (head->next == head) {
		printf("CircleList为空表\n");
		return true;
	}
	return false;
}

/**
* 功能：获取链表长度
* 参数：链表地址
* 返回值：链表长度
*/
int Length_List(CircleList *head) {
	CircleList* p = head->next;
	int length = 0;
	while (p != head && p!=NULL) {
		p = p->next;
		length++;
	}
	return length;
}

/**
* 功能：遍历链表
* 参数：链表地址
*/
void Show_List(CircleList *head) {
	if (head == NULL) {
		printf("链表未初始化\n");
		return;
	}
	if (head->next == head) {
		printf("[]\n");
		return;
	}
	bool flag = true;
	printf("[");
	CircleList *p = head->next;//第一个节点
	while (p != head) {
		if (flag) {
			printf("%d", p->data);
			flag = false;
		}
		else {
			printf(",%d", p->data);
		}
		p = p->next;
	}
	printf("]\n");
}

/**
* 功能：向链表插入数据元素
* 参数：链表地址 下标  插入的元素
* 返回值：链表长度
*/
bool Insert_List(CircleList *head, int index, ElemType e) {
	if (head == NULL) {
		printf("链表未初始化\n");
		return false;
	}
	if (index<1 || index>Length_List(head) + 1) {
		printf("下标越界\n");
		return false;
	}
	//开始插入
	int i;
	CircleList* pre = head;
	//遍历获取到插入位置的前一个元素
	for (i = 1; i<index && (pre->next != head); i++) {
		pre = pre->next;
	}
	//校验
	if (!pre || i>index) {
		printf("搜索index位置元素失败\n");//已判断下标越界，不会存在这个问题
		return false;
	}
	CircleList* newNode = (CircleList*)malloc(sizeof(CircleList));
	newNode->data = e;
	newNode->next = pre->next;
	pre->next = newNode;
	return true;
}

int Insert_List_gtx(CircleList* list, ElemType e, int pos) // O(n)
{
	int i = 0;
	CircleList* sList = (CircleList*)list;

	if (list == NULL || e == NULL || pos<0) {
		return -1;
	}

	CircleList* current = (CircleList*)sList;
	// 头插入下面不跳步
	for (i = 0; (i<pos) && (current->next != NULL); i++) {
		current = current->next;
	}
	CircleList* node = (CircleList*)malloc(sizeof(CircleList));
	if (NULL == node)	return -1;
	//current->next 0号节点的地址
	node->data = e;
	node->next = current->next;  //1
	current->next = node;        //2

	//若第一次插入节点
	//if (sList->next == NULL) {
	//	sList->next = node;
	//}

	//若头插法 current仍然指向头部，因为头插入法pos等于0 ，因此前面的next没有执行。
	//（原因是：跳0步，没有跳走）
	if (current == (CircleList*)sList) {
		//获取最后一个元素
		CircleList* last = GetNode(sList, Length_List(sList) - 1);
		last->next = current->next; //3
	}

	return 0;
}

/**
* 功能：删除某个下标的数据元素
* 参数：链表地址 下标  删除的元素
* 返回值：链表长度
*/
bool Delete_List(CircleList *head, int index, ElemType *e) {
	if (head == NULL) {
		printf("链表未初始化\n");
		return false;
	}
	if (index<1 || index>Length_List(head)) {
		printf("下标越界\n");
		return false;
	}
	CircleList *pre, *temp;
	pre = head;
	int i = 1;
	//遍历获取到删除的前一个元素
	while (pre->next != head && i<index) {
		pre = pre->next;
		i++;
	}
	temp = pre->next;
	*e = temp->data;
	pre->next = temp->next;
	free(temp);
	return true;
}

/**
* 功能：查找元素，返回下标
* 参数：链表地址 元素
* 返回值: 下标 -1 为查找不到
*/
int Search_List(CircleList *head, ElemType e) {
	if (IsEmpty(head)) {
		return -1;
	}
	CircleList *p = head->next;//第一个节点
	int i = 1;
	while (p != head) {
		if (p->data == e) {
			return i;
		}
		p = p->next;
		i++;
	}
	return -1;
}


/**
* 功能：获取某个下标的元素
* 参数：链表地址 下标
* 返回值: true ,false
*/
bool GetElem(CircleList *head, int index, ElemType *e) {
	if (IsEmpty(head)) {
		return false;
	}
	if (index<1 || index>Length_List(head)) {
		printf("数组下标越界\n");
		return false;
	}
	CircleList *p = head->next;//第一个节点
	int j = 1;
	while ((p != head) && j<index) {
		p = p->next;
		j++;
	}
	if ((p == head) || j>index)return false;
	*e = p->data;
	return false;
}

CircleList* GetNode(CircleList* list, int pos) // O(n)
{
	if (list == NULL || pos<0 || pos > Length_List(list)){
		return NULL;
	}

	CircleList* current = (CircleList*)list;
	int i = 0;
	for (i = 0; i<pos; i++){
		current = current->next;
	}
	Node* ret = current->next;

	return ret;
}

/**
* 功能：清空线性表
* 参数：pList：链表地址
*/
bool Clear_List(CircleList* head) {
	CircleList *temp, *p;
	temp = head->next;//第一个节点
	while (temp != head) {
		p = temp->next;
		free(temp);
		temp = p;
	}
	head->next = head;
	return true;
}

int main(int argc, char* argv[]) {
	CircleList* L = CircleList_Create();

	Insert_List_gtx(L, 1, 0);
	Insert_List_gtx(L, 2, 0);
	Insert_List_gtx(L, 3, 0);
	Insert_List_gtx(L, 4, 0);
	Insert_List_gtx(L, 5, 0);

	Show_List(L);

	getchar();
	return 0;
}
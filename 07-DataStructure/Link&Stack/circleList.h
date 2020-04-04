#pragma once
#ifndef _CIRCLELIST_H_
#define _CIRCLELIST_H_

typedef void CircleList;

// 链节点，指包含一个next指针。用于连接业务节点成为一条链
typedef struct _tag_CircleListNode
{
	struct _tag_CircleListNode * next;
}CircleListNode;

CircleList* CircleList_Create();
void List_Destroy(CircleList* list);
void CircleList_Clear(CircleList* list);
int CircleList_Length(CircleList* list);
int CircleList_Insert(CircleList* list, CircleListNode* node, int pos);
CircleListNode* CircleList_Get(CircleList* list, int pos);
CircleListNode* CircleList_Delete(CircleList* list, int pos);

//add
CircleListNode* CircleList_DeleteNode(CircleList* list, CircleListNode* node);
CircleListNode* CircleList_Reset(CircleList* list);
CircleListNode* CircleList_Current(CircleList* list);
CircleListNode* CircleList_Next(CircleList* list);

#endif
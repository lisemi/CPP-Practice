#ifndef __RB_TREE__
#define __RB_TREE__
#pragma once
#include <iostream>
#include <functional>

using namespace std;

typedef int element;
enum class NodeColor:unsigned int {
	RED,
	BLACK
};

struct Node {
	Node() :value(0),color(NodeColor::RED),left(nullptr),right(nullptr),parent(nullptr) {}

	element value;
	NodeColor color;
	Node *left, *right, *parent;

	Node* grandfather() {
		if (nullptr == parent)	return nullptr;
		return parent->parent;
	}

	Node* uncle() {
		if (nullptr == grandfather())	return nullptr;
		if (parent == grandfather()->left)
			return grandfather()->right;
		else
			return grandfather()->left;
	}

	// 获取节点的兄弟节点。
	Node* sibling() {
		if (nullptr == parent)	return nullptr;
		if (parent->left == this)
			return parent->right;
		else
			return parent->left;
	}
};

class RBTree:private Node {
public:
	RBTree();
	~RBTree();
	bool isEmpty(const RBTree& root);
	int  clear(RBTree& root);
	int  insert(element e);
	int  del_value(element e);
	void inorder();

private:
	void visit(element e);
	int  inorder(const Node* root, std::function<void(element)> visit);
	int  rotate_left(Node *pivot);
	int  rotate_right(Node *pivot);
	void insert(Node* p, element e);
	int  insert_case(Node *node);
	Node* getSmallestChild(Node *p);
	void delete_case(Node *p);
	bool find_delete_node(Node *p, int data);
	void delete_node(Node *p);

	Node* m_root;
	Node* m_nil;
};

#endif

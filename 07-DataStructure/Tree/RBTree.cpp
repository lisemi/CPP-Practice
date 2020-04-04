#include "RBTree.h"


// public function
//===============================================================================
RBTree::RBTree():m_root(nullptr) {
	m_nil = new Node();
	m_nil->color = NodeColor::BLACK;
} 

RBTree::~RBTree() {
	if (m_root) delete m_root;
	if (m_nil)	delete m_nil;
}

bool RBTree::isEmpty(const RBTree& root) {
	if (m_root == nullptr)
		return true;
	else
		return false;
}

int RBTree::clear(RBTree& root) {

	return 0;
}

int RBTree::insert(element e) {
	if (m_root == nullptr) {
		m_root = new Node();
		m_root->value = e;
		m_root->color = NodeColor::BLACK;
		m_root->left = m_root->right = m_nil;
	}
	else
		insert(m_root, e);
	return 0;
}

int RBTree::del_value(element e) {
	if (m_root == nullptr)
		return -1;
	return find_delete_node(m_root, e);
}

void RBTree::inorder() {
	if (m_root == nullptr)
		return;
	//auto visit = std::bind(&RBTree::visit, this, std::placeholders ::_1)
	inorder(m_root, std::bind(&RBTree::visit, this, placeholders::_1));
}

// private function
//=============================================================
int RBTree::inorder(const Node *root, std::function<void(element)> visit) {
	if (root == m_nil)
		return -1;
	if (root->left)
		inorder(root->left, visit);
	visit(root->value);
	if (root->right)
		inorder(root->right, visit);
	return 0;
}

void RBTree::visit(element e) {
	cout << e << " ";
}

/*
步骤：
1）原支点被原支点的右子节点替代；
2）原支点成为了原支点右子节点的左子节点；
3）原支点的右子节点的左子节点成为原支点的右子节点。
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y                
*   /  \      --(左旋)-->           / \   
*  lx   y                          x  ry     
*     /   \                       /  \
*    ly   ry                     lx  ly  
* 参数：
* cur
pivot：对应图中的x
*/
int RBTree::rotate_left(Node* pivot) {

	Node* pR = pivot->right;        // 支点的右孩子

	pivot->right = pR->left;		// 支点的右孩子 的 左孩子 设为支点的右孩子
	if (pR->left != nullptr)
		pR->left->parent = pivot;
	pR->parent = pivot->parent;		// 支点右孩子替换了原支点位置，因此需要把原支点的father设置为新支点的father；

	if (pivot->parent == nullptr)	// 如果原支点的father节点为空，则新支点为根节点
		m_root = pR;
	else {							// 支点的father节点不为空
		if (pivot->parent->left == pivot)	// 如果原支点是左孩子
			pivot->parent->left = pR;
		else
			pivot->parent->right = pR;
	}
	pR->left = pivot;		// 将原支点设为 原支点的右孩子的左孩子；
	pivot->parent = pR;     // 将原支点的father 设为原节点的有孩子；
	return 0;
}

/*
步骤：
	将y的左子树绕y顺时针旋转，使得y的左子树成为y的父亲，同时修改相关节点的引用
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x                  
*         /  \      --(右旋)-->            /  \              
*        x   ry                           lx   y  
*       / \                                   / \               
*      lx  rx                                rx  ry
* pivot：对应图中的y
*/
int RBTree::rotate_right(Node *pivot) {

	Node* pL = pivot->left;		//#0 保存支点的左孩子，对应图中x

	pivot->left = pL->right;	//#1 将新支点（x）的右孩子设为原支点（y）的左孩子
	if (pL->right != nullptr)
		pL->right->parent = pivot;	// #2，与#1为一对，如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
	//// 将 “y的父亲” 设为 “x的父亲”
	pL->parent = pivot->parent;		// #3
	if (pivot->parent == nullptr)
		m_root = pL;
	else {
		if (pivot->parent->right == pivot)
			pivot->parent->right = pL;
		else
			pivot->parent->left = pL;
	}
	pL->right = pivot;		// #4 将 “y” 设为 “x的右孩子”
	pivot->parent = pL;		// #5,与#4为一对。将 “y的父节点” 设为 “x”
		
	return 0;
}


/*
 * 红黑树插入修正函数
 */ 
int RBTree::insert_case(Node *node) {
	if (node->parent == nullptr) {
		m_root = node;
		m_root->color = NodeColor::BLACK;
		return 0;
	}
	// 只有父节点为红色才需要转换
	if (node->parent->color == NodeColor::RED) {
		if (node->uncle()->color == NodeColor::RED) {
			node->parent->color = node->uncle()->color = NodeColor::BLACK;
			node->grandfather()->color = NodeColor::RED;
			insert_case(node->grandfather());		// 将grandfather设为当前节点，然后继续判断规则。
		}
		else {
			if (node->grandfather()->left == node->parent) {  // 若父节点是左孩子
				if (node->parent->right == node) {
					rotate_left(node->parent);      // 以father节点为支点进行左线
				}
				node->parent->color = NodeColor::BLACK;
				node->grandfather()->color = NodeColor::RED;
				rotate_right(node->grandfather());
			}
			else {		// 父节点是右孩子
				if (node->parent->left == node) {
					rotate_right(node->parent);
				}
				node->parent->color = NodeColor::BLACK;
				node->grandfather()->color = NodeColor::RED;
				rotate_left(node->grandfather());
			}
		}
	}
	return 0;
}

void RBTree::insert(Node* p, element e) {
	if (p->value > e) {				// 插入的值比节点值小，插入的节点的左边
		if (p->left != m_nil)		// root节点初始化left和right都是等于m_nil;
			insert(p->left, e);      // 递归查找插入位置
		else {
			Node* node = new Node();
			node->value = e;
			node->left = node->right = m_nil;
			p->left = node;
			node->parent = p;
			insert_case(node);
		}
	}
	else {		// 插入到右边
		if (p->right != m_nil)
			insert(p->right, e);
		else {
			Node* node = new Node();
			node->value = e;
			node->left = node->right = m_nil;
			node->parent = p;
			p->right = node;
			insert_case(node);
		}
	}
}

// delete===========================================================
/*
① 被删除节点没有儿子，即为叶节点。那么，直接将该节点删除就OK了。
② 被删除节点只有一个儿子。那么，直接删除该节点，并用该节点的唯一子节点顶替它的位置。
③ 被删除节点有两个儿子。那么，先找出它的后继节点；然后把“它的后继节点的内容”复制
给“该节点的内容”；之后，删除“它的后继节点”。在这里，后继节点相当于替身，在将后继
节点的内容复制给"被删除节点"之后，再将后继节点删除。这样就巧妙的将问题转换为"删除后继
节点"的情况了，下面就考虑后继节点。 在"被删除节点"有两个非空子节点的情况下，它的后继节
点不可能是双子非空。既然"的后继节点"不可能双子都非空，就意味着"该节点的后继节点"要么没
有儿子，要么只有一个儿子。若没有儿子，则按"情况① "进行处理；若只有一个儿子，则按"情况② "进行处理。
*/
Node* RBTree::getSmallestChild(Node *p) {
	if (p->left == m_nil)
		return p;
	return getSmallestChild(p->left);
}

bool RBTree::find_delete_node(Node *p, int data) {
	if (p->value > data) {					// 在节点p的左边查找删除节点
		if (p->left == m_nil) {
			return false;
		}
		return find_delete_node(p->left, data);
	}
	else if (p->value < data) {				// 在节点的右边查找删除节点
		if (p->right == m_nil) {
			return false;
		}
		return find_delete_node(p->right, data);
	}
	else if (p->value == data) {			// 找到删除节点
		if (p->right == m_nil) {			// 删除节点没有右孩子；即有左孩子或者没有孩子
			delete_node(p);
			return true;
		}
		// 删除节点有右孩子，这种情况就是上面描述的情况③，则找出删除节点的后继节点。让其回到①或③的情况。
		Node *smallest = getSmallestChild(p->right);	// p存在右孩子，获取p的后继节点
		swap(p->value, smallest->value);                // 交互删除节点p和其后期节点的值
		delete_node(smallest);							// 然后删除后继节点。

		return true;
	}
	else {
		return false;
	}
}

// 经过delete_child函数处理，所有删除操作都变成了①和②。
void RBTree::delete_node(Node *p) {
	Node *child = p->left == m_nil ? p->right : p->left;
	// 空树
	if (p->parent == nullptr && p->left == m_nil && p->right == m_nil) {
		p = nullptr;
		m_root = p;
		return;
	}
	// case1: 删除的是根节点，直接把孩子节点设置成根节点，并为黑色。
	if (p->parent == nullptr) {
		delete  p;
		child->parent = nullptr;
		m_root = child;			// 孩子节点为新的根，直接把新的根节点置成黑色即可。
		m_root->color = NodeColor::BLACK;
		return;
	}
	// 用待删除结点的孩子代替待删除结点
	if (p->parent->left == p) {
		p->parent->left = child;
	}
	else {
		p->parent->right = child;
	}
	child->parent = p->parent;

	// 只有删除节点是黑色节点才需要修正树
	if (p->color == NodeColor::BLACK) {	
		if (child->color == NodeColor::RED) {	// 孩子节点为红色，不需要修改，直接改成黑色即可。
			child->color = NodeColor::BLACK;
		}
		else
			delete_case(child);
	}
	delete p;
}

void RBTree::delete_case(Node *p) {
	if (p->parent == nullptr) {
		p->color = NodeColor::BLACK;
		return;
	}
	// case5: 删除节点的兄弟节点是红色，case5操作之后会回到case2
	if (p->sibling()->color == NodeColor::RED) {
		p->parent->color = NodeColor::RED;          // #1
		p->sibling()->color = NodeColor::BLACK;		// #2和#1，相当于交互父节点和兄弟节点的颜色
		if (p == p->parent->left)					
			rotate_left(p->parent);					// 因为左旋函数接收左旋的当前节点，其支点实际上是p->parent
		else
			rotate_right(p->parent);
	}
	// 兄弟节点是黑色的
	else {
		// case6: 父节点是黑色，兄弟的两个子节点也都是黑色的
		if (p->parent->color == NodeColor::BLACK
			&& p->sibling()->left->color == NodeColor::BLACK && p->sibling()->right->color == NodeColor::BLACK) {
			p->sibling()->color = NodeColor::RED;
			delete_case(p->parent);
		}
		// case2: 父节点是红色，兄弟的两个子节点也都是黑色的
		else if (p->parent->color == NodeColor::RED
			&& p->sibling()->left->color == NodeColor::BLACK && p->sibling()->right->color == NodeColor::BLACK) {
			p->sibling()->color = NodeColor::RED;
			p->parent->color = NodeColor::BLACK;
		}
		else {
			// case4: 删除节点是左节点。兄弟节点的左子节点是红色，右子节点是黑色。之后会回到case3
			if (p == p->parent->left && p->sibling()->left->color == NodeColor::RED
				&& p->sibling()->right->color == NodeColor::BLACK) {
				p->sibling()->color = NodeColor::RED;
				p->sibling()->left->color = NodeColor::BLACK;
				rotate_right(p->sibling());     // 以兄弟节点为支点右旋
			}
			// case7: 删除节点是右节点。兄弟节点的左子节点是黑色，右子节点是红色，之后会回到case3
			else if (p == p->parent->right && p->sibling()->left->color == NodeColor::BLACK
				&& p->sibling()->right->color == NodeColor::RED) {
				p->sibling()->color = NodeColor::RED;
				p->sibling()->right->color = NodeColor::BLACK;
				rotate_left(p->sibling());		// 以兄弟节点为支点左旋
			}
			// case 3: case4和case7执行完成之后都会变成case3。兄弟节点是黑色的，且兄弟节点的右子节点是红色，左子节点任意颜色  
			p->sibling()->color = p->parent->color;
			p->parent->color = NodeColor::BLACK;
			if (p == p->parent->left) {
				p->sibling()->right->color = NodeColor::BLACK;
				rotate_left(p->parent);					// 以父节点为支点左旋
			}
			else {
				p->sibling()->left->color = NodeColor::BLACK;
				rotate_right(p->parent);
			}
		}
	}
}


int main(int argc, char* argv[]) {
	RBTree tree;

	tree.insert(5);
	tree.insert(10); 
	tree.insert(3);
	tree.insert(15);
	tree.insert(8);
	tree.insert(-9);
	tree.insert(30);

	cout << "inorder traversing rbtree:" << endl;
	tree.inorder();
	cout << endl;

	//tree.del_value(15);
	tree.del_value(8);
	cout << "after inorder traversing rbtree:" << endl;
	tree.inorder();
	cout << endl;

	cin.get();
	return 0;
}

/*
1、节点是红色或黑色。
2、根节点是黑色。
3、所有叶子都是黑色（叶子是NIL节点）。
4、每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
5、从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点。
*/

#define BLACK 1
#define RED 0
#include <iostream>

using namespace std;

class bst {
private:

	struct Node {
		int value;
		bool color;
		Node *leftTree, *rightTree, *parent;

		Node() : value(0), color(RED), leftTree(NULL), rightTree(NULL), parent(NULL) { }

		Node* grandparent() {
			if (parent == NULL) {
				return NULL;
			}
			return parent->parent;
		}

		Node* uncle() {
			if (grandparent() == NULL) {
				return NULL;
			}
			if (parent == grandparent()->rightTree)
				return grandparent()->leftTree;
			else
				return grandparent()->rightTree;
		}

		Node* sibling() {
			if (parent->leftTree == this)
				return parent->rightTree;
			else
				return parent->leftTree;
		}
	};

	void rotate_right(Node *p) {
		Node *gp = p->grandparent();
		Node *fa = p->parent;
		Node *y = p->rightTree;

		fa->leftTree = y;

		if (y != NIL)
			y->parent = fa;
		p->rightTree = fa;
		fa->parent = p;

		if (root == fa)
			root = p;
		p->parent = gp;

		if (gp != NULL) {
			if (gp->leftTree == fa)
				gp->leftTree = p;
			else
				gp->rightTree = p;
		}

	}

	/* 
	* 插入节点p为红色，uncle节点为黑色，且当前节点p是右子树，这样才执行左旋。
	*
	* 左旋示意图(对节点x进行左旋)：
	*      px                              px
	*     /                               /
	*    x                               y                
	*   /  \      --(左旋)-->           / \                #
	*  lx   y                          x  ry     
	*     /   \                       /  \
	*    ly   ry                     lx  ly  
	*/
	void rotate_left(Node *p) {
		if (p->parent == NULL) {
			root = p;
			return;
		}
		// p为当前节点，对应图中的y
		Node *gp = p->grandparent();  // 当前节点的grandfather，对应图的px
		Node *fa = p->parent;         // 当前节点的father，对应图的x
		Node *y = p->leftTree;        // 当前节点的left孩子，对应图的ly

		fa->rightTree = y;            // 对应图中x->right = ly：把当前节点的left孩子设为当前节点father节点的right孩子

		if (y != NIL)
			y->parent = fa;           // 对应图中ly->parent = x
		p->leftTree = fa;             // 对应图中y->left = x
		fa->parent = p;               // 对应图中x->parent = y

		if (root == fa)
			root = p;
		p->parent = gp;

		if (gp != NULL) {
			if (gp->leftTree == fa)   // 当前节点的father节点是grandfather节点left孩子，把当前节点p设为grandfather的left孩子
				gp->leftTree = p;
			else
				gp->rightTree = p;
		}
	}

	void inorder(Node *p) {
		if (p == NIL)
			return;

		if (p->leftTree)
			inorder(p->leftTree);

		cout << p->value << " ";

		if (p->rightTree)
			inorder(p->rightTree);
	}

	string outputColor(bool color) {
		return color ? "BLACK" : "RED";
	}

	Node* getSmallestChild(Node *p) {
		if (p->leftTree == NIL)
			return p;
		return getSmallestChild(p->leftTree);
	}

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
	bool delete_child(Node *p, int data) {
		if (p->value > data) {					// 在节点p的左边找删除节点
			if (p->leftTree == NIL) {
				return false;
			}
			return delete_child(p->leftTree, data);
		}
		else if (p->value < data) {				// 在节点的右边找删除节点
			if (p->rightTree == NIL) {
				return false;
			}
			return delete_child(p->rightTree, data);
		}
		else if (p->value == data) {			// 找到删除节点
			if (p->rightTree == NIL) {			// 删除节点没有右孩子
				delete_one_child(p);
				return true;
			}
			// 删除节点有右孩子，则找出删除节点的后继节点。
			Node *smallest = getSmallestChild(p->rightTree);  // p存在右孩子，获取p的后继节点
			swap(p->value, smallest->value);                  // 交互删除节点p和其后期节点的值
			delete_one_child(smallest);                       // 然后删除后继节点。

			return true;
		}
		else {
			return false;
		}
	}

	// 经过delete_child函数处理，所有删除操作都变成了①和②。
	void delete_one_child(Node *p) {
		Node *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
		// 空树
		if (p->parent == NULL && p->leftTree == NIL && p->rightTree == NIL) {
			p = NULL;
			root = p;
			return;
		}
		// 删除的是根节点，直接把孩子节点设置成根节点，并为黑色。
		if (p->parent == NULL) {
			delete  p;
			child->parent = NULL;
			root = child;			// 孩子节点为新的根，直接把新的根节点置成黑色即可。
			root->color = BLACK;
			return;
		}
		// 使用删除节点p的孩子节点替换p
		if (p->parent->leftTree == p) {
			p->parent->leftTree = child;
		}
		else {
			p->parent->rightTree = child;
		}
		child->parent = p->parent;

		if (p->color == BLACK) {		// 只有删除节点是黑色节点才需要修正树
			if (child->color == RED) {  // 孩子节点为红色，不需要修改，直接改成黑色即可。
				child->color = BLACK;
			}
			else
				delete_case(child);
		}
		delete p;
	}

	void delete_case(Node *p) {
		if (p->parent == NULL) {
			p->color = BLACK;
			return;
		}
		// 删除节点的兄弟节点是红色
		if (p->sibling()->color == RED) {
			p->parent->color = RED;
			p->sibling()->color = BLACK;
			if (p == p->parent->leftTree)
				rotate_left(p->sibling());	// 因为左旋函数接收左旋的当前节点，其支点实际上是p->parent
			else
				rotate_right(p->sibling());
		}
		// 兄弟节点是黑色的，兄弟的两个子节点也都是黑色的
		if (p->parent->color == BLACK && p->sibling()->color == BLACK
			&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
			p->sibling()->color = RED;
			delete_case(p->parent);
		}
		else if (p->parent->color == RED && p->sibling()->color == BLACK
			&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
			p->sibling()->color = RED;
			p->parent->color = BLACK;
		}
		else {
			if (p->sibling()->color == BLACK) {
				// 兄弟节点是黑色的，且兄弟节点的左子节点是红色，右子节点是黑色
				if (p == p->parent->leftTree && p->sibling()->leftTree->color == RED
					&& p->sibling()->rightTree->color == BLACK) {
					p->sibling()->color = RED;
					p->sibling()->leftTree->color = BLACK;
					rotate_right(p->sibling()->leftTree);     // rotate_right(p->sibling()),p->sibling()==pivot
				}
				else if (p == p->parent->rightTree && p->sibling()->leftTree->color == BLACK
					&& p->sibling()->rightTree->color == RED) {
					p->sibling()->color = RED;
					p->sibling()->rightTree->color = BLACK;
					rotate_left(p->sibling()->rightTree);
				}
			}

			// 兄弟节点是黑色的，且兄弟节点的右子节点是红色，左子节点任意颜色
			p->sibling()->color = p->parent->color;
			p->parent->color = BLACK;
			if (p == p->parent->leftTree) {
				p->sibling()->rightTree->color = BLACK;
				rotate_left(p->sibling());					// rotate_left(p->parent)
			}
			else {
				p->sibling()->leftTree->color = BLACK;
				rotate_right(p->sibling());
			}
		}
	}

	/*
	 * 描述：递归方法插入元素到树中
	 * p:    红黑树跟节点 
	 * data: 要插入的数据
	*/
	void insert(Node *p, int data) {
		if (p->value >= data) {              // 插到左子树
			if (p->leftTree != NIL)
				insert(p->leftTree, data);   // 递归查找插入位置
			else {                           // 找到插入位置，并开始插入
				Node *tmp = new Node();
				tmp->value = data;
				tmp->leftTree = tmp->rightTree = NIL;
				tmp->parent = p;
				p->leftTree = tmp;
				insert_case(tmp);
			}
		}
		else {                               // 插到右子树
			if (p->rightTree != NIL)
				insert(p->rightTree, data);
			else {
				Node *tmp = new Node();
				tmp->value = data;
				tmp->leftTree = tmp->rightTree = NIL;
				tmp->parent = p;
				p->rightTree = tmp;
				insert_case(tmp);
			}
		}
	}

	// 当插入元素后需要判断插入元素后的树是否需要进行转换操作（变色、左旋、右旋）
	void insert_case(Node *p) {
		if (p->parent == NULL) {     // 正常从insert函数调用insert_case是不会进入这里的，除非出错了。
			root = p;
			p->color = BLACK;
			return;
		}
		// 只有当前节点的父节点为红色时才需要进行转换操作。
		if (p->parent->color == RED) {
			if (p->uncle()->color == RED) {  // father节点和uncle节点都是红色时，把father节点和uncle节点转成黑色，把grandfather节点转成红色

				p->parent->color = p->uncle()->color = BLACK;
				p->grandparent()->color = RED;
				insert_case(p->grandparent());     // 将grandfather设为当前节点，然后继续判断规则。
			}
			else {
				if (p->parent->rightTree == p && p->grandparent()->leftTree == p->parent) {    //parent是grandfather的左孩子，p是father的右孩子
					rotate_left(p);
					rotate_right(p);
					p->color = BLACK;
					p->leftTree->color = p->rightTree->color = RED;
				}
				else if (p->parent->leftTree == p && p->grandparent()->rightTree == p->parent) {  //parent是grandfather的右孩子，p是father的左孩子
					rotate_right(p);
					rotate_left(p);
					p->color = BLACK;
					p->leftTree->color = p->rightTree->color = RED;
				}
				else if (p->parent->leftTree == p && p->grandparent()->leftTree == p->parent) {   //parent是grandfather的左孩子，p是father的左孩子
					p->parent->color = BLACK;
					p->grandparent()->color = RED;
					rotate_right(p->parent);  // 插入的是parent，内部函数实际上是以parent->parent为支点进行旋转。
				}
				else if (p->parent->rightTree == p && p->grandparent()->rightTree == p->parent) {  //parent是grandfather的右孩子，p是father的右孩子
					p->parent->color = BLACK;
					p->grandparent()->color = RED;
					rotate_left(p->parent);
				}
			}
		}
	}

	void DeleteTree(Node *p) {
		if (!p || p == NIL) {
			return;
		}
		DeleteTree(p->leftTree);
		DeleteTree(p->rightTree);
		delete p;
	}
public:

	bst() {
		NIL = new Node();
		NIL->color = BLACK;
		root = NULL;
	}

	~bst() {
		if (root)
			DeleteTree(root);
		delete NIL;
	}

	void inorder() {
		if (root == NULL)
			return;
		inorder(root);
		cout << endl;
	}

	void insert(int x) {
		if (root == NULL) {
			root = new Node();
			root->color = BLACK;
			root->leftTree = root->rightTree = NIL;
			root->value = x;
		}
		else {
			insert(root, x);
		}
	}

	bool delete_value(int data) {
		return delete_child(root, data);
	}

private:
	Node *root, *NIL;
};

int main2()
{
	cout << "---【红黑树】---" << endl;
	// 创建红黑树
	bst tree;

	// 插入元素
	/*tree.insert(2);
	tree.insert(9);
	tree.insert(-10);
	tree.insert(0);
	tree.insert(33);
	tree.insert(-19);
	*/
	tree.insert(5);
	tree.insert(10);
	tree.insert(3);
	tree.insert(15);
	tree.insert(8);
	tree.insert(-9);
	tree.insert(30);

	// 顺序打印红黑树
	cout << "插入元素后的红黑树：" << endl;
	tree.inorder();

	// 删除元素
	tree.delete_value(8);

	// 顺序打印红黑树
	cout << "删除元素 2 后的红黑树：" << endl;
	tree.inorder();

	// 析构
	tree.~bst();

	getchar();
	return 0;
}
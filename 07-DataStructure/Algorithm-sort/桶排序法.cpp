/*****************
桶排序：将值为i的元素放入i号桶，最后依次把桶里的元素倒出来。
桶排序序思路：
1. 设置一个定量的数组当作空桶子。
2. 寻访序列，并且把项目一个一个放到对应的桶子去。
3. 对每个不是空的桶子进行排序。
4. 从不是空的桶子里把项目再放回原来的序列中。
假设数据分布在[0，100)之间，每个桶内部用链表表示，在数据入桶的同时插入排序，然后把各个桶中的数据合并。
例如一个数据分布在[0, 100]之间，长度是50的数组进行排序，bucket=10，按照arr[i]/bucket把数据插入到对应的桶中，
这样[0, 10]的数据就会插入到bucket[0]桶中，以此类推数据以小到大的顺序插入到对应的桶。然后把这10个桶连起来，桶
中链表的数据便是有序的，再逐个拷贝到原来的数组中，最终得到有序数组。

数组元素映射到桶的公式，一般是：
	f = array[i] / k; k^2 = n; n是所有元素个数
	如：100个元素，那么通过k^2 = n可以计算出桶的个数是10个。
	该算法计算桶数有可能会导致数据插入越界，如100个元素的数据对应的桶个数是10个（0--9），然这个数组里有一些元素是大于100的，
	导致会去第10个桶插入数据，而根本不存在第10个桶。因此最好使用一下公式：
	k = max/10 - min/10 + 1;   max:数组中的最大值；min：数组中最小值。

时间复杂度：
	平均时间复杂度：	O(n+k)  (n:元素个数，k：桶的个数)
	最差时间复杂度：	O(n+k)
	空间复杂度：		O(n*k)
	数据对象稳定性：	稳定
*****************/
#include<iterator>
#include<iostream>
#include<vector>

using namespace std;

const int BUCKET_NUM = 10;

struct ListNode {
	explicit ListNode(int i = 0) :mData(i), mNext(NULL) {}
	ListNode* mNext;
	int mData;
};

// 相当于在数组里实现单链表的插入。
ListNode* insert(ListNode* head, int val) {
	ListNode dummyNode;
	ListNode *newNode = new ListNode(val);  // 给插入元素分配空间
	ListNode *pre, *curr;
	dummyNode.mNext = head;   // 记录当前指针
	pre = &dummyNode;         // pre指针初始化为当前桶的头结点。
	curr = head;              // curr指针初始化为当前桶的头结点。
	// 桶的元素是从小到头排序，定位适合参数val插入的位置上。
	while (NULL != curr && curr->mData <= val) {  // 查找元素插入位置（确保有序）
		pre = curr;
		curr = curr->mNext;  // 右移指针
	}
	// 以下两句是链表中插入节点。
	newNode->mNext = curr;
	pre->mNext = newNode;
	// 返回开始保存的桶头部指针
	return dummyNode.mNext;
}

// merge的过程实际上就是把新数组中的所有桶按数据大小进行桶排序
ListNode* Merge(ListNode *head1, ListNode *head2) {
	ListNode dummyNode;
	// dummy指针用于辅助桶排序和连接时游标移动，dummyNode用于保存连接后桶的链表的首地址。
	// 首次循环把head1/head2赋给了dummyNode.mNext之后，dummy开始移动自己的指针，dummyNode没有变，因此其mNext一直保存着head1/head2；
	ListNode *dummy = &dummyNode;  
	// 开始两个桶的数据进行排序和连接。根据算法i-1号桶里的所有数据都会比i号桶的数据要小
	// 因此以下情况会先完成head1的排序，再开始head2的排序head1赋给了
	while (NULL != head1 && NULL != head2) {
		if (head1->mData <= head2->mData) {  // 目前算法head1中的mData都会比head2的mData小
			dummy->mNext = head1;            // dummy->next保存head1节点；
			head1 = head1->mNext;            // head1节点后移，循环直到head1的尾部
		}
		else {  // 目前算法不会进入else区域
			dummy->mNext = head2;
			head2 = head2->mNext;
		}
		dummy = dummy->mNext;                // dummy保存head[1/2]头部节点。      
	}
	// 把head1和head2连接起来。
	if (NULL != head1) dummy->mNext = head1;
	if (NULL != head2) dummy->mNext = head2;

	return dummyNode.mNext;   // 返回连接后第一个节点地址；即输入桶中小数值桶的首地址（demo是head1）
}

void BucketSort(int n, int arr[]) {
	vector<ListNode*> buckets(BUCKET_NUM, (ListNode*)(0));
	// 每个数组的元素插入到对应的桶中，桶中的数据以链表形式连接，而且是有序的。
	for (int i = 0; i<n; ++i) {
		int index = arr[i] / BUCKET_NUM;          // 得到的index必须在桶数组范围内，否则会越界。因此原数组数值分布于桶个数有关。
		ListNode *head = buckets.at(index);       // 指向桶的头部
		buckets.at(index) = insert(head, arr[i]); // 在桶中插入元素，同时返回该桶的头部指针。
	}
	// 桶排序
	ListNode *head = buckets.at(0);
	for (int i = 1; i<BUCKET_NUM; ++i) {
		head = Merge(head, buckets.at(i));
	}
	// 把已排序的桶数据重新拷贝到原数组中，完成排序。
	for (int i = 0; i<n; ++i) {
		arr[i] = head->mData;
		head = head->mNext;
	}
}

int main(int argc, char* argv[]) {
	int arr[] = { 9,23,8,11, 13, 24, 2, 15};
	int len = sizeof(arr) / sizeof(arr[0]);
	BucketSort(len, arr);
	for (int i = 0; i < len; i++)
		cout <<" " << arr[i];
	cout << endl;

	getchar();
	return 0;
}
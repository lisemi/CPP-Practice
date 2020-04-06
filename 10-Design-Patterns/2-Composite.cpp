#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

// 目录和文件都使用相同的接口。
class IFile {
public:
	virtual void display() = 0;
	virtual int add(IFile* ifile) = 0;
	virtual int remove(IFile* ifile) = 0;
	virtual list<IFile*>* getChild() = 0;
};

// 文件对象
class File : public IFile{
public:
	File(string name) {
		m_name = name;
	}
	virtual void display() {
		cout << m_name << endl;
	}
	virtual int add(IFile* ifile) {
		return -1;
	}
	virtual int remove(IFile* ifile) {
		return -1;
	}
	virtual list<IFile*>* getChild() {
		return NULL;
	}
private:
	string m_name;
	list<IFile*> m_list;
};

// 目录对象
class Dir : public IFile{
public:
	Dir(string name) {
		m_name = name;
		m_list = new list<IFile*>;
		m_list->clear();
	}
	virtual void display() {
		cout << m_name << endl;
	}
	virtual int add(IFile* ifile) {
		m_list->push_back(ifile);
		return 0;
	}
	virtual int remove(IFile* ifile) {
		m_list->remove(ifile);
		return 0;
	}
	virtual list<IFile*>* getChild() {
		return m_list;
	}
private:
	string m_name;
	list<IFile*>* m_list;
};

struct play{
	void operator()(IFile* it) {
		it->display();
	}
};

// 分层递归显示所有目录和文件
void show(IFile* root, int level) {
	if (NULL == root)	return;
	list<IFile*>* flist = NULL;
	for (int i = 0; i < level; i++) {
		printf("\t");
	}
	root->display();
	flist = root->getChild();
	if (flist != NULL) {
		for (list<IFile*>::iterator it = flist->begin(); it != flist->end(); it++) {
			if ((*it)->getChild() == NULL) {
				for (int i = 0; i < level; i++) {
					printf("\t");
				}
				(*it)->display();
			}
			else {
				show((*it), level + 1);
			}
		}
	}
}

int main(int argc, char* argv[]) {
	Dir* root = new Dir("C");
	Dir* dir1 = new Dir("aaa");
	File* file123 = new File("111.txt");
	root->add(dir1);		// C盘下增加目录abc
	root->add(file123);		// C盘下增加文件123.txt

	Dir* dir2 = new Dir("bbb");
	File* file222 = new File("222.txt");
	dir1->add(dir2);
	dir1->add(file222);

	// 显示单层文件和目录
	//root->display();
	//list<IFile*>* mylist = dir1->getChild();
	//for_each(mylist->begin(), mylist->end(), play());
	// 显示所有目录和文件
	show(root, 0);

	cin.get();
	return 0;
}
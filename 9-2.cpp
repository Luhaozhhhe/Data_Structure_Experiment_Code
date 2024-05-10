#include<iostream>
#include"BinaryTree.h"
#include"myExceptions.h"
using namespace std;
#define BLACK 1
#define RED 0
template<class T>
class redBlackTree :public BinaryTree<T> {
public:
	BinaryTreeNode<T>* LL(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* RR(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* LR(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* RL(BinaryTreeNode<T>* t);
	void Change(BinaryTreeNode<T>* t);
	bool Search(const T& t)const;
	redBlackTree<T>& Insert(const T& t);
	redBlackTree<T>& Delete(const T& t);
	void Delete(const T& t, bool yes);
	void Ascend() { redBlackTree<T>::InOrderOutput(); }
};

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::LL(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->LeftChild;
	if (!t->father)
	{
		temp->father = NULL;
	}
	else
	{
		if (t == t->father->LeftChild)
		{
			t->father->LeftChild = temp;
			temp->father = t->father;
		}
		else
		{
			t->father->RightChild = temp;
			temp->father = t->father;
		}
	}
	t->LeftChild = temp->RightChild;
	temp->RightChild->father = t;
	temp->RightChild = t;
	t->father = temp;
	t->color = RED;
	temp->color = BLACK;
	return temp;
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::RR(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->RightChild;
	if (!t->father)
	{
		temp->father = NULL;
	}
	else
	{
		if (t == t->father->RightChild)
		{
			t->father->RightChild = temp;
			temp->father = t->father;
		}
		else
		{
			t->father->LeftChild = temp;
			temp->father = t->father;
		}
	}
	t->RightChild = temp->LeftChild;
	temp->LeftChild->father = t;
	temp->LeftChild = t;
	t->father = temp;
	t->color = RED;
	temp->color = BLACK;
	return temp;
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::LR(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->LeftChild;
	t->LeftChild = RR(temp);
	return LL(t);
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::RL(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->RightChild;
	t->RightChild = LL(temp);
	return RR(t);
}

template<class T>
void redBlackTree<T>::Change(BinaryTreeNode<T>* t)
{
	if (!t->father || !t->father->father)
		return;
	BinaryTreeNode<T>* p = t->father->father;
	if (!p->LeftChild || !p->RightChild || p->LeftChild->color == 1 || p->RightChild->color == 1)
	{
		if (p->LeftChild && p->LeftChild->color == 0)
		{
			if (t->father == p->LeftChild)
				p = LL(p);
			else
				p = LR(p);
		}
		if (p->RightChild && p->RightChild->color == 0)
		{
			if (t->father == p->LeftChild)
				p = RL(p);
			else
				p = RR(p);
		}
	}
	if (p->LeftChild && p->RightChild)
	{
		if (p->LeftChild->color == 0 && p->RightChild->color == 0)
		{
			p->LeftChild->color = 1;
			p->RightChild->color = 1;
			if (!p->father)
				p->color = 1;
			else
			{
				p->color = 0;
				Change(p);
			}
		}
	}

}

template<class T>
bool redBlackTree<T>::Search(const T& t)const
{

	//首先使p指向跟节点
	BinaryTreeNode<T>* p = redBlackTree<T>::root;
	while (p)
	{
		//两层if-else，三选一，k小于根节点时指向左子树，k大于根节点时指向右子树，等于根节点时返回true
		if (t < p->data)
			p = p->LeftChild;
		else
		{
			if (t > p->data)
				p = p->RightChild;
			else
				return true;
		}
	}
	//没有找到关键值为k的元素，此时p为空，直接返回false
	return false;
}



template<class T>
redBlackTree<T>& redBlackTree<T>::Insert(const T& t)
{
	//p指向根节点，pp指向根节点的根节点（非初始时）
	BinaryTreeNode<T>* p = redBlackTree<T>::root, * pp = 0;
	while (p)
	{
		//pp指向上一个while循环结束的p节点的位置
		pp = p;
		//两层if-else，三选一，k小于根节点时指向左子树，
		//k大于根节点时指向右子树，等于根节点时说明已经含有e这个元素，无法插入
		if (t <= p->data)
			p = p->LeftChild;
		else
			p = p->RightChild;
	}
	//现在已经找到了合适的插入位置
	BinaryTreeNode<T>* r = new BinaryTreeNode<T>(t);
	//当根节点存在时，判断插入其左子树还是插入其右子树
	if (redBlackTree<T>::root)
	{
		if (t <= pp->data)
		{

			pp->LeftChild = r;
			r->father = pp;

		}
		else
		{
			pp->RightChild = r;
			r->father = pp;
		}
		Change(r);
	}
	//根节点不存在是e就是根节点
	else
		redBlackTree<T>::root = r;
	return *this;
}

//删除函数，删除关键值为t的元素
template<class T>
redBlackTree<T>& redBlackTree<T>::Delete(const T& t)
{
	//p指向根节点，pp指向根节点的根节点（非初始时）
	BinaryTreeNode<T>* p = redBlackTree<T>::root, * pp = 0;
	while (p && p->data != t)
	{
		pp = p;
		if (t < p->data)
			p = p->LeftChild;
		else
			p = p->RightChild;
	}
	//当p不存在的时候说明关键值为k的元素不存在，抛出异常即可
	if (!p)
		throw BadInput();
	//要删除节点的左右节点都存在的情况下
	if (p->LeftChild && p->RightChild)
	{
		//使s指向p的左孩子，ps指向p
		BinaryTreeNode<T>* s = p->LeftChild, * ps = p;
		//找到左孩子这一条线上最后一个右孩子用s来表示，ps表示s的父节点
		while (s->RightChild)
		{
			ps = s;
			s = s->RightChild;
		}
		//s为最大前驱，ps为其父节点
		//s的数据来替代要删除的节点，至此，左右子树都存在的情况下大体完成
		p->data = s->data;

		//如果s有左节点，还要将s删除后左节点移上来，移动p和pp位置为下面的代码铺垫
		//p为左孩子这一条线上最后一个右孩子s
		p = s;
		//pp为s的父节点
		pp = ps;
	}
	//当p有左子树时(进入了上一个if循环)，或p有左子树或右子树的一棵时（没进入上个if循环）
	if (!p->LeftChild && !p->RightChild)
	{
		delete p;
		return *this;
	}
	BinaryTreeNode<T>* c;
	if (p->LeftChild)
	{
		p->LeftChild->color = BLACK;
		c = p->LeftChild;
	}
	else
	{
		p->RightChild->color = BLACK;
		c = p->RightChild;
	}
	//如果p是根节点直接把c赋值给根节点
	if (p == redBlackTree<T>::root)
		redBlackTree<T>::root = c;
	//p不是根节点的话回找pp与p的关系，从而建立pp和c的关系
	else
	{
		if (p == pp->LeftChild)
		{
			pp->LeftChild = c;
			c->father = pp;
		}
		else
		{
			pp->RightChild = c;
			c->father = pp;
		}
		if (c->color == 0 && pp->color == 0)
			Change(c);
	}
	delete p;
	return *this;
}

template<class T>
void redBlackTree<T>::Delete(const T& t, bool yes)
{
	while (Search(t))
	{
		Delete(t);
	}
}

int main()
{
	redBlackTree<int> A;
	int tmp;
	cout << "-----insert datas-----" << endl << endl;
	for (int i = 19; i > 0; i--)
	{
		tmp = i + 1;
		cout << tmp << " ";
		A.Insert(tmp);
	}
	tmp = 15;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 15;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 5;
	cout << tmp << " ";
	A.Insert(tmp);
	cout << endl << "-----input-----" << endl << endl;
	A.Ascend();
	cout << endl << "-----delete 3,8,12-----" << endl << endl;
	A.Delete(3);
	A.Delete(8);
	A.Delete(15);
	A.Ascend();
	return 0;
}
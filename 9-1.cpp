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
	void DChange(BinaryTreeNode<T>* t);
	bool Search(const T& t)const;
	redBlackTree<T>& Insert(const T& t);
	redBlackTree<T>& Delete(const T& t);
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

	if (temp->RightChild)
	{
		t->LeftChild = temp->RightChild;
		temp->RightChild->father = t;
	}
	else
	{
		t->LeftChild = NULL;
	}

	temp->RightChild = t;
	t->father = temp;

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

	if (temp->LeftChild)
	{
		t->RightChild = temp->LeftChild;
		temp->LeftChild->father = t;
	}
	else
	{
		t->RightChild = NULL;
	}

	temp->LeftChild = t;
	t->father = temp;

	return temp;
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::LR(BinaryTreeNode<T>* t)
{
	t->LeftChild = RR(t->LeftChild);
	return LL(t);
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::RL(BinaryTreeNode<T>* t)
{
	t->RightChild = LL(t->RightChild);
	return RR(t);
}

template<class T>
void redBlackTree<T>::DChange(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* f = t->father;
	BinaryTreeNode<T>* s;
	if (t == f->LeftChild)
		s = f->RightChild;
	else
		s = f->LeftChild;
	//情形 2 t的兄弟为红
	if (s && s->color == RED)
	{
		s->color = BLACK;
		f->color = RED;
		if (t == f->LeftChild)
			f = RR(f);
		else
			f = LL(f);
		DChange(t);
	}
	else //s->color==BLACK
	{
		//情形 3 父亲黑、兄弟黑、兄弟的两个孩子黑
		if (f->color == BLACK && s->LeftChild->color == BLACK && s->RightChild->color == BLACK)
		{
			s->color = RED;
			DChange(t->father);
		}
		//情形 4 父亲红、兄弟黑、兄弟的两个孩子黑
		if (s && f->color == RED && s->LeftChild->color == BLACK && s->RightChild->color == BLACK)
		{
			f->color = BLACK;
			s->color = RED;
		}
		//情形 5 t是左孩子，兄弟左孩子红，右孩子黑  以及t是右孩子，兄弟右孩子红左孩子黑
		if (s && t == t->father->LeftChild && s->LeftChild->color == RED && s->RightChild->color == BLACK)
		{
			s->color = RED;
			s->LeftChild->color = BLACK;
			s = LL(s);
		}
		if (s && t == t->father->RightChild && s->RightChild->color == RED && s->LeftChild->color == BLACK)
		{
			s->color = RED;
			s->RightChild->color = BLACK;
			s = RR(s);
		}
		//情形 6 t是左孩子，兄弟右孩子红  以及t是左孩子，兄弟右孩子红
		if (s && t == t->father->LeftChild && s->RightChild->color == RED)
		{
			s->RightChild->color = BLACK;
			int temp = s->color;
			s->color = f->color;
			f->color = temp;
			f = RR(f);
		}
		/*if (t == t->father->RightChild && s->LeftChild->color == RED)
		{
			s->LeftChild->color = BLACK;
			int temp = s->color;
			s->color = f->color;
			f->color = temp;
			f = LL(f);
		}
		*/
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
			{
				//t = p->data;
				return true;
			}
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
	if (redBlackTree<T>::Search(t))
	{
		return *this;
	}
	else {
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
			DChange(r);
		}
		//根节点不存在是e就是根节点
		else
			redBlackTree<T>::root = r;
		return *this;
	}
}

//删除函数，删除关键值为k的元素并且将其返回到e中
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
	if (p && p->LeftChild && p->RightChild)
	{
		//使s指向p的左孩子，ps指向p
		BinaryTreeNode<T>* s = p->LeftChild, * ps = p;
		//找到左孩子这一条线上最后一个右孩子用s来表示，ps表示s的父节点
		while (s->RightChild)
		{
			ps = s;
			s = s->RightChild;
		}
		//s的数据来替代要删除的节点，至此，左右子树都存在的情况下大体完成
		p->data = s->data;

		//如果s有左节点，还要将s删除后左节点移上来，移动p和pp位置为下面的代码铺垫
		//p为左孩子这一条线上最后一个右孩子s
		p = s;
		//pp为s的父节点
		pp = ps;
	}

	//要删除的节点没有子节点
	if (!p->LeftChild && !p->RightChild)
	{
		if (p == redBlackTree<T>::root)
		{
			delete p;
			return *this;
		}
		else
		{
			if (p == pp->LeftChild)
			{
				pp->LeftChild = NULL;
			}
			else
			{
				pp->RightChild = NULL;
			}
			DChange(pp);
		}
		delete p;
		return *this;
	}

	BinaryTreeNode<T>* c;
	//p有左子树或右子树的一棵时
	if (p->LeftChild)
		c = p->LeftChild;
	else
		c = p->RightChild;
	//如果p是根节点直接把c赋值给根节点
	if (p == redBlackTree<T>::root)
	{
		c->color = BLACK;
		redBlackTree<T>::root = c;
	}
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
		if (p->color == 1 && c->color == 0)
			c->color = BLACK;
		else
		{
			if (p->color == 1 && c->color == 1)
				DChange(c);
		}
	}
	delete p;
	return *this;
}

int main()
{
	redBlackTree<int> A;
	int tmp;
	cout << "-----insert datas-----" << endl << endl;
	for (int i = 20; i > 1; i--)
	{
		tmp = i + 1;
		cout << tmp << " ";
		A.Insert(tmp);
	}
	tmp = 7;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 9;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 13;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 7;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 7;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 5;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 9;
	cout << tmp << " ";
	A.Insert(tmp);
	cout << endl << "-----output-----" << endl << endl;
	A.Ascend();
	cout << endl << "-----delete 3,8,12-----" << endl << endl;
	A.Delete(3);
	A.Delete(8);
	A.Delete(12);
	A.Ascend();
	return 0;
}
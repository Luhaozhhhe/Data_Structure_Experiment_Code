#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstddef>
using namespace std;
template<class K>
class SortedChainNode {
public:
	K data;
	SortedChainNode<K>* link;
};

template<class K>
class SortedChain {
public:
	SortedChain()
	{
		first = new SortedChainNode<K>;
	}
	bool Search(const K& k)const;//查找链表中是否有相应元素
	SortedChain<K>& Delete(const K& k);//删除节点
	SortedChain<K>& DistinctInsert(const K& k);//插入节点
public:
	SortedChainNode<K>* first;
};


template<class K>//查找链表中是否有相应元素
bool SortedChain<K>::Search(const K& k)const
{
	SortedChainNode<K>* p = first;
	while (p->data < k)
	{
		p = p->link;
	}
	//判断是否匹配
	if (p->data == k)
	{
		return true;
	}
	//链表已经为空或者当前数据大于k
	return false;
}

template<class K>//删除节点
SortedChain<K>& SortedChain<K>::Delete(const K& k)
{
	//p用于移动，tp用于记录p的前一个位置
	SortedChainNode<K>* p = first, * tp = first;
	while (p->data < k)
	{
		tp = p;
		p = p->link;
	}
	//找到了要删除的节点
	if (p->data == k)
	{
		tp->link = p->link;
		delete p;
		return *this;
	}
	//没有可删的节点
	/*throw BadInput();*/
	return *this;
}

template<class K>//插入节点
SortedChain<K>& SortedChain<K>::DistinctInsert(const K& k)
{
	SortedChainNode<K>* p = first, * tp = first;
	while (p->data < k)
	{
		tp = p;
		p = p->link;
	}
	//不允许重复关键字的插入
	if (p->data == k)
	{
		//cout << k << "重复插入" << " ";
		return *this;
	}
	SortedChainNode<K>* q = new SortedChainNode<K>;
	q->data = k;
	q->link = p;
	tp->link = q;
	return *this;
}

//所谓链表法只是先在链表数组中找到对应的那一条链表，然后用字典的函数来处理而已
template<class K>
class ChainHashTable {
public:
	ChainHashTable(int divisor = 11)
	{
		m = divisor;
		tail = new SortedChainNode<K>;
		tail->data = 1001;
		tail->link = NULL;
		ht = new SortedChain<K>[m];//创建m个链表用来存放数据
		for (int i = 0; i < m; i++)
		{
			ht[i].first->link = tail;
		}
	}
	bool Search(const K& k)const//按照标签查找
	{
		return ht[k % m].Search(k);
	}
	ChainHashTable<K>& Insert(const K& k)//插入元素
	{
		ht[k % m].DistinctInsert(k);
		return *this;
	}
	ChainHashTable<K>& Delete(const K& k)//删除元素
	{
		ht[k % m].Delete(k);
		return *this;
	}
	void Output()const;
public:
	int m;//m是除数
	SortedChain<K>* ht;//ht是链表数组
	SortedChainNode<K>* tail;
};

template<class K>
void ChainHashTable<K>::Output()const
{
	for (int i = 0; i < m; i++)
	{
		SortedChainNode<K>* p = ht[i].first->link;
		if (p->data < tail->data)
		{
			cout << "( " << i << " ) ";
			while (p->data < tail->data)
			{
				cout << p->data << " ";
				p = p->link;
			}
			cout << endl;
		}
	}
}

int main()
{
	clock_t t1, t2;
	ChainHashTable<int>zqzy(30);
	for (int i = 0; i < 100; i++)
		zqzy.Insert(rand() % 100);
	cout << endl;
	zqzy.Output();
}
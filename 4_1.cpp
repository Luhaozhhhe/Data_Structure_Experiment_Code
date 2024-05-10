#include<iostream>
using namespace std;

//公式化
template<class T>
class Josephus {
public:
	int n;
	int m;
	T* array;
	Josephus(int x, int y)//构造函数，给n、m、初始数组赋值
	{
		n = x;
		m = y;
		array = new T[n + 1];
		for (int i = 1; i <= n; i++)
			array[i] = i;
	}
	T Delete(int x)//将数组中序号为x的元素返回并将x后面的所有元素向前移
	{
		T y = array[x];
		for (int i = x; i < n; i++)
			array[i] = array[i + 1];
		return y;

	}
	void Output()//输出
	{
		int num;//本次循环需要删除掉的元素序号
		int temp = 0;//中间量，记录上一次删除元素前面的元素个数
		for (int i = 0; i < n - 1; i++)
		{
			if (!((m + temp) % (n - i)))
			{
				num = n - i;
			}
			else
			{
				num = (m + temp) % (n - i);
			}
			//temp积累本次删除的元素前面的元素个数，留待下次循环使用
			temp = num - 1;
			cout << Delete(num) << " ";
		}
		//删除掉前n-1个元素后只剩最后一个元素，直接输出即可
		cout << array[1] << endl;
	}
};


//链表
template<class T>
class ChainNode {
public:
	T data;
	ChainNode<T>* link;
};

template<class T>
class Chain {

public:
	Chain() { first = 0; last = 0; }
	Chain<T>& Delete(int k, T& x);//删除元素
	Chain<T>& Insert(int k, const T& x);//插入元素
	Chain<T>& Sort(int n, int m);//筛选
	Chain<T>& Append(const T& x);//拓展
	void output(ostream& out)const;

public:
	ChainNode<T>* first, * last;//头指针与尾指针
};

template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{
	ChainNode<T>* current = first;
	if (k == 1)
		first = first->link;//如果是第一个删除位置就直接往后指一下
	else
	{
		ChainNode<T>* q = first;
		for (int index = 1; index < k - 1 && q; index++)
		{
			q = q->link;//先往后k-1个，让q的link指针指向需要删除的位置
		}
		current = q->link;//将q的link指针给current，获取到了需要删除的位置
		q->link = current->link;
	}
	x = current->data;
	delete current;
	return *this;
}

template<class T>//插入
Chain<T>& Chain<T>::Insert(int k, const T& x)
{
	ChainNode<T>* q = first;
	for (int i = 1; i < k && q; i++)
	{
		q = q->link;
	}
	ChainNode<T>* p = new ChainNode<T>;
	p->data = x;
	if (k)
	{
		p->link = q->link;
		q->link = p;
	}
	else
	{
		p->link = first;
		first = p;
	}
	return *this;
}

template<class T>//拓展
Chain<T>& Chain<T>::Append(const T& x)
{
	ChainNode<T>* y = new ChainNode<T>;
	y->data = x;
	y->link = 0;
	if (first)
	{
		last->link = y;
		last = y;
	}
	else
		first = last = y;
	return *this;
}

template<class T>//筛选
Chain<T>& Chain<T>::Sort(int n, int m)
{
	int num;
	int temp = 0;
	for (int i = 0; i < n - 1; i++)
	{
		if (!((m + temp) % (n - i)))
		{
			num = n - i;
		}
		else
		{
			num = (m + temp) % (n - i);
		}
		temp = num - 1;
		T x;
		Delete(num + i, x);
		Insert(i, x);
	}
	return *this;
}

template<class T>
void Chain<T>::output(ostream& out)const
{
	ChainNode<T>* current;
	for (current = first; current; current = current->link)
	{
		out << current->data;
		if (current->link)
			cout << " ";
	}
}

template<class T>
ostream& operator<<(ostream& out, const Chain<T>& x)
{
	x.output(out);
	return out;
}

int main()
{
	
	int n, m;
	cin >> n >> m;
	Josephus<int>array1(n, m);
	array1.Output();//第一种输出方式——公式化

	Chain<int>array2;
	for (int i = 1; i <= n; i++)
	{
		array2.Append(i);//输出有序的数
	}
	array2.Sort(n, m);
	cout << array2 << endl;//第二种输出方式——链表
	return 0;
}
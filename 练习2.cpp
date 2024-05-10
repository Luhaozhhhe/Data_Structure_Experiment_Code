#include<iostream>
using namespace std;

//编辑双向节点
template<class T>
class DoubleNode {
public:
	T data;
	DoubleNode<T>* left;
	DoubleNode<T>* right;
};
//编写Double类
template<class T>
class Double {

public:
	Double();
	void Erase();
	bool Isempty()const;
	int Len()const;
	bool Find(int k, T& x)const;
	int Search(const T& x)const;
	void output(ostream& out)const;
	void Getall(int num);
	Double<T>& Delete(int k, T& x);
	Double<T>& Insert(int k, const T& x);
	Double<T>& Append(const T& x);

public:
	DoubleNode<T>* LeftEnd;
};
//编写Double函数，给leftend赋一个初始值0，表明leftend只有一个，left和right都指向lefthand
template<class T>
Double<T>::Double()
{
	LeftEnd = new DoubleNode<T>;
	LeftEnd->data = 0;
	LeftEnd->right = LeftEnd;
	LeftEnd->left = LeftEnd;
}
//写一个擦除函数
template<class T>
void Double<T>::Erase()
{
	DoubleNode<T>* current = LeftEnd->right;//申明一个current指针，让最右端指向它
	while (current != LeftEnd)
	{
		current = LeftEnd->right;
		delete LeftEnd;
		LeftEnd = current;
	}
	cout << "the space is erased!" << endl;
}

template<class T>
bool Double<T>::Isempty()const
{
	if (LeftEnd->right == LeftEnd)//如果相等说明无内容
		return true;
	else
		return false;
}

template<class T>
int Double<T>::Len()const//计算长度，使用一个临时指针指向最右边，然后从左边开始遍历，计算出长度即可。
{
	DoubleNode<T>* current = LeftEnd->right;
	int len = 0;
	while (current != LeftEnd)
	{
		len++;
		current = current->right;
	}
	return len;
}
//课上写过的find函数，如果k的值不符合长度要求就跳出；如果符合，就计算一下从左边开始的数量，找出第k个即可，看看是否相等。
template<class T>
bool Double<T>::Find(int k, T& x)const
{
	if (k < 1 || k>Len())
		return false;
	DoubleNode<T>* current = LeftEnd->right;
	int index = 1;
	while (index < k)
	{
		current = current->right;
		index++;
	}
	x = current->data;
	return true;
}
//查找函数，index表示查找成功之后的所在位置。
template<class T>
int Double<T>::Search(const T& x)const
{
	DoubleNode<T>* current = LeftEnd->right;
	int index = 1;
	LeftEnd->data = x;
	while (current->data != x)
	{
		current = current->right;
		index++;
	}
	return ((current == LeftEnd) ? 0 : index);
}
//输出函数，输出链表中的各项数据。
template<class T>
void Double<T>::output(ostream& out)const
{
	DoubleNode<T>* current;
	for (current = LeftEnd->right; current != LeftEnd; current = current->right)
	{
		out << current->data << " ";
	}
}
//重载<<符号，使其能够连续输出。
template<class T>
ostream& operator<<(ostream& out, const Double<T>& x)
{
	x.output(out);
	return out;
}

template<class T>
void Double<T>::Getall(int num)
{
	if (num < 1)
	{
		cout << "wrong!at least one " << endl;
		return;
	}
	cout << "input" << num << "number：" << endl;
	DoubleNode<T>* current = LeftEnd;
	for (int i = 0; i < num; i++)
	{
		current->right = new DoubleNode<T>;
		cin >> current->right->data;
		current->right->left = current;
		current = current->right;
		current->right = LeftEnd;
		LeftEnd->left = current;
	}
}

template<class T>
Double<T>& Double<T>::Delete(int k, T& x)
{
	if (k < 1 || k>Len())
	{
		cout << "wrong!" << endl;
		return *this;
	}
	DoubleNode<T>* current = LeftEnd->right;
	if (k == 1)
	{
		LeftEnd->right = current->right;
		current->right->left = LeftEnd;
	}
	else
	{
		DoubleNode<T>* q = LeftEnd->right;
		for (int index = 1; index < k - 1; index++)
		{
			q = q->right;
		}
		current = q->right;
		q->right = current->right;
		current->right->left = q;
	}
	x = current->data;
	delete current;
	return *this;
}

template<class T>
Double<T>& Double<T>::Insert(int k, const T& x)
{
	if (k < 0 || k>Len() + 1)
	{
		cout << "wrong!" << endl;
		return *this;
	}
	DoubleNode<T>* q = LeftEnd;
	for (int i = 0; i < k; i++)
	{
		q = q->right;
	}
	DoubleNode<T>* p = new DoubleNode<T>;
	p->data = x;
	p->right = q->right;
	q->right->left = p;
	q->right = p;
	p->left = q;
	return *this;
}

template<class T>
Double<T>& Double<T>::Append(const T& x)
{
	DoubleNode<T>* y = new DoubleNode<T>;
	y->data = x;
	y->left = LeftEnd->left;
	LeftEnd->left->right = y;
	y->right = LeftEnd;
	LeftEnd->left = y;
	return *this;
}

template<class T>
void split(Double<T>a, Double<T>b)
{
	Double<T>c;
	cout << "please input the number:" << endl;
	int num;
L:cin >> num;
	if (num < 1)
	{
		cout << "wrong!input it again!" << endl;
		goto L;
	}
	c.Getall(num);
	DoubleNode<T>* current = c.LeftEnd->right;
	while (current != c.LeftEnd)
	{
		a.Append(current->data);
		current = current->right;
		if (current == c.LeftEnd)
			break;
		b.Append(current->data);
		current = current->right;
	}
}






int main() {

	cout << "choose one" << endl;
	cout << "A.int   B.float   C.char" << endl;
	char m;
L:cin >> m;
	if (m == 'A')
	{
		Double<int>a, b;
		split(a, b);
		cout << "a:" << endl << a << endl;
		cout << "b:" << endl << b << endl;
	}
	if (m == 'B')
	{
		Double<float>a, b;
		split(a, b);
		cout << "a:" << endl << a << endl;
		cout << "b:" << endl << b << endl;
	}
	if (m == 'C')
	{
		Double<char>a, b;
		split(a, b);
		cout << "a:" << endl << a << endl;
		cout << "b:" << endl << b << endl;
	}
	if (m != 'A' && m != 'B' && m != 'C')
	{
		cout << "wrong!" << endl;
		goto L;
	}



	return 0;
}
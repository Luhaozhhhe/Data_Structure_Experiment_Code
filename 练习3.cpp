#include<iostream>
using namespace std;

template<class T>
class DoubleNode {
public:
	T data;
	DoubleNode<T>* left, * right;
};

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

template<class T>
Double<T>::Double()
{
	LeftEnd = new DoubleNode<T>;
	LeftEnd->data = 0;
	LeftEnd->right = LeftEnd;
	LeftEnd->left = LeftEnd;
}


template<class T>
void Double<T>::Erase()
{
	DoubleNode<T>* current = LeftEnd->right;
	while (current != LeftEnd)
	{
		current = LeftEnd->right;
		delete LeftEnd;
		LeftEnd = current;
	}
	cout << "erasing!" << endl;
}

template<class T>
bool Double<T>::Isempty()const
{
	if (LeftEnd->right == LeftEnd)
		return true;
	else
		return false;
}

template<class T>
int Double<T>::Len()const
{
	DoubleNode<T>* current = LeftEnd->right;
	int index = 0;
	while (current != LeftEnd)
	{
		index++;
		current = current->right;
	}
	return index;
}

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

template<class T>
void Double<T>::output(ostream& out)const
{
	DoubleNode<T>* current;
	for (current = LeftEnd->right; current != LeftEnd; current = current->right)
	{
		out << current->data << " ";
	}
}

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
		cout << "wrong!at least one" << endl;
		return;
	}
	cout << "input" << num << "numbers：" << endl;
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
		cout << "wrong" << endl;
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
		cout << "wrong" << endl;
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



//split
template<class T>
void split(Double<T>a, Double<T>b)
{
	Double<T>c;
	cout << "input the numbers：" << endl;
	int num;
L:cin >> num;
	if (num < 1)
	{
		cout << "wrong!again" << endl;
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

int main()
{
	cout << "choose one：" << endl;
	cout << "A.int   B.float   C.char" << endl;
	char m;
L:cin >> m;
	if (m == 'A')
	{
		Double<int>a, b;
		split(a, b);
		cout << "a：" << endl << a << endl;
		cout << "b：" << endl << b << endl;
	}
	if (m == 'B')
	{
		Double<float>a, b;
		split(a, b);
		cout << "a：" << endl << a << endl;
		cout << "b：" << endl << b << endl;
	}
	if (m == 'C')
	{
		Double<char>a, b;
		split(a, b);
		cout << "a：" << endl << a << endl;
		cout << "b：" << endl << b << endl;
	}
	if (m != 'A' && m != 'B' && m != 'C')
	{
		cout << "wrong!again" << endl;
		goto L;
	}
	return 0;
}
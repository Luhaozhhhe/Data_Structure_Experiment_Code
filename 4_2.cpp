#include<iostream>
using namespace std;

template<class T>
class Node {
public:
	T data;
	Node<T>* link;
};

template<class T>
class LinkedStack {
public:
	template<class T>//重载输出运算符
	friend ostream& operator<<(ostream& out, LinkedStack<T>&);
	template<class T>//重载输入运算符
	friend istream& operator>>(istream& in, LinkedStack<T>&);
	LinkedStack() { top = 0; }
	bool IsEmpty()const { return top == 0; }
	T Top()const;//栈顶元素
	LinkedStack<T>& Push(const T& x);//进栈
	LinkedStack<T>& Pop(T& x);//出栈
	LinkedStack<T>& Delete(const T& x);//删除元素
	bool Find(const T& x)const;//查找元素
	Node<T>* top;
};
template<class T>//重载输出运算符
ostream& operator<<(ostream& out, LinkedStack<T>& x)
{
	while (!x.IsEmpty())
	{
		T temp;
		x.Pop(temp);
		out << temp;
		if (!x.IsEmpty())
			out << " ";
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, LinkedStack<T>& x)
{
	cout << "please input the number:";
	int num;
	in >> num;
	for (int i = 0; i < num; i++)
	{
		T temp;
		in >> temp;
		x.Push(temp);
	}
	return in;
}

template<class T>//获取栈顶元素
T LinkedStack<T>::Top()const
{
	return top->data;
}

template<class T>//进栈
LinkedStack<T>& LinkedStack<T>::Push(const T& x)
{
	Node<T>* p = new Node<T>;
	p->data = x;
	p->link = top;
	top = p;
	return *this;
}

template<class T>//出栈
LinkedStack<T>& LinkedStack<T>::Pop(T& x)
{
	x = top->data;
	Node<T>* p = top;
	top = top->link;
	delete p;
	return *this;
}

template<class T>//删除元素
LinkedStack<T>& LinkedStack<T>::Delete(const T& x)
{
	Node<T>* current = top;
	if (current->data == x)
	{
		top = top->link;
		delete current;
	}
	else
	{
		Node<T>* temp = current;
		current = current->link;
		while (current)
		{
			if (current->data == x)
			{
				temp->link = current->link;
				delete current;
				return *this;
			}
			current = current->link;
			temp = temp->link;
		}
	}
	return *this;
}

template<class T>//查找元素
bool LinkedStack<T>::Find(const T& x)const
{
	Node<T>* temp = top;
	while (temp)
	{
		if (temp->data == x)
			return 1;
		temp = temp->link;
	}
	return 0;
}

template<class T>
void delete_all(LinkedStack<T>& s, const T& x)
{
	while (s.Find(x))
	{
		s.Delete(x);
	}
}

int main()
{
	char x;
	cin >> x;
	LinkedStack<char>zqzy;
	cin >> zqzy;
	if (zqzy.IsEmpty())
	{
		cout << "empty stack!";
		return 0;
	}
	delete_all(zqzy, x);
	cout << zqzy;
	return 0;
}
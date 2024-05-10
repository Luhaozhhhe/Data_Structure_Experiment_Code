/*
#include<iostream>
using namespace std;
template<typename T>
//定义一个node类
class node {
public:
	node* next;
	T data;
	node() {
		next = nullptr;
	}
	node(T a) {
		data = a;
		next = nullptr;
	}
};

template<typename T>
class Chain {
public:
	node<T>* head;
	node<T>* tail;
	Chain() {
		head = tail = nullptr;
	}
//insert函数负责查找a的位置
	void insert(T a) {
		node<T>* tmp = new node<T>(a);
		if (head = nullptr) {
			head = tail = tmp;
		}
		else {
			tail->next = tmp;
			tail = tmp;
		}
	}
	//打印函数负责遍历所有的数据进行输出
	void print() {
		node<T>* cur = head;
		while (cur != nullptr) {
			cout << cur->data << " ";
			cur = cur->next;
		}

	}
	int length() {
		node<T>* cur = head;
		int len = 0;
		while (cur!= nullptr) {
			len++;
			cur = cur->next;
		}
		return len;
	}

};

template<typename T>
void meld(Chain<T> c1, Chain<T> c2, Chain<T>&c3) {
	int min = 0;
	if (c1.length() < c2.length()) {
		min = c1.length();
	}
	else {
		min = c2.length();
	}
	node<T>* cur1 = c1.head;
	node<T>* cur2 = c2.head;

	for (int i = 0; i < min; i++) {
		c3.insert(cur1->data);
		c3.insert(cur2->data);
		cur1=cur1->next;
		cur2=cur2->next;
	}
	if (min == c1.length() && min == c2.length()) {
		return;
	}
	else if (min == c1.length()) {
		//输出c2的剩余部分即可
		while (cur2 != nullptr) {
			c3.insert(cur2->data);
			cur2 = cur2->next;
		}
		return;
	}
	else {
		while (cur1 != nullptr) {
			c3.insert(cur1->data);
			cur1 = cur1->next;
		}
		return;
	}

}
//类编写完毕，下面利用main函数来检验一下能否实现功能。

int main() {
	int a[10];
	node<int>* p = new node<int>[5];
	for (int i = 0; i < 4; i++)
	{
		cin >> a[i];
		p[i] = a[i];
	}
	Chain<int>c1;
	for (int i = 0; i < 4; i++)
	{
		c1.insert(p[i].data);
	}
	c1.print();
	cout << c1.length();
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> a[i];
		p[i] = a[i];
	}
	Chain<int>c2;
	for (int i = 0; i < 5; i++)
	{
		c2.insert(p[i].data);
	}
	c2.print();
	cout << c2.length();
	cout << endl;
	Chain<int>c3;
	meld(c1, c2, c3);
	c3.print();
	cout << c3.length();



	return 0;
}
*/

#include<iostream>
using namespace std;

template <typename T>
class node
{
public:
	T data;
	node* next;
	node()
	{
		next = nullptr;
	}
	node(T a)
	{
		data = a;
		next = nullptr;
	}
};
template <typename T>
class Chain
{
public:
	node<T>* head;
	node<T>* tail;
	Chain()
	{
		head = tail = nullptr;
	}
	void Insert(T a)
	{
		node<T>* tmp = new node<T>(a);
		if (head == nullptr)
		{
			head = tail = tmp;
		}
		else
		{
			tail->next = tmp;
			tail = tmp;
		}
	}
	void Print()
	{
		node<T>* cur = head;
		while (cur != nullptr)
		{
			cout << cur->data << " ";
			cur = cur->next;
		}
	}
	int Length()
	{
		node<T>* cur = head;
		int len = 0;
		while (cur != nullptr)
		{
			len++;
			cur = cur->next;
		}
		return len;
	}
};
template <typename T>
void meld(Chain<T>c1, Chain<T>c2, Chain<T>& c3)
{
	int min = 0;
	if (c1.Length() < c2.Length())
	{
		min = c1.Length();
	}
	else
	{
		min = c2.Length();
	}
	node<T>* cur1 = c1.head;
	node<T>* cur2 = c2.head;
	for (int i = 0; i < min; i++)
	{
		c3.Insert(cur1->data);
		c3.Insert(cur2->data);
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	if (min == c1.Length() && min == c2.Length())
	{
		return;
	}
	else if (min == c1.Length())
	{
		while (cur2 != nullptr)
		{
			c3.Insert(cur2->data);
			cur2 = cur2->next;
		}
		return;
	}
	else
	{
		while (cur1 != nullptr)
		{
			c3.Insert(cur1->data);
			cur1 = cur1->next;
		}
		return;
	}

}
int main()
{
	int a[10];
	node<int>* p = new node<int>[5];
	for (int i = 0; i < 4; i++)
	{
		cin >> a[i];
		p[i] = a[i];
	}
	Chain<int>c1;
	for (int i = 0; i < 4; i++)
	{
		c1.Insert(p[i].data);
	}
	cout << "print c1" << endl;
	c1.Print();
	cout << endl;
	cout << "print c1 length" << endl;

	cout << c1.Length();
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cin >> a[i];
		p[i] = a[i];
	}
	Chain<int>c2;
	for (int i = 0; i < 10; i++)
	{
		c2.Insert(p[i].data);
	}
	cout << "print c2" << endl;
	c2.Print();
	cout << endl;
	cout << "print c2 length" << endl;
	cout << c2.Length();
	cout << endl;
	Chain<int>c3;
	meld(c1, c2, c3);
	cout << "print c3" << endl;
	c3.Print();
	cout << endl;
	cout << "print c3 length" << endl;
	cout << c3.Length();


}

/*问题解决：
第一个c1的时间复杂度为O(n)；第二个c2的时间复杂度为O(n)；
c3为两个的叠加，即为O(n);
*/
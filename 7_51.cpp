#include<iostream>
using namespace std;

//链表节点类
template<class T>
class ChainNode {
public:
	T data;
	ChainNode<T>* link;
};

//链表类，程序需要使用的是链表的Insert和Append函数
template<class T>
class Chain {

public:
	Chain() { first = 0; last = 0; }//构造函数
	bool Isempty()const { return first == 0; }//判断链表是否为空
	int Len()const;//返回链表的长度
	bool Find(int k, T& x)const;//查找链表中是否有相应的值
	int Search(const T& x)const;//查找链表中值的位置
	Chain<T>& Delete(int k, T& x);//删除链表中元素
	Chain<T>& Insert(int k, const T& x);//插入元素
	Chain<T>& Append(const T& x);//拓展链表
	void output(ostream& out)const;//输出链表
	void Erase();//删除元素

public:
	ChainNode<T>* first, * last;
};

template<class T>//删除元素
void Chain<T>::Erase()
{
	ChainNode<T>* current;
	while (first)
	{
		current = first->link;
		delete first;
		first = current;
	}
}

template<class T>//返回链表的长度
int Chain<T>::Len()const
{
	ChainNode<T>* current = first;
	int index = 0;
	while (current)
	{
		index++;
		current = current->link;
	}
	return index;
}

template<class T>//查找链表中是否有相应的值
bool Chain<T>::Find(int k, T& x)const
{
	if (k < 1)return false;
	ChainNode<T>* current = first;
	int index = 1;
	while (index < k && current)
	{
		current = current->link;
		index++;
	}
	if (current)
	{
		x = current->data;
		return true;
	}
	return false;
}

template<class T>//查找链表中值的位置
int Chain<T>::Search(const T& x)const
{
	ChainNode<T>* current = first;
	int index = 1;
	while (current && current->data != x)
	{
		current = current->link;
		index++;
	}
	if (current)
		return index;
	return 0;
}

template<class T>//删除链表中元素
Chain<T>& Chain<T>::Delete(int k, T& x)
{
	ChainNode<T>* current = first;
	if (k == 1)
		first = first->link;
	else
	{
		ChainNode<T>* q = first;
		for (int index = 1; index < k - 1 && q; index++)
		{
			q = q->link;
		}
		current = q->link;
		q->link = current->link;
	}
	x = current->data;
	delete current;
	return *this;
}

template<class T>//插入元素
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

template<class T>//输出链表
void Chain<T>::output(ostream& out)const
{
	ChainNode<T>* current;
	for (current = first; current; current = current->link)
	{
		out << current->data << " ";
	}
}

template<class T>//重载输出运算符
ostream& operator<<(ostream& out, const Chain<T>& x)
{
	x.output(out);
	return out;
}



template<class T>//拓展链表
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



//节点类，使用到的是<<、>>、构造、默认构造、col、value等函数成员或数据成员
template<class T>
class CNode {
public:
	template<class T>
	friend ostream& operator<<(ostream& out, const CNode<T>&);
	template<class T>
	friend istream& operator>>(istream& in, CNode<T>&);
	CNode<T>() = default;
	CNode<T>(int x, T y)
	{
		col = x;
		value = y;
	}
	CNode<T>& operator=(const CNode<T>& x);
	int operator!=(const CNode<T>& y)
	{
		return (value != y.value);
	}
	void Output(ostream& out)const
	{
		out << "  column:" << col << "  value:" << value;
	}
public:
	int col;
	T value;
};



template<class T>//重载输出运算符
ostream& operator<<(ostream& out, const CNode<T>& x)
{
	x.Output(out);
	out << endl;
	return out;
}

template<class T>//重载输入运算符
istream& operator>>(istream& in, CNode<T>& x)
{
	cout << "Please input colume:";
	in >> x.col;
	cout << "Please input value:";
	in >> x.value;
	return in;
}



template<class T>//重载=运算符
CNode<T>& CNode<T>:: operator=(const CNode<T>& x)
{
	col = x.col;
	value = x.value;
	return *this;
}



//行头节点类，使用到的是<<、>>、row、Chain<CNode<T>>b等函数成员或数据成员
template<class T>
class HeadNode {
	template<class T>
	friend ostream& operator<<(ostream&, const HeadNode<T>&);
	template<class T>
	friend istream& operator>>(istream&, HeadNode<T>&);

public:
	int operator!=(const HeadNode<T>& y)
	{
		return (row != y.row);
	}
	void Output(ostream& out)const
	{
		out << "row:" << row;
	}
public:
	int row;
	Chain<CNode<T>>b;
};



template<class T>
ostream& operator<<(ostream& out, const HeadNode<T>& x)
{
	x.Output(out);
	out << endl;
	return out;
}



template<class T>
istream& operator>>(istream& in, HeadNode<T>& x)
{
	cout << "Please input row:";
	in >> x.row;
	return in;
}



//把行节点连接起来的链表，也保存整个稀疏矩阵的整体行号和列号
//需要增加存数、取数、加、减、乘操作
template<class T>
class LinkedMatrix {
public:
	template<class T>
	friend ostream& operator<<(ostream&, const LinkedMatrix<T>&);//输出双层链表中全部元素
	template<class T>
	friend istream& operator>>(istream&, LinkedMatrix<T>& b);//输入双层链表中全部元素
	LinkedMatrix<T>& Store(const T& x, int r, int c);//存数函数
	T Retrieve(int i, int j)const;//取数函数
	LinkedMatrix(int r, int c);//构造函数
	void Transpose(LinkedMatrix<T>& b)const;//转置函数
	LinkedMatrix<T>operator+(const LinkedMatrix<T>& x)const;//重载矩阵加法
	LinkedMatrix<T>operator-(const LinkedMatrix<T>& x)const;//重载矩阵减法
	LinkedMatrix<T>operator*(const LinkedMatrix<T>& x)const;//重载矩阵乘法
private:
	int rows;
	int cols;
	Chain<HeadNode<T>>a;
};



template<class T>//重载输出运算符
ostream& operator<<(ostream& out, const LinkedMatrix<T>& x)
{
	//开始时p指向头节点链表的头指针，之后p遍历头节点链表
	ChainNode<HeadNode<T>>* p = x.a.first;
	while (p)
	{
		//temp指向p的数据域
		HeadNode<T>temp = p->data;
		//判断当前行链表是否为空，是的话移到下一个行链表，以此类推
		if (temp.b.first)
		{
			//temp2指向当前行链表的头节点
			ChainNode<CNode<T>>* temp2 = temp.b.first;
			//输出行号
			out << temp;
			//当行链表中有元素时靠temp2的移动将元素依次输出
			while (temp2)
			{
				CNode<T>b = temp2->data;
				out << b;
				temp2 = temp2->link;
			}
			cout << endl;
		}
		p = p->link;
	}
	return out;
}



template<class T>//重载输入运算符
istream& operator>>(istream& in, LinkedMatrix<T>& b)
{
	cout << "please input the number that is not 0";
	int count, r, c;
	T x;
	in >> count;
	//通过调用Store函数将所有元素输入
	for (int i = 1; i <= count; i++)
	{
		cout << "please input" << i << "'s value，row，col：";
		in >> x >> r >> c;
		b.Store(x, r, c);
	}
	return in;
}



template<class T>//存数函数
LinkedMatrix<T>& LinkedMatrix<T>::Store(const T& x, int r, int c)
{
	//将x插入链表分三种情况：1、插入行链表头部；2、插中间；3、插尾部

	//p指向头节点链表的头指针
	ChainNode<HeadNode<T>>* p = a.first;
	//使p移动到r行所在位置
	while (p->data.row != r)
	{
		p = p->link;
	}
	//q指向第r行的行链表的头节点
	ChainNode<CNode<T>>* q = p->data.b.first;
	//如果此行为空则直接用Append插入
	if (!q)
	{
		q = new ChainNode<CNode<T>>;
		q->data.col = c;
		q->data.value = x;
		p->data.b.Append(q->data);
		return *this;
	}
	//num用来统计插入到链表中间的具体位置坐标
	int num = 0;
	//此行不为空则依次遍历插入位置
	while (q)
	{
		if (q->data.col == c)
		{
			cout << "have been datas!cannot input!";
			return *this;
		}
		//当遇到列号比c大的元素时将c插入到num位置
		if (q->data.col > c)
		{
			ChainNode<CNode<T>>* q3 = new ChainNode<CNode<T>>;
			q3->data.col = c;
			q3->data.value = x;
			p->data.b.Insert(num, q3->data);
			return *this;
		}
		q = q->link;
		num++;
	}
	//遍历完后没有合适位置则直接插入队尾
	ChainNode<CNode<T>>* q1 = new ChainNode<CNode<T>>;
	q1->data.col = c;
	q1->data.value = x;
	p->data.b.Append(q1->data);
	return *this;
}



template<class T>//取数函数
T LinkedMatrix<T>::Retrieve(int r, int c)const
{
	ChainNode<HeadNode<T>>* p1 = a.first;
	HeadNode<T>temp1 = p1->data;
	while (temp1.row != r)
	{
		p1 = p1->link;
		temp1 = p1->data;
	}
	ChainNode<CNode<T>>* p2 = temp1.b.first;
	CNode<T>temp2 = p2->data;
	while (temp2.col < c && p2)
	{
		p2 = p2->link;
		temp2 = p2->data;
	}
	T val = temp2.value;
	return T;
}



template<class T>//构造函数
LinkedMatrix<T>::LinkedMatrix(int r, int c)
{
	//在构造函数中将头节点链表通过Append函数全部初始化并加上行号row
	rows = r;
	cols = c;
	ChainNode<HeadNode<T>>* p = new ChainNode<HeadNode<T>>;
	for (int i = 1; i <= rows; i++)
	{
		p->data.row = i;
		a.Append(p->data);
	}
}



template<class T>//转置矩阵
void LinkedMatrix<T>::Transpose(LinkedMatrix<T>& x)const
{
	//依次遍历双层链表中所有元素，通过Store函数将其行列交换并插入新的双层链表x中
	ChainNode<HeadNode<T>>* temp1 = a.first;
	ChainNode<CNode<T>>* temp2 = temp1->data.b.first;
	while (temp1)
	{
		ChainNode<CNode<T>>* next = temp2;
		while (next)
		{
			x.Store(next->data.value, next->data.col, temp1->data.row);
			next = next->link;
		}
		temp1 = temp1->link;
		if (!temp1)
			break;
		temp2 = temp1->data.b.first;
	}
}


template<class T>//重载矩阵加法
LinkedMatrix<T> LinkedMatrix<T>::operator+(const LinkedMatrix<T>& x)const
{
	LinkedMatrix<T>y(rows, cols);
	ChainNode<HeadNode<T>>* temp1 = a.first;
	ChainNode<HeadNode<T>>* temp2 = x.a.first;
	ChainNode<HeadNode<T>>* temp3 = y.a.first;
	//同时遍历两个链表的每一行
	while (temp1 && temp2)
	{
		ChainNode<CNode<T>>* temp4 = temp1->data.b.first;
		ChainNode<CNode<T>>* temp5 = temp2->data.b.first;
		//当两个行链表都不为空时
		while (temp4 && temp5)
		{
			//列号相等则进行加法
			if (temp4->data.col == temp5->data.col)
			{
				//如果相加后的value不为0则Append到新行链表中
				if (temp4->data.value + temp5->data.value)
				{
					CNode<T>a(temp4->data.col, temp4->data.value + temp5->data.value);
					temp3->data.b.Append(a);
				}
				temp4 = temp4->link;
				temp5 = temp5->link;
				if (!(temp4 && temp5))
					break;
			}
			//一个的列号小于另一个列号，则将前一个Append进新链表，并将前一个行链表指针右移
			if (temp4->data.col < temp5->data.col)
			{
				CNode<T>a(temp4->data.col, temp4->data.value);
				temp3->data.b.Append(a);
				temp4 = temp4->link;
				if (!temp4)
					break;
			}
			//一个的列号大于另一个列号，则将后一个Append进新链表，并将后一个行链表指针右移
			if (temp4->data.col > temp5->data.col)
			{
				CNode<T>a(temp5->data.col, temp5->data.value);
				temp3->data.b.Append(a);
				temp5 = temp5->link;
				if (!temp5)
					break;
			}
		}
		//后一个行链表已经遍历完，则把前一个链表所有剩余元素Append进新链表
		while (temp4 && !temp5)
		{
			CNode<T>a(temp4->data.col, temp4->data.value);
			temp3->data.b.Append(a);
			temp4 = temp4->link;
		}
		//前一个行链表已经遍历完，则把后一个链表所有剩余元素Append进新链表
		while (!temp4 && temp5)
		{
			CNode<T>a(temp5->data.col, temp5->data.value);
			temp3->data.b.Append(a);
			temp5 = temp5->link;
		}
		temp1 = temp1->link;
		temp2 = temp2->link;
		temp3 = temp3->link;
	}
	return y;
}

template<class T>//重载矩阵减法
LinkedMatrix<T> LinkedMatrix<T>::operator-(const LinkedMatrix<T>& x)const
{
	LinkedMatrix<T>y(rows, cols);
	ChainNode<HeadNode<T>>* temp1 = a.first;
	ChainNode<HeadNode<T>>* temp2 = x.a.first;
	ChainNode<HeadNode<T>>* temp3 = y.a.first;
	while (temp1 && temp2)
	{
		ChainNode<CNode<T>>* temp4 = temp1->data.b.first;
		ChainNode<CNode<T>>* temp5 = temp2->data.b.first;
		while (temp4 && temp5)
		{

			if (temp4->data.col == temp5->data.col)
			{
				if (temp4->data.value - temp5->data.value)
				{
					CNode<T>a(temp4->data.col, temp4->data.value - temp5->data.value);
					temp3->data.b.Append(a);
				}
				temp4 = temp4->link;
				temp5 = temp5->link;
				if (!(temp4 && temp5))
					break;
			}
			if (temp4->data.col < temp5->data.col)
			{
				CNode<T>a(temp4->data.col, temp4->data.value);
				temp3->data.b.Append(a);
				temp4 = temp4->link;
				if (!temp4)
					break;
			}
			if (temp4->data.col > temp5->data.col)
			{
				CNode<T>a(temp5->data.col, -(temp5->data.value));
				temp3->data.b.Append(a);
				temp5 = temp5->link;
				if (!temp5)
					break;
			}
		}
		while (temp4 && !temp5)
		{
			CNode<T>a(temp4->data.col, temp4->data.value);
			temp3->data.b.Append(a);
			temp4 = temp4->link;
		}
		while (!temp4 && temp5)
		{
			CNode<T>a(temp5->data.col, -(temp5->data.value));
			temp3->data.b.Append(a);
			temp5 = temp5->link;
		}
		temp1 = temp1->link;
		temp2 = temp2->link;
		temp3 = temp3->link;
	}
	return y;
}

template<class T>//重载矩阵乘法
LinkedMatrix<T> LinkedMatrix<T>::operator*(const LinkedMatrix<T>& x)const
{
	LinkedMatrix<T>y(x.cols, x.rows);
	LinkedMatrix<T>z(rows, x.cols);
	//通过转置，使乘法简化为两个双层链表逐行相乘，从而避免了一行乘一列的复杂情况
	x.Transpose(y);
	ChainNode<HeadNode<T>>* temp1 = a.first;
	ChainNode<HeadNode<T>>* temp2 = y.a.first;
	ChainNode<CNode<T>>* zqzy1 = temp1->data.b.first;
	ChainNode<CNode<T>>* zqzy2 = temp2->data.b.first;
	//sum用来记录两行相乘后的数值
	T sum = 0;
	//第一个循环依次遍历左矩阵的每一行
	while (temp1)
	{
		//判断第一个矩阵不为空的行链表
		if (zqzy1)
		{
			//第二个循环依次遍历右矩阵的每一行
			while (temp2)
			{
				//当第二个矩阵的行链表为空时则移动到下一行
				while (!zqzy2)
				{
					temp2 = temp2->link;
					if (!temp2)
						return z;
					zqzy2 = temp2->data.b.first;
				}
				//两个行链表都不为空则判断行号，大于或小于则右移，等于则相乘
				while (zqzy1 && zqzy2)
				{
					while (zqzy1->data.col > zqzy2->data.col)
					{
						zqzy2 = zqzy2->link;
						if (!zqzy2)
							goto L;
					}
					while (zqzy1->data.col < zqzy2->data.col)
					{
						zqzy1 = zqzy1->link;
						if (!zqzy1)
							goto L;
					}
					if (zqzy1->data.col == zqzy2->data.col)
					{
						sum += zqzy1->data.value * zqzy2->data.value;
						zqzy1 = zqzy1->link;
						zqzy2 = zqzy2->link;
					}
				L:;
				}
				//当sum不为0则Append进新链表
				if (sum)
				{
					z.Store(sum, temp1->data.row, temp2->data.row);
					sum = 0;
				}
				zqzy1 = temp1->data.b.first;
				temp2 = temp2->link;
				if (!temp2)
					break;
				zqzy2 = temp2->data.b.first;
			}
		}
		temp1 = temp1->link;
		if (!temp1)
			break;
		zqzy1 = temp1->data.b.first;
		temp2 = y.a.first;
		zqzy2 = temp2->data.b.first;
	}
	return z;
}

int main()
{
	int row1, col1, row2, col2;
	cout << "input the first Matrix's row and col:";
	cin >> row1 >> col1;
	cout << "input the second Matrix's row and col";
	cin >> row2 >> col2;
	LinkedMatrix<int>x1(row1, col1);
	LinkedMatrix<int>x2(row2, col2);
	LinkedMatrix<int>x3(row1, col1);
	LinkedMatrix<int>x4(row1, col1);
	LinkedMatrix<int>x5(row1, col2);
	cout << endl << "input the first Matrix:" << endl;
	cin >> x1;
	cout << endl << "input the second Matrix:" << endl;
	cin >> x2;
	x3 = x1 + x2;
	cout << endl << "the  + result:" << endl << x3 << endl;
	x4 = x1 - x2;
	cout << "the - result：" << endl << x4 << endl;
	x5 = x1 * x2;
	cout << "the * result：" << endl << x5 << endl;
	return 0;
}
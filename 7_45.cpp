#include<iostream>
using namespace std;

template<class T>
class Term {
public:
	//元素所在原矩阵的行号row、列号col、元素数值value
	int row;
	int col;
	T value;
};

template<class T>
class SparseMatrix {
	template<class T>
	friend ostream& operator<<(ostream& out, const SparseMatrix<T>& m);
	template<class T>
	friend istream& operator>>(istream& in, SparseMatrix<T>& m);

public:
	SparseMatrix(int maxTerms = 10);//构造函数，赋值MaxTerms，其他数据成员赋值为0
	void Transpose(SparseMatrix<T>& b)const;//将原矩阵转置存储在b中
	void Add(const SparseMatrix<T>& b, SparseMatrix<T>& c)const;//原矩阵和b矩阵相加存储在c中
	void Append(const Term<T>& t);//在数组的末尾插入元素
	void no_same();//去除数组中行号和列号相等的元素的后者，并且把两者相加后的值附给前者
	void no_zero();//去除数组中值为零的元素
	SparseMatrix<T>operator*(const SparseMatrix<T>x)const;//重定义数组乘法

	//稀疏矩阵行数rows，列数cols，非零元素数terms，能够承载的最多非零元素数MaxTerms
	int rows, cols;
	int terms;
	int MaxTerms;
	Term<T>* a;//一维数组来存储三元组
};

template<class T>//构造函数，赋值MaxTerms，其他数据成员赋值为0
SparseMatrix<T>::SparseMatrix(int maxTerms)
{
	MaxTerms = maxTerms;
	a = new Term<T>[MaxTerms];
	terms = rows = cols = 0;
}

template<class T>//重载输出
ostream& operator<<(ostream& out, const SparseMatrix<T>& x)
{
	out << "rows=" << x.rows << " columns=" << x.cols << endl;
	out << "nonzero terms=" << x.terms << endl;
	for (int i = 0; i < x.terms; i++)
	{
		out << "a(" << x.a[i].row << "," << x.a[i].col << ")=" << x.a[i].value << endl;
	}
	cout << endl;
	return out;
}

template<class T>//重载输入
istream& operator>>(istream& in, SparseMatrix<T>& x)
{
	cout << "Enter number of rows,columns,and terms" << endl;
	in >> x.rows >> x.cols >> x.terms;
	for (int i = 0; i < x.terms; i++)
	{
		cout << "Enter row,column,and value of term" << (i + 1) << endl;
		in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
	}
	cout << endl;
	return in;
}

template<class T>//将原矩阵转置存储在b中
void SparseMatrix<T>::Transpose(SparseMatrix<T>& b)const
{
	b.cols = rows;
	b.rows = cols;
	b.terms = terms;
	int* ColSize, * RowNext;
	ColSize = new int[cols + 1];
	RowNext = new int[cols + 1];
	for (int i = 1; i <= cols; i++)
		ColSize[i] = 0;
	for (int i = 0; i < terms; i++)
		ColSize[a[i].col]++;
	RowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
		RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
	for (int i = 0; i < terms; i++)
	{
		int j = RowNext[a[i].col]++;
		b.a[j].row = a[i].col;
		b.a[j].col = a[i].row;
		b.a[j].value = a[i].value;
	}
}

template<class T>//原矩阵和b矩阵相加存储在c中
void SparseMatrix<T>::Add(const SparseMatrix<T>& b, SparseMatrix<T>& c)const
{
	c.rows = rows;
	c.cols = cols;
	c.terms = 0;
	int ct = 0, cb = 0;
	while (ct < terms && cb < b.terms)
	{
		int indt = a[ct].row * cols + a[ct].col;
		int indb = b.a[cb].row * cols + b.a[cb].col;
		if (indt < indb)
		{
			c.Append(a[ct]);
			ct++;
		}
		if (indt > indb)
		{
			c.Append(b.a[cb]);
			cb++;
		}
		if (indt == indb)
		{
			if (a[ct].value + b.a[cb].value)
			{
				Term<T>t;
				t.row = a[ct].row;
				t.col = a[ct].col;
				t.value = a[ct].value + b.a[cb].value;
				c.Append(t);
			}
			ct++;
			cb++;
		}
	}
	for (; ct < terms; ct++)
		c.Append(a[ct]);
	for (; cb < b.terms; cb++)
		c.Append(b.a[cb]);
}

template<class T>//在数组的末尾插入元素
void SparseMatrix<T>::Append(const Term<T>& t)
{
	a[terms] = t;
	terms++;
}

template<class T>//去除数组中行号和列号相等的元素的后者，并且把两者相加后的值附给前者
void SparseMatrix<T>::no_same()
{
	for (int i = 0; i < terms - 1; i++)
	{
		for (int j = i + 1; j < terms; j++)
		{
			if (a[i].row == a[j].row && a[i].col == a[j].col)
			{
				a[i].value += a[j].value;
				terms--;
				for (int k = j; k < terms; k++)
				{
					a[k].row = a[k + 1].row;
					a[k].col = a[k + 1].col;
					a[k].value = a[k + 1].value;
				}
				j--;
			}
		}
	}
}

template<class T>//去除数组中值为零的元素
void SparseMatrix<T>::no_zero()
{
	for (int i = 0; i < terms; i++)
	{
		if (a[i].value == 0)
		{
			terms--;
			for (int j = i; j < terms; j++)
			{
				a[j].row = a[j + 1].row;
				a[j].col = a[j + 1].col;
				a[j].value = a[j + 1].value;
			}
			i--;
		}
	}
}

template<class T>//重定义数组乘法
SparseMatrix<T> SparseMatrix<T>::operator*(const SparseMatrix<T>v)const
{
	//乘法是前一个矩阵的行乘以后一个矩阵的列，将后一个矩阵转置后变成了前一个矩阵的行乘以后一个矩阵的行
	//因为都是行主顺序存储的，所以就可以二重循环遍历完两个矩阵中的所有元素了
	SparseMatrix<T>m, x;
	v.Transpose(x);
	m.rows = rows;
	m.cols = x.rows;
	//sum是乘后矩阵在数组中存储位置的索引
	int sum = 0;
	for (int i = 0; i < terms; i++)
	{
		for (int j = 0; j < x.terms; j++)
		{
			if (a[i].col == x.a[j].col)
			{
				m.terms++;
				m.a[sum].row = a[i].row;
				m.a[sum].col = x.a[j].row;
				m.a[sum].value = a[i].value * x.a[j].value;
				sum++;
			}
		}
	}
	//清除行号和列号相同元素的后者以及值为零的元素
	m.no_same();
	m.no_zero();
	return m;
}

int main()
{
	SparseMatrix<int>x, y;
	cout << "input the first Matrix:" << endl;
	cin >> x;
	cout << "input the second Matrix:" << endl;
	cin >> y;
	cout << "the result is:" << endl;
	cout << x * y;
	return 0;
}
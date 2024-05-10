#include<iostream>
using namespace std;

template <typename T>
class lowerTriangularMatrix
{
public:
	template<typename T>
	friend ostream& operator<<(ostream& out, const lowerTriangularMatrix<T>& x);
	template<typename T>
	friend istream& operator>>(istream& in, lowerTriangularMatrix<T>& x);
	lowerTriangularMatrix(int size);
	lowerTriangularMatrix();
	~lowerTriangularMatrix();
	void Outpuut1(ostream& out)const;
	void Outpuut2(ostream& out)const;
	void transpose(lowerTriangularMatrix<T>& x)const;
	lowerTriangularMatrix<T>operator+(const lowerTriangularMatrix<T>& x)const;
	lowerTriangularMatrix<T>operator-(const lowerTriangularMatrix<T>& x)const;
	lowerTriangularMatrix<T>& Store(const T& x, int i, int j);
	T Retrieve(int i, int j)const;
private:
	int n;
	T* t;
};
//重载了>>符号，能输出矩阵
template<typename T>
istream& operator>>(istream& in, lowerTriangularMatrix<T>& x)
{
	for (int i = 0; i < x.n * (x.n + 1) / 2; i++)
	{
		in >> x.t[i];
	}
	return in;//能够连续使用>>符号
}

//同理，重载<<符号
template<typename T>
ostream& operator<<(ostream& out, const lowerTriangularMatrix<T>& x)
{
	x.Outpuut1(out);
	return out;
}

template <typename T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int size)
{
	n = size;//输入矩阵的大小
	t = new T[n * (n + 1) / 2];//给t数组new相应的大小
}

template <typename T>
lowerTriangularMatrix<T>::lowerTriangularMatrix()
{

}

template<typename T>
lowerTriangularMatrix<T>::~lowerTriangularMatrix()
{
	delete[]t;
}
//输出下三角
template<typename T>
void lowerTriangularMatrix<T>::Outpuut1(ostream& out)const
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			cout << t[i * (i - 1) / 2 + j] << " ";
		}
		for (int j = 0; j < n - i; j++)
		{
			cout << 0 << " ";
		}
		cout << endl;
	}
}
//输出上三角
template<typename T>
void lowerTriangularMatrix<T>::Outpuut2(ostream& out)const
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			cout << 0 << " ";
		}
		for (int j = 0; j <= n - i; j++)
		{
			cout << t[(2 * n - i + 2) * (i - 1) / 2 + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>
void lowerTriangularMatrix<T>::transpose(lowerTriangularMatrix<T>& x)const
{
	int count1 = 0, count2 = 0, position = 0, temp = 0;
	for (int i = 1; i <= n; i++)
	{
		temp = i;//temp是一个中间量，表示原矩阵同列元素在数组中的位置差值
		count1 = i * (i + 1) / 2;//count表示原矩阵前i行的元素个数
		position = count1;
		for (int j = 0; j <= n - i; j++)
		{
		
			x.t[count2 + j] = t[position - 1];
			position += temp;
			temp++;
		}
		count2 += (n - i + 1);//每循环一遍就加上了n-i+1，count2表示前面行数的元素总个数
	}
}

//重载+运算符
template<typename T>
lowerTriangularMatrix<T>lowerTriangularMatrix<T>::operator+(const lowerTriangularMatrix<T>& x)const
{
	lowerTriangularMatrix<T>y;
	for (int i = 0; i < n * (n + 1) / 2; i++)
	{
		y.t[i] = t[i] + x.t[i];
	}
	return y;
}
//重载-运算符
template<typename T>
lowerTriangularMatrix<T>lowerTriangularMatrix<T>::operator-(const lowerTriangularMatrix<T>& x)const
{
	lowerTriangularMatrix<T>y;
	for (int i = 0; i < n * (n + 1) / 2; i++)
	{
		y.t[i] = t[i] - x.t[i];
	}
	return y;
}
//修改
template<typename T>
lowerTriangularMatrix<T>& lowerTriangularMatrix<T>::Store(const T& x, int i, int j)
{
	t[i * (i - 1) / 2 + j - 1] = x;
	return *this;
}
//读取矩阵的值
template<typename T>
T lowerTriangularMatrix<T>::Retrieve(int i, int j)const
{
	if (i >= j)
	{
		return t[i * (i - 1) / 2 + j - 1];
	}
	else
	{
		return 0;
	}
}

int main()
{
	cout << "choose one:" << endl;
	cout << "A.int   B.float   C.char" << endl;
	char m;
L:cin >> m;
	if (m == 'A')
	{
		int size;
		cout << endl << "please input size:";
		cin >> size;
		lowerTriangularMatrix<int>x(size), y(size);
		cout << endl << "please input the Matrix:" << endl;
		cin >> x;
		cout << endl << "the lowerMatrix is:" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "the upperMatrix is：" << endl;
		y.Outpuut2(cout);
	}
	if (m == 'B')
	{
		int size;
		cout << endl << "please input size:";
		cin >> size;
		lowerTriangularMatrix<float>x(size), y(size);
		cout << endl << "please input the Matrix:" << endl;
		cin >> x;
		cout << endl << "the lowerMatrix is:" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "the upperMatrix is：" << endl;
		y.Outpuut2(cout);
	}
	if (m == 'C')
	{
		int size;
		cout << endl << "please input size:";
		cin >> size;
		lowerTriangularMatrix<char>x(size), y(size);
		cout << endl << "please input the Matrix:" << endl;
		cin >> x;
		cout << endl << "the lowerMatrix is:" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "the upperMatrix is：" << endl;
		y.Outpuut2(cout);
	}
	if (m != 'A' && m != 'B' && m != 'C')
	{
		cout << "wrong!again：" << endl;
		goto L;
	}
	return 0;
}
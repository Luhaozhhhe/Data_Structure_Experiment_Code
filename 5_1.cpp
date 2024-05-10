#include<iostream>
using namespace std;

template<typename T1, typename T2>
class HashTable
{
public:
	HashTable(int divisor);//构造函数创建一个divisor长度的数组和与之匹配的bool类型初值全为true的empty和neverUsed数组
	bool Search(const T1& t1, const T2& t2)const;//搜索函数，判断关键字为t2的位置的值是否为t1
	HashTable<T1, T2>& Insert(const T1& t);//插入函数，将t插入的相应的位置
	HashTable<T1, T2>& Delete(const T2& t);//查找删除坐标函数，要删除的键为t的坐标位置
	void Output();//输出函数，当此位置当前非空的情况下则将其输出
	void NewHash();//散列重组函数
private:
	int hSearch(const T2& t);//查找插入坐标函数，寻找适合k插入的数组的坐标位置
	int dSearch(const T2& t);//查找删除坐标函数，要删除的键为k的坐标位置
	int divisor;//除数
	T1* ht;//存取原始数据
	bool* empty;//判断当前位置是否为空，为空则可插入元素
	bool* neverUsed;//判断当前位置是否被使用过
};
template<typename T1, typename T2>//构造函数创建一个divisor长度的数组和与之匹配的bool类型初值全为true的empty和neverUsed数组
HashTable<T1, T2>::HashTable(int divisor)
{
	this->divisor = divisor;
	ht = new T1[this->divisor];
	empty = new bool[this->divisor];
	neverUsed = new bool[this->divisor];
	for (int i = 0; i < this->divisor; i++)
	{
		empty[i] = neverUsed[i] = true;
	}
}
template<typename T1, typename T2>//输出函数，当此位置当前非空的情况下则将其输出
void HashTable<T1, T2>::Output()
{
	cout << "the result is：" << endl;
	for (int i = 0; i < this->divisor; i++)
	{
		if (!empty[i])
		{
			cout << "(" << i << ")" << ht[i] << " ";
		}
	}
	cout << endl;
}
template<typename T1, typename T2>//查找插入坐标函数，寻找适合k插入的数组的坐标位置
int HashTable<T1, T2>::hSearch(const T2& t)
{
	int i = t % this->divisor;
	int j = i;
	do
	{
		if (empty[j] || ht[j] == t)//当j位置是空的或者j位置原来的数就是t则直接返回j
		{
			return j;
		}
		j = (j + 1) % this->divisor;//看下一个位置是否为空或者为j
	} while (j != i);
	return j;
}
template<typename T1, typename T2>//查找删除坐标函数，要删除的键为k的坐标位置
int HashTable<T1, T2>::dSearch(const T2& t)
{
	int i = t % this->divisor;
	int j = i;
	do
	{
		if (neverUsed[j] || ht[j] == t)//当j位置被使用过或者j位置原来的数就是k则直接返回j
		{
			return j;
		}
		j = (j + 1) % this->divisor;//看下一个位置是否为空或者为j
	} while (j != i);
	return j;
}
template<typename T1, typename T2>//搜索函数，判断关键字为t2的位置的值是否为t1
bool HashTable<T1, T2>::Search(const T1& t1, const T2& t2)const
{
	int b = hSearch(t2);
	if (empty[b] || ht[b] != t2)
	{
		cout << "cannot find" << t2 << endl;
		return false;
	}
	cout << "the number" << t2 << "is in" << b << "bins" << endl;
	return true;
}
template<typename T1, typename T2>//插入函数，将t插入的相应的位置
HashTable<T1, T2>& HashTable<T1, T2>::Insert(const T1& t)
{
	T2 t2 = t;
	//b表示适合k插入的位置坐标
	int b = hSearch(t);
	//当此位置为空，则将b插入即可
	if (empty[b])
	{
		empty[b] = neverUsed[b] = false;
		ht[b] = t;
		return *this;
	}
	//当此位置的值已经为k则表示没有空间插入重复元素或另外一种情况是数组满了，查找坐标函数j=i，且ht[j]!=k，直接返回*this即可
	return *this;
}
template<typename T1, typename T2>//查找删除坐标函数，要删除的键为t的坐标位置
HashTable<T1, T2>& HashTable<T1, T2>::Delete(const T2& t)
{
	int b = dSearch(t);
	if (ht[b] == t)
	{
		if (empty[b] == true)
		{
			cout << "deleted again!" << endl;
		}
		else
		{
			//当删除一个元素后要判断已空位置曾经被使用过的是否超过60%，是的话进行重组
			empty[b] = true;
			int sum1 = 0;//sum1记录已空位置数量
			int sum2 = 0;//sum2记录已空位置曾经被使用过的数量
			for (int i = 0; i < this->divisor; i++)
			{
				if (empty[i])//如果已空，sum1++
				{
					sum1++;
					if (!neverUsed[i])//如果曾经被使用过，sum2++
					{
						sum2++;
					}
				}
			}
			if (float(sum1 / sum2) > 0.6)
			{
				NewHash();
			}
		}
	}
	else
	{
		cout << "cannot find!" << endl;
	}
	return *this;
}
template<typename T1, typename T2>//散列重组函数
void HashTable<T1, T2>::NewHash()
{
	for (int i = 0; i < this->divisor; i++)
	{
		if (empty[i] == true && neverUsed[i] == false)
		{
			neverUsed[i] = true;
			continue;
		}
		if (empty[i] == false)
		{
			T1 t1 = ht[i];
			T2 t2 = t1;
			//判断此位置的元素是否应该插入到此位置
			int b = hSearch(t2);
			//是的话进行下一重循环
			if (b == i)
			{
				continue;
			}
			//不是的话将此位置的empty和neverUsed设置为true表示此位置没有元素，然后将对应元素插入到合适位置
			empty[i] = true;
			neverUsed[i] = true;
			Insert(t1);
		}
	}
}
int main()
{
	int num, delnum;
	cout << "please input the number:";
	cin >> num;
	HashTable<int, int>zqzy(num);
	for (int i = 0; i < num; i++)
	{
		int k;
		cout << "input" << i + 1 << "k's number:";
		cin >> k;
		zqzy.Insert(k);
	}
	zqzy.Output();
	cout << "please input the deleted:";
	cin >> delnum;
	for (int i = 0; i < delnum; i++)
	{
		int k;
		cout << "input" << i + 1 << "k's number:";
		cin >> k;
		zqzy.Delete(k);
	}
	zqzy.Output();
	return 0;
}

#include<iostream>
#include<cstring>
using namespace std;

class Queue
{
public:
	bool IsEmpty() { return front == rear; };
	bool IsFull() { return (((rear + 1) % MaxSize == front) ? 1 : 0); };
	void AddLeft(int a);
	void AddRight(int a);
	void DeleteLeft();
	void DeleteRight();
	void print();
	Queue(int M);
private:
	int front;
	int rear;
	int MaxSize;
	int* queue;
};
void Queue::print()
{
	//正常情况下队尾大于队首直接输出
	if (rear > front)
	{
		for (int i = front + 1; i <= rear; i++)
		{
			cout << queue[i];
			if (i != rear)
				cout << " ";
		}
	}
	//当队尾小于队首的时候
	if (rear < front)
	{
		//首先要看队首是否是数组中最后一个元素，是的话直接从0输出，不是的话从front+1输出
		if (front == MaxSize - 1)
		{
			for (int i = 0; i <= rear; i++)
			{
				cout << queue[i];
				if (i != rear)
					cout << " ";
			}
		}
		else
		{
			for (int i = front + 1; i < MaxSize; i++)
				cout << queue[i] << " ";
			for (int i = 0; i <= rear; i++)
			{
				cout << queue[i];
				if (i != rear)
					cout << " ";
			}
		}
	}
	cout << endl;
}
Queue::Queue(int M)
{
	MaxSize = M + 1;
	queue = new int[M];
	front = rear = 0;
}
void Queue::AddLeft(int a)
{
	if (IsFull())
	{
		cout << "FULL" << endl;
		return;
	}
	queue[front] = a;
	if (front)//如果front不是0的时候减一取余，找到前面一个位置，否则就用最大值减去1，找到最后一个位置
	{
		front = (front - 1) % MaxSize;
	}
	else
		front = MaxSize - 1;
	print();
	return;
}
void Queue::AddRight(int a)
{
	if (IsFull())
	{
		cout << "FULL" << endl;
	}
	rear = (rear + 1) % MaxSize;//直接加一取余就行，若是最后一个位置的话就直接跳转到第一个
	queue[rear] = a;
	print();
	return;
}
void Queue::DeleteLeft()
{
	if (IsEmpty())
	{
		cout << "WRONG" << endl;
		return;
	}
	front = (front + 1) % MaxSize;//直接删，不用重新赋值
	print();
	return;
}
void Queue::DeleteRight()
{
	if (IsEmpty())
	{
		cout << "WRONG" << endl;
		return;
	}
	if (rear)//如果不是0的话就直接减一取余，是0的话就到最后一位
		rear = (rear - 1) % MaxSize;
	else
		rear = MaxSize - 1;
	print();
	return;
}
int main()
{
	Queue zqzy(10);
	string str;
	int num, x;
L:cin >> str;
	if (str == "AddLeft")
	{
		cin >> num;
		zqzy.AddLeft(num);
		goto L;
	}
	if (str == "AddRight")
	{
		cin >> num;
		zqzy.AddRight(num);
		goto L;
	}
	if (str == "DeleteRight")
	{
		zqzy.DeleteRight();
		goto L;
	}
	if (str == "DeleteLeft")
	{
		zqzy.DeleteLeft();
		goto L;
	}
	if (str == "IsFull")
	{
		if (zqzy.IsFull())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
		goto L;
	}
	if (str == "IsEmpty")
	{
		if (zqzy.IsEmpty())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
		goto L;
	}
	if (str == "End")
	{
		cout << endl;
	}
	return 0;
}
//主要思路是通过输出顺序的替换与改变，实现左插与右插。
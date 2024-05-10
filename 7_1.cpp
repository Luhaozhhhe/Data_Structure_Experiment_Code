#include<iostream>
using namespace std;
class maxheap {
private:
	int* h;
	int maxelement, minelement, num;
	int count = 0;
public:
	maxheap(int max, int min, int n) {
		maxelement = max; minelement = min; num = n;
		h = new int[2 * num + 2];
		h[0] = maxelement;
		for (int i = n; i <= 2 * n + 1; i++) h[i] = minelement;//赋值
	}
	void push(int k) {//push的实现方法是如果不是根节点，或者k的值比其父亲节点要大的话，就把父亲节点往下移
		if (k > maxelement || k < minelement);//如果不符合数据要求，就不输入
		else {
			int i = ++count;
			while (i != 1 && k > h[i / 2]) {
				h[i] = h[i / 2];
				i /= 2;
			}
			h[i] = k;//如果k比父亲节点小的话，就正常插入
		}
	}

	void pop() {//pop函数实现的是删除操作，删完根节点之后，判断最后一个位置应该插入的点
		int y = h[count--];
		int i = 1, ci = 2;
		while (ci <= count) {
			if (ci < count && h[ci] < h[ci + 1]) ci++;
			if (y > h[ci]) break;
			h[i] = h[ci];
			i = ci;
			ci *= 2;
		}
		h[i] = y;
	}
	void show() {
		for (int i = 1; i <= count; i++)cout << h[i] << " ";
		cout << endl;
	}
};
int main() {
	maxheap mh(100, 2, 10);
	int n;
	for (int i = 0; i < 10; i++) {
		cin >> n;
		mh.push(n);
	}
	mh.show();
	mh.pop();
	mh.show();
	mh.pop();
	mh.show();
	mh.pop();
	mh.show();
}

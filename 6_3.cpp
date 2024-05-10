#include<iostream>
#include<stack>
#include<queue>
#include<cstring>
#include <iomanip>
using namespace std;
class node {
public:
	char data;
	node* left;
	node* right;
	node(char x) {
		data = x;
		left = right = NULL;
	}
};
//中缀表达式转后缀表达式，跟前面一题是一样的
string zztohz(string s) {
	int l = s.length();
	string target;
	string a;
	stack<char>sk;
	for (int i = 0; i < l; i++) {
		char temp = (char)s[i];
		switch (temp)
		{
		case'(':
			sk.push(temp);
			break;
		case')':
			while (sk.top() != '(') {
				a = sk.top();
				target.append(a);
				sk.pop();
			}
			sk.pop();
			break;
		case'+':
		case'-':
			if (sk.empty() || sk.top() == '(')
				sk.push(temp);
			else {
				while (!sk.empty() && sk.top() != '(') {
					a = sk.top();
					target.append(a);
					sk.pop();
				}
				sk.push(temp);
			}
			break;
		case'*':
		case'/':
			if (sk.empty() || (sk.top() != '/' && sk.top() != '*'))sk.push(temp);
			else {
				a = sk.top();
				target.append(a);
				sk.pop();
				sk.push(temp);
			}
			break;
		default:
			a = temp;
			target.append(a);
			break;
		}
	}
	while (!sk.empty()) {
		a = sk.top();
		target.append(a);
		sk.pop();
	}
	return target;
}
class binarytree {
public:
	node* root = NULL;
	binarytree(string st) {//构造函数将字符串转成二叉树
		string s = zztohz(st);
		int l = s.length();
		stack<node*>sk;
		for (int i = 0; i < l; i++) {
			char t = (char)s[i];
			if (t != '+' && t != '-' && t != '*' && t != '/') {
				root = new node(t);
				sk.push(root);
			}
			else {
				root = new node(t);
				if (!sk.empty()) {
					root->right = sk.top();
					sk.pop();
				}
				if (!sk.empty()) {
					root->left = sk.top();
					sk.pop();
				}
				sk.push(root);
			}
		}
	}
	int depth(node* p) {//递归计算树高
		if (p == NULL)return 0;
		int i = depth(p->left);
		int j = depth(p->right);
		return i > j ? i + 1 : j + 1;
	}
	void output(node* root, int depth1) {
		if (root != NULL)
		{
			output(root->right, depth1 + 1);
			cout << setw(4 * (depth1 - 1)) << " ";
			cout << root->data << endl;
			output(root->left, depth1 + 1);
		}
	}
	int leafnum(node* p) {
		if (p->left == NULL && p->right == NULL) return 1;
		int i = leafnum(p->left);
		int j = leafnum(p->right);
		return i + j;
	}
	void changelr(node* p) {
		if (p != NULL) {
			node* t = p->left;
			p->left = p->right;
			p->right = t;
			changelr(p->left);
			changelr(p->right);
		}
	}
	void bianli() {//完成树的遍历
		queue<node*>qe;
		qe.push(root);
		while (!qe.empty()) {
			node* p = qe.front();
			cout << p->data << " ";
			qe.pop();
			if (p->left)qe.push(p->left);
			if (p->right)qe.push(p->right);
		}
		cout << endl;
	}
	int width() {
		int width = 0;
		queue<node*>qe;
		qe.push(root);
		while (1) {
			if (qe.empty())break;//直到qe空了再跳出
			else {
				int l = qe.size();
				for (int i = 0; i < l; i++) {//l记录上一层有多少个结点，然后把每个结点的左右节点分别插入到队列里后，弹出该节点。同时比较现在的
					node* p = qe.front();//队列大小（下一层节点数量）和width大小，进行更新。
					if (p->left)qe.push(p->left);
					if (p->right)qe.push(p->right);
					qe.pop();
				}
				width = width > qe.size() ? width : qe.size();
			}
		}
		return width;
	}
};
int main() {
	string s;
	cin >> s;
	string s1 = zztohz(s);
	binarytree b(s);
	b.output(b.root, 1);
	cout << endl;
	cout << b.leafnum(b.root) << endl;
	b.changelr(b.root);
	b.output(b.root, 1);
	b.bianli();
	cout << b.width();
}


//实现思路：对于前两问，用递归很容易实现。第三问需要层次遍历，显然不能用递归。对于每个节点，访问时是先进先出的，所以应该利用队列。每个节点输出之后，就要接着判断他的两个孩子节点是否可以入队，这样的话就实现了从上到下，从左到右的入队顺序，即输出顺序。第四问和第三问的思路很类似，需要利用的就是每次上一层节点全输出完毕之后，队列里留下的就是他们的所有孩子的节点，也就是下一层的节点数量。不断对比进行更新width就可以了。
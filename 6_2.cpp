#include<iostream>
#include<stack>
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
//中缀表达式转后缀表达式
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
		default://数字直接弹出即可
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
};
int main() {
	string s;
	cin >> s;
	binarytree b(s);
	b.output(b.root, 1);
	cout<<zztohz(s);
}
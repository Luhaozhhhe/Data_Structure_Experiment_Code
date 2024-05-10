#include<iostream>
#include<cstring>
using namespace std;
class hnode {
public:
	int parent, lchild, rchild;
	char s;
	int weight;
};
class htree {
public:
	hnode* ht;
	char** res;//存放编码字符串数组
	int num;//叶节点数目
	htree(int x) { ht = new hnode[2 * x]; num = x; res = new char* [x + 1]; }
	//找到最小的两个节点
	void findtwominnode(int pos, int& m1, int& m2) {//找出前pos项里最小的两项
		double min1 = 9999999;
		double min2 = 9999999;
		for (int i = 1; i <= pos; i++) {
			if (ht[i].weight < min1 && ht[i].parent == 0) {//只有根节点的parent是0
				min1 = ht[i].weight;
				m1 = i;
			}
		}
		for (int j = 1; j <= pos; j++) {
			if (ht[j].weight < min2 && ht[j].weight != min1 && ht[j].parent == 0) {//必须要根节点，根节点合并成新的根节点
				min2 = ht[j].weight;
				m2 = j;
			}
		}
	}
	//创建霍夫曼树
	void create() {//叶子节点在main函数里手动输入了，这里要生成霍夫曼树需要把第n+1到2n-1位补齐；num是叶节点数目
		for (int i = num + 1; i <= 2 * num - 1; i++) {
			int m1, m2;
			findtwominnode(i - 1, m1, m2);
			ht[i].weight = ht[m1].weight + ht[m2].weight;
			ht[m1].parent = i;
			ht[m2].parent = i;
			ht[i].lchild = m1;
			ht[i].rchild = m2;//第一小的是左孩子，第二小的是右孩子
			ht[i].parent = 0;
		}
	}
	//编码
	void encode() {//对每个叶节点进行编码，所以目的是要找到叶节点，即左孩子右孩子均位0
		char* cd = new char[num + 1];
		int now = 1;//记录哪个位置正在被编码
		int nowpar;//被编码位置的父亲下标
		int i = 1;
		while (i <= num) {//共需要处理n次
			int index = 0;
			now = i;
			nowpar = ht[now].parent;
			while (nowpar != 0) {
				if (ht[nowpar].lchild == now) cd[index++] = '0';
				else cd[index++] = '1';
				now = nowpar;
				nowpar = ht[now].parent;
			}
			res[i] = new char[index + 2];
			for (int j = 0; j < index; j++) res[i][j] = cd[index - j - 1];
			res[i][index] = '\0';
			i++;
		}
	}
	//输出：
	void output() {
		for (int i = 1; i <= num; i++) {
			cout << ht[i].s << "the encode is:" << res[i] << endl;
		}
	}

	//译码
	void decode(char* s) {
		int len = strlen(s);
		int i = 0;
		int index = 2 * num - 1;
		cout << "the decode is:";
		while (i < len) {
			if (s[i] == '0') {
				index = ht[index].lchild;
				if (ht[index].lchild == 0 && ht[index].rchild == 0) {//判断是否为root节点
					cout << ht[index].s;
					index = 2 * num - 1;
				}
			}
			else {
				index = ht[index].rchild;
				if (ht[index].lchild == 0 && ht[index].rchild == 0) {
					cout << ht[index].s;
					index = 2 * num - 1;//每次识别出来一个字符后，index回到根节点的位置，便于继续译码下一个字符。
				}
			}
			i++;
		}
		cout << endl;
	}
};
int main() {
	cout << "please input:";
	char s[100];
	cin >> s;
	cout << endl;
	int l = strlen(s);
	char* s1 = new char[l];//存放删除重复元素后的字符串
	int sl = 0, m = 1;
	int* w = new int[l];
	for (int i = 0; i < l; i++)w[i] = 0;
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < sl; j++) {
			if (s[i] == s1[j]) { m = 0; break; }
			m = 1;
		}
		if (m) {
			s1[sl] = s[i];
			for (int k = 0; k < l; k++) {
				if (s[k] == s1[sl]) w[sl]++;
			}
			sl++;
		}
	}
	htree h(sl);
	for (int i = 0; i < sl; i++) {
		h.ht[i + 1].s = s1[i];
		h.ht[i + 1].parent = 0;
		h.ht[i + 1].lchild = 0;
		h.ht[i + 1].rchild = 0;
		h.ht[i + 1].weight = w[i];
	}
	h.create();
	h.encode();
	h.output();
	cout << endl;
	cout << "the encode result is:";
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < sl; j++) {
			if (s[i] == s1[j]) {
				cout << h.res[j + 1];
				break;
			}
		}
	}
	cout << endl;
	cout << endl;
	cout << "please input the decoding:";
	char n[100]; cin >> n;
	cout << endl;
	h.decode(n);
}
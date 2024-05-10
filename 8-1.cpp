#include <iostream>
using namespace std;
template<class T>
struct Node {//AVL树节点
	T data;
	Node* lchild;
	Node* rchild;
	int height;//平衡因子
	Node(const T& e, Node* lc, Node* rc, int h = 0)
		:data(e), lchild(lc), rchild(rc), height(h) {}
};
template<class T>
class AVLTree {
public:
	Node<T>* root;
	void insert(const T& x, Node<T>*& t);//插入
	AVLTree() {
		root = NULL;
	}
	~AVLTree() {
		set_empty(root);
	}
	bool is_empty();
	void set_empty(Node<T>* t);
	int get_height(Node<T>* t);
	void insert(const T& x);
	void rotate_right(Node<T>*& t);//LL型 右单旋
	void rotate_left(Node<T>*& t);//RR型 左单旋
	void right_left(Node<T>*& t);//RL型 先右后左旋
	void left_right(Node<T>*& t);//LR型 先左后右旋
	int tree_height(Node<T>* t);
	void get_near(Node<T>* t);
};
template<class T>
bool AVLTree<T>::is_empty() {//判断是否为空
	return root == NULL;
}
template<class T>
void AVLTree<T>::set_empty(Node<T>* t) {//清空()递归实现
	if (t != NULL) {
		set_empty(t->lchild);
		set_empty(t->rchild);
		delete t;
	}
}
template<class T>
int AVLTree<T>::get_height(Node<T>* t) {
	return t == NULL ? 0 : t->height;
}
//从根节点开始将key与节点值比较，如果key小于节点值，进入左子树；如果key大于节点值，进入右子树；直到找到或子树为空停止（同BST）
template<class T>
void AVLTree<T>::insert(const T& x, Node<T>*& t) {
	if (t == NULL) {
		t = new Node<T>(x, NULL, NULL);//插入后只有一个根节点
	}
	else if (x < t->data) {//小的值进入左子树（递归实现）
		insert(x, t->lchild);
		if (get_height(t->lchild) - get_height(t->rchild) == 2) {//插入后不平衡旋转
			if (get_height(t->lchild->lchild) > get_height(t->lchild->rchild))
				rotate_right(t);//LL型
			else left_right(t);//LR型
		}
	}
	else if (x > t->data) {//大的值进右子树
		insert(x, t->rchild);
		if (get_height(t->rchild) - get_height(t->lchild) == 2) {
			if (get_height(t->rchild->lchild) > get_height(t->rchild->rchild))
				right_left(t);//RL型
			else rotate_left(t);//RR型
		}
	}
	t->height = max(get_height(t->lchild), get_height(t->rchild)) + 1;
}
template<class T>
void AVLTree<T>::insert(const T& x) {
	insert(x, root);
}
template<class T>
void AVLTree<T>::rotate_right(Node<T>*& t) {//LL型
	Node<T>* p = t->lchild;//t是不平衡的节点，p是其左孩子
	t->lchild = p->rchild;//旋转 t的左孩子变为p的右孩子
	p->rchild = t;//p替代t的位置 旋转完成
	//旋转后结点位置变化，需要更新树高（很重要！！！）
	t->height = max(get_height(t->lchild), get_height(t->rchild)) + 1;
	p->height = max(get_height(p->lchild), t->height) + 1;
	t = p;
}
template<class T>
void AVLTree<T>::rotate_left(Node<T>*& t) {//RR型(和LL是镜像)
	Node<T>* p = t->rchild;
	t->rchild = p->lchild;
	p->lchild = t;
	t->height = max(get_height(t->lchild), get_height(t->rchild)) + 1;
	p->height = max(get_height(p->rchild), t->height) + 1;
	t = p;
}
template<class T>
void AVLTree<T>::left_right(Node<T>*& t) {//LR型
	rotate_left(t->lchild);//先对A的左子树根结点RR旋转
	rotate_right(t);//再对A结点LL旋转 
}
template<class T>
void AVLTree<T>::right_left(Node<T>*& t) {//RL型 与LR镜像
	rotate_right(t->rchild);
	rotate_left(t);
}
template<class T>
int AVLTree<T>::tree_height(Node<T>* t) {//平衡因子(递归)
	if (t == NULL)return 0;
	int lh = 0, rh = 0;
	lh = tree_height(t->lchild) + 1;
	rh = tree_height(t->rchild) + 1;
	return max(lh, rh);
}
template<class T>
void AVLTree<T>::get_near(Node<T>* t) {//因为高度差最大也就1，所以最后只需在高度差为1和为2的时候判断是否只向单边拓展即可
	if (t == NULL)return;
	if (t->lchild == NULL && t->rchild == NULL) {//是叶子节点了
		cout << t->data << " ";
		return;
	}
	int lh = 0, rh = 0;
	lh = tree_height(t->lchild);
	rh = tree_height(t->rchild);
	if (lh == 1 && rh == 2) {
		get_near(t->lchild);
	}
	else if (lh == 2 && rh == 1) {
		get_near(t->rchild);
	}
	else {
		get_near(t->lchild);
		get_near(t->rchild);
	}
}
int main() {
	AVLTree<int> avl;
	int tmp;
	cout << endl << "-----insert datas-----" << endl << endl;
	for (int i = 0; i < 9; i++) {
		cin >> tmp;
		avl.insert(tmp);
	}
	cout << endl;
	cout << endl << "-----the height of tree-----" << endl << endl;
	cout << avl.tree_height(avl.root) << endl;
	cout << endl;
	cout << endl << "-----the nearest:-----" << endl << endl;
	avl.get_near(avl.root);
	cout << endl << endl;
	return 0;
}
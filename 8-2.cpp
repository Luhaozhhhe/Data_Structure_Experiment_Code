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
private:
	Node<T>* root;
	void insert(const T& x, Node<T>*& t);//插入
	void remove(T e, Node<T>*& t);//删除
	void set_empty();//清空
public:
	AVLTree() {
		root = NULL;
	}
	~AVLTree() {
		set_empty(root);
	}
	bool is_empty();
	void set_empty(Node<T>* t);
	T find_min(Node<T>* t);
	T find_max(Node<T>* t);
	int get_height(Node<T>* t);
	Node<T>* get_root();
	void insert(const T& x);
	void rotate_right(Node<T>*& t);//LL型 右单旋
	void rotate_left(Node<T>*& t);//RR型 左单旋
	void right_left(Node<T>*& t);//RL型 先右后左旋
	void left_right(Node<T>*& t);//LR型 先左后右旋
	void show_smaller(Node<T>* t);
	void show_bigger(Node<T>* t);
	void remove(T e);
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
void AVLTree<T>::set_empty() {
	this->set_empty(root);
}
template<class T>
int AVLTree<T>::get_height(Node<T>* t) {
	return t == NULL ? -1 : t->height;
}
template<class T>
Node<T>* AVLTree<T>::get_root() {
	return root;
}
template<class T>
T AVLTree<T>::find_max(Node<T>* t) {//最大值最靠右
	if (t->rchild == NULL)return t->data;
	else return find_max(t->rchild);
}
template<class T>
T AVLTree<T>::find_min(Node<T>* t) {//最小值最靠左
	if (t->lchild == NULL)return t->data;
	else return find_min(t->lchild);
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
	//cout<<get_height(t->lchild)<<" "<<get_height(t->rchild)<<endl;
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
void AVLTree<T>::remove(T e, Node<T>*& t) {//删除节点
	if (t == NULL)return;
	if (e < t->data)
		remove(e, t->lchild);
	else if (e > t->data)
		remove(e, t->rchild);
	else {//找到要删除元素了
		if (t->lchild != NULL && t->rchild != NULL) {//元素找到了并且左右子树都不为空(非叶子节点)
			Node<T>* p = t->rchild;
			while (p->lchild != NULL)p = p->lchild;//将要删除的节点用右子树中的最小节点代替
			t->data = p->data;
			remove(p->data, t->rchild); //递归删除该最小节点
		}
		else {//元素找到了并且左右子树有一个为空
			Node<T>* p = t->lchild == NULL ? t->rchild : t->lchild;//让p指向t的非空子树
			// cout<<t->data<<endl;
			delete t;
			t = p;//用孩子节点顶替原来位置
			return;
		}
	}
	//删除完节点之后要更新高度(很重要！！！)//和插入一样
	if (get_height(t->lchild) - get_height(t->rchild) == 2) {
		if (get_height(t->lchild->lchild) > get_height(t->lchild->rchild))
			rotate_right(t);
		else left_right(t);
	}
	else if (get_height(t->rchild) - get_height(t->lchild) == 2) {
		if (get_height(t->rchild->lchild) > get_height(t->rchild->rchild))
			right_left(t);
		else rotate_left(t);
	}
	t->height = max(get_height(t->lchild), get_height(t->rchild)) + 1;
}
template<class T>
void AVLTree<T>::remove(T e) {
	remove(e, root);
}
template<class T>
int AVLTree<T>::tree_height(Node<T>* t) {//平衡因子(递归)
	if (t == NULL)return 0;
	int lh = 0, rh = 0;
	lh = tree_height(t->lchild) + 1;
	rh = tree_height(t->rchild) + 1;
	return max(lh, rh);
}
/*

* 1.删除叶子结点。操作：直接删除，然后依次向上调整为AVL树。



2.删除非叶子节点，该节点只有左孩子。操作：该节点的值替换为左孩子节点的值，然后删除左孩子节点。

【左孩子节点为叶子结点，所以删除左孩子节点的情况为第1种情况。】

【为什么左孩子节点为叶子节点，因为删除节点前，该树是AVL树，由AVL树的定义知，每个节点的左右子树的高度差的绝对值<=1,

由于该节点只有左孩子，没有右孩子，如果左孩子还有子节点，那么将不满足每个节点的左右子树的高度差的绝对值<=1，所以左孩子节点为叶子结点】

3.删除非叶子节点，该节点只有右孩子。操作：该节点的值替换为右孩子节点的值，然后删除右孩子节点。

【右孩子节点为叶子结点，所以删除右孩子节点的情况为第1种情况。】【为什么右孩子节点为叶子节点？答案和第二种情况一样】

4.删除非叶子节点，该节点既有左孩子，又有右孩子。操作：该节点的值替换为该节点的前驱节点（或者后继节点），然后删除前驱节点（或者后继节点）。

【前驱结点:在中序遍历中，一个节点的前驱结点，先找到该节点的左孩子节点，再找左孩子节点的最后一个右孩子节点。向左走一步，然后向右走到头。

最后一个右孩子节点即为前驱节点】【后继节点：在中序遍历中，一个节点的后继结点，先找到该节点的右孩子节点，再找右孩子节点的最后一个左孩子节点。

向右走一步，然后向左走到头。最后一个左孩子节点即为前驱节点】

*/
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
template<class T>
void AVLTree<T>::show_smaller(Node<T>* t) {//从大到小
	if (t != NULL) {
		show_smaller(t->rchild);
		cout << t->data << " ";
		show_smaller(t->lchild);
	}
}
template<class T>
void AVLTree<T>::show_bigger(Node<T>* t) {//从小到大
	if (t != NULL) {
		show_bigger(t->lchild);
		cout << t->data << " ";
		show_bigger(t->rchild);
	}
}
int main() {
	AVLTree<int> avl;
	srand(time(NULL));
	int tmp;
	cout << endl << "-----插入随机数-----" << endl << endl;
	for (int i = 0; i < 100; i++) {
		tmp = rand() % 2333;
		cout << tmp << " ";
		avl.insert(tmp);
	}
	cout << endl;
	cout << endl << "-----从小到大输出-----" << endl << endl;
	avl.show_bigger(avl.get_root());
	cout << endl;
	cout << endl << "-----从大到小输出-----" << endl << endl;
	avl.show_smaller(avl.get_root());
	cout << endl;
	cout << endl << "-----树的高度-----" << endl << endl;
	cout << avl.tree_height(avl.get_root()) << endl;
	cout << endl << "-----删除最后一个插入的随机数-----" << endl << endl;
	avl.remove(tmp);
	avl.show_bigger(avl.get_root());
	cout << endl;
	cout << endl << "-----距离根最近的叶节点的值-----" << endl << endl;
	avl.get_near(avl.get_root());
	cout << endl << endl;
	return 0;
}
//
// Created by leeyoungjun on 2023/11/21.
//
/*
* 랭크 정수 이진트리
 *
 *
 * 1. 각 노드에  leftSize 필드를 추가한다: 1+ numberOfNodes(leftchild)

2. rank() 함수가 각 노드의 leftSize 필드를 갱신하도록 구현한다

3. search(3)이면 inorder 출력에서 3번째 출력, n이면 n번째 출력하도록 수정한다.

4. 각 노드에 Height(Tl) - Height(Tr)를 저장한다. LL 타입과 RR 타입에 대하여 split를 호출한다.
 이후 join 함수를 사용하여 LL, RR 타입이 제거 됨을 height 값을 출력하여 확인한다. > 교재 소스코드 5.7를 활용한다.

5. LR, RL 타입을 제거하면 보너스 점수 준다: + 20% 가산점 추가한다.
 *
*/


#include <iostream>
#define MaxCapacity 20
using namespace std;

class TreeNode {
	friend class Tree;
private:
	TreeNode* LeftChild;
	int data;
	int leftSize;
    int height; // 추가됨.
	TreeNode* RightChild;

public:
	TreeNode() {
		LeftChild = RightChild = NULL; leftSize = 0;
	}
	bool equals(TreeNode& x) {
		if (this->data == x.data)
			return true;
		else
			return false;
	}
	int getData() {
		return data;
	}
	friend ostream& operator<<(ostream&, TreeNode&);
};
ostream& operator<<(ostream& os, TreeNode& tn) {
	os << "[data: " << tn.data << ", leftSize: " << tn.leftSize << "]" << endl;
	return os;
}
class Tree {
public:
	Tree() {
		root = NULL;
	}
	Tree(const Tree& s)//copy constructor
	{
		root = copy(s.root);
	}
	TreeNode* inorderSucc(TreeNode* current);//현재노드를 넣음
	bool isLeafNode(TreeNode* current);
	void inorder() {
		inorder(root);
	}
	void preorder() {
		preorder(root);
	}
	void postorder() {
		postorder(root);
	}
	bool insert(int x);
	bool remove(int num);
	void rank() {
		rank(root);
	}
    void depth(){depth(root);} // TODO : 과제로 추가됨
	int search(int rank);//nth 작은 값을 찾는다
	// Driver
	int operator==(const Tree& t)
	{
		return equal(this->root, t.root);
	}
private:
	TreeNode* root;
	void inorder(TreeNode* CurrentNode);
	void preorder(TreeNode* CurrentNode);
	void postorder(TreeNode* CurrentNode);
	TreeNode* copy(TreeNode* orignode);
	int equal(TreeNode* a, TreeNode* b);
	int rank(TreeNode*);
    int depth(TreeNode*); //TODO
};
int Tree::rank(TreeNode* current) {
    //TODO
    //각 노드의 leftsize를 갱신한다.
    //rank는 자신을 root로 하는 하위 트리의 높이를 저장하는 것이다.
    //노드를 합칠 경우 rank가 낮은 트리가 랭크가 높은 트리에게 붙게 된다.

}
int Tree::depth(TreeNode* p){ //TODO
    //root가 p를 가리킨다.
    int lnum = depth(p->LeftChild);
    int rnum = depth(p->RightChild);
}

TreeNode* Tree::inorderSucc(TreeNode* current)
{
    //중위선회
    //왼쪽 leaf노드로 이동한다음 중간에 root노드를 거치고 오른쪽 트리를 순회하는 구조.
	TreeNode* temp = current->RightChild;
	if (current->RightChild != NULL)
		while (temp->LeftChild != NULL) temp = temp->LeftChild;
	return temp;
}
bool Tree::isLeafNode(TreeNode* current) {
	if (current->LeftChild == NULL && current->RightChild == NULL)
		return true;
	else
		return false;
}
void Tree::inorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		inorder(CurrentNode->LeftChild);
		cout << *CurrentNode;
		inorder(CurrentNode->RightChild);
	}
}

void Tree::preorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		cout << CurrentNode->data << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}

void Tree::postorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
}



TreeNode* Tree::copy(TreeNode* orignode)
{
	if (orignode) {
		TreeNode* temp = new TreeNode;
		temp->data = orignode->data;
		temp->LeftChild = copy(orignode->LeftChild);
		temp->RightChild = copy(orignode->RightChild);
		return temp;
	}
	else return 0;
}


// Workhorse
int Tree::equal(TreeNode* a, TreeNode* b)
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */
{
	if ((!a) && (!b)) return 1;  // both a and b are 0
	if (a && b &&                // both a and b are non-0
		(a->data == b->data)      // data is the same
		&& equal(a->LeftChild, b->LeftChild) // left subtrees are the same
		&& equal(a->RightChild, b->RightChild)) // right subtrees are the same
		return 1;
	return 0;
}


bool Tree::insert(int x) {// binary search tree를 만드는 입력 => A + B * C을 tree로 만드는 방법: 입력 해결하는 알고리즘 작성 방법을
							// 설계하여 구현
	TreeNode* p = root;
	TreeNode* q = NULL;

}

bool Tree::remove(int num) {
	TreeNode* p = root, * q = NULL, * parent = NULL;


}

int Tree::search(int rank) { //rank에서 사용되는? 것.
	TreeNode* p = root;

}
enum { Insert, Remove, Inorder, Preorder, Postorder, Search, Copy, Height, SplitJoin,Quit };
int main() {
	srand(time(NULL));
	Tree t;
	bool eq = false;
	int select = 0, rankNumber = 0;
	int max = 0, x = 0;
	while (select != 7)
	{
		int rnd = 0;
		cout << "BinarySearchTree. Select 0.Insert, 1. Remove, 2.Inorder, 3.Preorder, 4.Postorder, 5.Search, 6.Copy, 7.Quit =>";
		cin >> select;
		switch (select)
		{
		case Insert:
			cout << "The number of items = ";
			cin >> max;
			for (int i = 0; i < max; i++) {
				rnd = rand() % 20;
				if (!t.insert(rnd)) cout << "Insert Duplicated data" << endl;
			}

			break;
		case Remove:
			int x;
			cin >> x;
			cout << t.remove(x);//입력된 x에 대한 tree 노드를 찾아 삭제한다.
			cout << endl;
			break;
		case Inorder:
			cout << "inorder print:: ";
			t.inorder();
			cout << endl;
			break;
		case Preorder:
			cout << "preorder print:: ";
			t.preorder();
			cout << endl;
			break;
		case Postorder:
			cout << "postorder print:: ";
			t.postorder();
			cout << endl;
			break;
		case Search:
			t.rank();
			cout << "찾고자 하는 rank 순위 입력: ";
			cin >> x;
			rankNumber = t.search(x); // x번째 순위의 값을 찾는다
			cout << x << " 번째 순위 값은 " << rankNumber << endl;

			break;
		case Copy:
			eq = (t == Tree(t));//copy constructor를 호출
			if (eq) {
				cout << "compare result: true" << endl;
			}
			else
				cout << "compare result: false" << endl;
			break;

        case Height:
            t.depth();
            t.inorder();
            break;

        case SplitJoin:
            cin >> x;
            split(x,A,B,y);
            Tree tx = ThreeWayJoin(A,x,B);
            tx.inorder(); //split과 책에 있는 코드 활용해서 만들기
            break;

            
		case Quit:
			cout << "Quit" << endl;
			break;

		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}

	system("pause");
	return 0;

}


//
// Created by leeyoungjun on 2023/11/21.
//
//소스코드 5.3: Threaded Tree


//Tree 5.13 Threaded binary tree
/*
1. template version으로 Employee 객체를 노드에 저장
2. tree iterator를 사용하여 sum을 구한다
3. main에서 Insert, Remove, Inorder, IteratorInorder, Search, PrintTree는 Employee에 대하여 구현한다
4. Employee 객체는 화면에서 입력하지 않고 10개의 객체를 배열로 초기화 for문으로 입력한다.
5. main에서 InsertStudent, InorderStudent는 Student에 대하여 구현한다.
*/
//root가 있고 root는 빈 노드, 그리고 오른쪽 자식이 진짜 시작 노드가 된다. TODO 확인하기
#include <iostream>
#include <cstdlib>
#define MAX_VALUE 65536
using namespace std;

template <class T>
class ThreadedTree;
template <class T>
class ThreadedInorderIterator;

class Employee {
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname) :eno(sno), ename(sname) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
    bool operator>(Employee&);
	bool operator==(Employee&);
};

class Student {
	string snum;
	string sname;
	int age;
public:
	Student() {}
    Student(string num,string name) :snum(num), sname(name) {}
    friend ostream& operator<<(ostream& os, Student&);
    bool operator<(Student&);
    bool operator>(Student&);
	bool operator==(Student&);
};

//대소비교 오퍼레이터 Employee 객체

ostream& operator<<(ostream& os, Employee& em){
    os<<"[ eno : "<<em.eno<<", ename : "<<em.ename<<", salary : "<<em.salary<<" ]";
    return os;
}
bool Employee::operator<(Employee& em){
    //root라서 null인 경우에
    if(eno.length()==0){
        return true;
    }
    if(em.eno.length()==0){
        return false;
    }
    if(stoi(eno) < stoi(em.eno)){
        return true;
    } else {
        return false;
    }
}
bool Employee::operator>(Employee& em){
    if(stoi(eno) > stoi(em.eno)){
        return true;
    } else {
        return false;
    }
}

bool Employee::operator==(Employee & em) {
    if(stoi(eno) != stoi(em.eno)){
        return false;
    }
    if (stoi(ename) != stoi(em.ename)){
        return false;
    }
    if (salary != em.salary){
        return false;
    }
    return true;
}

//대소 비교 오퍼레이터 Student 객체

ostream& operator<<(ostream& os, Student& st){
    os<<"[ snum : "<<st.snum<<", sname : "<<st.sname<<", age : "<<st.age<<" ]";
    return os;
}
bool Student::operator<(Student& st){
    if(stoi(snum) < stoi(st.snum)){
        return true;
    } else {
        return false;
    }
}

bool Student::operator>(Student& st){
    if(stoi(snum) > stoi(st.snum)){
        return true;
    } else {
        return false;
    }
}

bool Student::operator==(Student & st) {
    if(stoi(snum) != stoi(st.snum)){
        return false;
    }
    if (sname != st.sname){
        return false;
    }
    if (age != st.age){
        return false;
    }
    return true;
}


template <class T>
class ThreadedNode {
	friend class ThreadedTree<T>;
	friend class ThreadedInorderIterator<T>;
private:
	bool LeftThread;
	ThreadedNode<T>* LeftChild;
	T data;
	ThreadedNode<T>* RightChild;
	bool RightThread;
public:
	ThreadedNode() { LeftChild = RightChild = 0; };
	ThreadedNode(T ch) { data = ch; };
	ThreadedNode(T ch, ThreadedNode<T>* lefty, ThreadedNode<T>* righty,
		bool lthread, bool rthread)
	{
		data = ch; LeftChild = lefty; RightChild = righty;
		LeftThread = lthread;  RightThread = rthread;
	};
};

template <class T>
class ThreadedTree {
	friend class ThreadedInorderIterator<T>;
private:
	ThreadedNode<T>* root;
	void Inorder(ThreadedNode<T>*, bool);
public:
	/* Constructor */
	ThreadedTree() {
		root = new ThreadedNode<T>;
		root->RightChild = root->LeftChild = root;
		root->data; //TODO?
		root->LeftThread = true; root->RightThread = false;
	};
	void InsertRight(ThreadedNode<T>*, T);
	bool Insert(T data);
	void Delete(T data);
	void Inorder();
	void PrintTree();
	bool Search(T data);
	ThreadedNode<T>* InorderSucc(ThreadedNode<T>*);
};

template<class T>
ThreadedNode<T>* ThreadedTree<T>::InorderSucc(ThreadedNode<T>* current)
{   //current에서 리프노드의 제일 왼쪽 노드를 반환한다.

	ThreadedNode<T>* temp = current->RightChild; //넣은 노드의 오른쪽 자식 포인터를 복사함.
	if (!current->RightThread) //오른쪽이 실제 노드일때
		while (!temp->LeftThread) temp = temp->LeftChild;//오른쪽 자식의 왼쪽 값이 실제 노드일때, 오른쪽 자식 포인터를 왼쪽 자식으로 이동시킴
	return temp; //포인터를 반환.
}

template <class T>
void ThreadedTree<T>::InsertRight(ThreadedNode<T>* s, T ch)
// Create node r; store ch in r; insert r as the right child of s
{
	ThreadedNode<T>* r = new ThreadedNode(ch);
	r->RightChild = s->RightChild;
	r->RightThread = s->RightThread;
	r->LeftChild = s;
	r->LeftThread = true; // LeftChild is a thread
	s->RightChild = r; // attach r to s
	s->RightThread = false;
	if (!r->RightThread) {
		ThreadedNode<T>* temp = InorderSucc(r); // returns the inorder successor of r
		temp->LeftChild = r;
	}
}

/* Function to delete an element */
template <class T>
void ThreadedTree<T>::Delete(T ch)
{
	ThreadedNode<T>* dest = root->LeftChild, * p = root;
	for (;;)
	{
		if (dest->data < ch)
		{
			/* not found */
			if (dest->RightThread)
				return;
			p = dest;
			dest = dest->RightChild;
		}
		else if (dest->data > ch)
		{
			/* not found */
			if (dest->LeftThread)
				return;
			p = dest;
			dest = dest->LeftChild;
		}
		else
		{
			/* found */
			break;
		}
	}
	ThreadedNode<T>* target = dest;
	if (!dest->RightThread && !dest->LeftThread)
	{
		/* dest has two children*/
		p = dest;
		/* find largest node at left child */
		target = dest->LeftChild;
		while (!target->RightThread)
		{
			p = target;
			target = target->RightChild;
		}
		/* using replace mode*/
		dest->data = target->data;
	}
	if (p->data > target->data && p->data == target->data)
	{
		if (target->RightThread && target->LeftThread)
		{
			p->LeftChild = target->LeftChild;
			p->LeftThread = true;
		}
		else if (target->RightThread)
		{
			ThreadedNode<T>* largest = target->LeftChild;
			while (!largest->RightThread)
			{
				largest = largest->RightChild;
			}
			largest->RightChild = p;
			p->LeftChild = target->LeftChild;
		}
		else
		{
			ThreadedNode<T>* smallest = target->RightChild;
			while (!smallest->LeftThread)
			{
				smallest = smallest->LeftChild;
			}
			smallest->LeftChild = target->LeftChild;
			p->LeftChild = target->RightChild;
		}
	}
	else
	{
		if (target->RightThread && target->LeftThread)
		{
			p->RightChild = target->RightChild;
			p->RightThread = true;
		}
		else if (target->RightThread)
		{
			ThreadedNode<T>* largest = target->LeftChild;
			while (!largest->RightThread)
			{
				largest = largest->RightChild;
			}
			largest->RightChild = target->RightChild;
			p->RightChild = target->LeftChild;
		}
		else
		{
			ThreadedNode<T>* smallest = target->RightChild;
			while (!smallest->LeftThread)
			{
				smallest = smallest->LeftChild;
			}
			smallest->LeftChild = p;
			p->RightChild = target->RightChild;
		}
	}
}
template <class T>
void ThreadedTree<T>::Inorder()
{
	Inorder(root, root->LeftThread);
}

template <class T>
void ThreadedTree<T>::Inorder(ThreadedNode<T>* CurrentNode, bool b)
{
	if (!b) {
		Inorder(CurrentNode->LeftChild, CurrentNode->LeftThread);
		cout << " " << CurrentNode->data;
		cout << "Inorder:" << "rightthread=" << CurrentNode->RightThread;
		if (CurrentNode->RightChild != root) Inorder(CurrentNode->RightChild, CurrentNode->RightThread);
	}
}

template <class T>
bool ThreadedTree<T>::Insert(T d)//leaf node에만 insert, 중간 노드에 insert 아님
{
	ThreadedNode<T>* p = root;
	ThreadedNode<T>* q = p;
	bool temp = p->LeftThread;
	while (!temp) {
		q = p;
		if (d == p->data) return false;
		if (d < p->data) { temp = p->LeftThread; p = p->LeftChild; }
		else { temp = p->RightThread; p = p->RightChild; }
	}
	p = new ThreadedNode<T>;
	p->data = d;
	//	if (q->LeftChild == q){ q->LeftChild = p;q->LeftThread = false;}
	//	else
	if (d < q->data)
	{
		p->RightChild = q; p->RightThread = true;
		p->LeftChild = q->LeftChild; p->LeftThread = q->LeftThread;
		q->LeftChild = p; q->LeftThread = false;
	}
	else
	{
		p->RightChild = q->RightChild; p->RightThread = q->RightThread;
		p->LeftChild = q; p->LeftThread = true;
		q->RightChild = p; q->RightThread = false;
	}
	return true;
}


/* Function to print tree */
template <class T>
void ThreadedTree<T>::PrintTree()
{
	ThreadedNode<T>* tmp = root, * p;
	for (;;)
	{
		p = tmp; //root에서 시작해서
		tmp = tmp->RightChild;//root의 오른쪽 자식으로 이동
		if (!p->RightThread)//오른쪽이 스레드가 아니라면(오른쪽 자식이 더 있다면)
		{
			while (!tmp->LeftThread) //왼쪽이 스레드가 나올때까지
			{
				tmp = tmp->LeftChild; //왼쪽 자식으로 이동
			}
		}
		if (tmp == root)
			break;
		cout << tmp->data << "   ";
	}
	cout << endl;
}

template <class T>
bool ThreadedTree<T>::Search(T data) {
    ThreadedNode<T>* tmp = root, * p;
	for (;;)
	{
		p = tmp;
		tmp = tmp->RightChild;
		if (!p->RightThread)
		{
			while (!tmp->LeftThread)
			{
				tmp = tmp->LeftChild;
			}
		}

		if (tmp == root)
			break;
		if (tmp->data == data){
            return true;
        }
	}

    return false;
}

template <class T>
class ThreadedInorderIterator {
public:
	void Inorder();
	T* Next();
	ThreadedInorderIterator(ThreadedTree<T> tree) : t(tree) {
		CurrentNode = t.root;
	};
private:
	ThreadedTree<T> t;
	ThreadedNode<T>* CurrentNode;
};

template <class T>
T* ThreadedInorderIterator<T>::Next()
// Find the inorder successor of CurrentNode in a threaded binary tree
{
	ThreadedNode<T>* temp = CurrentNode->RightChild;
	if (!CurrentNode->RightThread)
		while (!temp->LeftThread) temp = temp->LeftChild;
	CurrentNode = temp;
	if (CurrentNode == t.root) return 0; // all tree nodes have been traversed
	else return &CurrentNode->data;
}

template <class T>
void ThreadedInorderIterator<T>::Inorder()
{
	for (T* ch = Next(); ch; ch = Next())
		cout << *ch << endl;
}


enum Enum { Insert, Remove, Inorder, IteratorInorder, Search, PrintTree, Sum, InsertStudent, InorderStudent, Quit };
int main() {
	ThreadedTree<Employee> te;
	ThreadedTree<Student> ts;
	ThreadedInorderIterator ti(te);
	cout << "ThreadedTree Test\n";
	char ch;
	int select;

	Employee* data;
    Student* datas;
	cout << "\nThreadedTree Operations\n";

	while (select != 11)
	{
		cout << "1. Insert list, 2. Remove, 3.Inorder, 4.IteratorInorder, 5.Search, 6.PrintTree, 7.Sum, 8. InsertStudent, 9.InorderStudent, 10.Quit" << endl;
		// postorder traversal
		// preorder traversal
		cout << "Enter Your Choice: ";
		cin >> select;
        select -=1;
		int rnd = 0;
		//cin >> select;
		string eno, ename;
		switch (static_cast<Enum>(select))
		{
		case Insert:
			//객체 배열 초기화하여 입력
            for(int i =0; i<10; i++){
                data = new Employee(to_string(i),"name : "+to_string(i));
                te.Insert(*data);
            }

			break;
		case Remove:
			cout << "삭제 사원번호 입력:: ";
			cin >> eno;
			cout << "삽입 사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			/*
			data = new Employee(eno, nullptr);//오류가 나는 이유는 nullptr은 포인터 타입인데 string으로 변환할 수가 없기 때문임
			*/
			cout << endl;
			break;

		case Inorder:
			cout << "Recursive Inorder" << endl;
			te.Inorder();
			break;
		case IteratorInorder:
			cout << "IteratorInorder" << endl;
			ti.Inorder();
			break;
		case Search:
			cout << "검색 사원번호 입력:: ";
			cin >> eno;
			cout << "삽입 사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			if (te.Search(*data))//입력된 x에 대한 tree 노드를 찾아 삭제한다.
				cout << eno << " 값이 존재한다" << endl;
			else
				cout << "값이 없다" << endl;

			break;
		case PrintTree:
			cout << "PrintTree " << endl;
			te.PrintTree();
			break;
		case Sum:
			//iterator를 사용한 구현 : 모든 노드의 salary를 합한다
			break;
		case InsertStudent:
			//객체 배열 초기화하여 입력

            for(int i =0; i<10; i++){
                datas = new Student(to_string(i),"name : "+to_string(i));
                te.Insert(*data);
            }
			ts.Insert(*datas);
			break;
		case InorderStudent:
			//출력
            ts.PrintTree();
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
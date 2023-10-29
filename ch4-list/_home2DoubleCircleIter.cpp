//
// Created by leeyoungjun on 2023/10/29.
//
/*
* doubly linked list
6단계- 원형 객체 이중 연결 리스트의 available list, getNode, retNode
head node를 갖고 있고 삭제된 노드들은 available list에 리턴한다.
CircularDoublyList를 대상으로 한 iterator를 구현한다.
*/
#include <iostream>
#include <time.h>
using namespace std;
template<class T> class DoublyListNode;
template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;
class Employee {
	template<class T> friend class DoublyListNode;
	template<class T> friend class CircularDoublyList;
	template<class T> friend class CircularDoublyListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator>(Employee&);
	bool operator==(Employee&);
	char compare(const Employee* emp) const;
	int getSalary() const {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {
    os<<"[ eno : "<<emp.eno<<", ename : "<<emp.ename<<", salary : "<<emp.salary<<" ]";
    return os;
}
bool Employee::operator==(Employee& emp) {

    if(eno != emp.eno){
        return false;
    }
    if(ename != emp.ename){
        return false;
    }
    if(salary != emp.salary){
        return false;
    }
    return true;
}
bool Employee::operator<(Employee& emp) {
    if(eno < emp.eno){
        return true;
    } else {
        return false;
    }
}
bool Employee::operator>(Employee& emp) {
    if(eno > emp.eno){
        return true;
    } else {
        return false;
    }
}
char Employee::compare(const Employee* emp) const {

    if(this>emp){
        return '>';
    } else if (this<emp){
        return '<';
    } else {
        return '=';
    }

}
template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;
template<class T>
class DoublyListNode {
	friend class CircularDoublyList<T>;
	friend class CircularDoublyListIterator<T>;
public:
	DoublyListNode(T* p) {
		data = *p; llink = rlink = this;
	}
	DoublyListNode() {
		llink = rlink = this;
	}
private:
	T data;
	DoublyListNode<T>* llink, * rlink;
};
template<class T>
class CircularDoublyList {
	friend class CircularDoublyListIterator<T>;
public:
	CircularDoublyList() { last = new DoublyListNode<T>; }
	template<class U>
	friend ostream& operator<<(ostream&, CircularDoublyList<U>&);
	bool Delete(string);
	void Show();
	void Add(T*);//sno로 정렬되도록 구현
	bool Search(string);
	DoublyListNode<T>* GetNode();
	void RetNode(DoublyListNode<T>*);
	void Erase();
	CircularDoublyList<T>& operator+(CircularDoublyList<T>&);
private:
	DoublyListNode<T>* last;
	static DoublyListNode<T>* av;
};

template<class T>
class CircularDoublyListIterator {
public:
	CircularDoublyListIterator(const CircularDoublyList<T>& l) : list(l)
	{

	}
	~CircularDoublyListIterator();
	bool NotNull();
	bool NextNotNull();
	T* First();
	T* Next();
	T* GetCurrent();
private:
	const CircularDoublyList<T>& list;
	DoublyListNode<T>* current;
};
template<class T>
DoublyListNode<T>* CircularDoublyList<T>::GetNode()
{ //provide a node for use

}
template<class T>
void CircularDoublyList<T>::RetNode(DoublyListNode<T>* x)
{ //free the node pointed to by x

}
template<class T>
void CircularDoublyList<T>::Show() { // 전체 리스트를 순서대로 출력한다.

}
template<class T>
void CircularDoublyList<T>::Add(T* element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	DoublyListNode<T>* newNode = GetNode(); newNode->data = *element;
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;

}
template<class T>
bool CircularDoublyList<T>::Search(string eno) { // sno를 갖는 레코드를 찾기
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;

}
template<class T>
bool CircularDoublyList<T>::Delete(string eno) // delete the element
{
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;

}
template<class T>
void CircularDoublyList<T>::Erase() {

}

template<class T>
ostream& operator<<(ostream& os, CircularDoublyList<T>& l)
{

}
template<class T>
CircularDoublyList<T>& CircularDoublyList<T>::operator+(CircularDoublyList<T>& lb) {
	T* p, * q;
	CircularDoublyListIterator<T> Aiter(*this); CircularDoublyListIterator<T> Biter(lb);
	CircularDoublyList<T> lc;
	p = Aiter.First(); q = Biter.First();

}

template<class T>
bool CircularDoublyListIterator<T>::NotNull() {

}
template<class T>
bool CircularDoublyListIterator<T>::NextNotNull() {

}
template<class T>
T* CircularDoublyListIterator<T>::First() {

}
template<class T>
T* CircularDoublyListIterator<T>::Next() {

}
template<class T>
T* CircularDoublyListIterator<T>::GetCurrent() {

}
template<class T>
CircularDoublyListIterator<T>::~CircularDoublyListIterator() {
}

//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습
template<class T>
int sum(const CircularDoublyList<T>& l)
{

}
template<class T>
double avg(const CircularDoublyList<T>& l)
{

}
template<class T>
int min(const CircularDoublyList<T>& l)
{

}
template<class T>
int max(const CircularDoublyList<T>& l)
{

}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};
template<class T>
DoublyListNode<T>* CircularDoublyList<T>::av = 0;
/*
Node* CircularDoublyList::av = NULL;//static 변수의 초기화 방법을 기억해야 한다
*/
void main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularDoublyList<Employee> la, lb, lc;
	Employee* s;
	do {
		cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit 선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			cout << *data;
			la.Add(data);
			break;
		case Add1:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			cout << *data;
			lb.Add(data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "eno = " << eno << " 삭제 완료.";
			break;
		case Show:
			cout << "리스트 la = ";
			la.Show();
			cout << "리스트 lb = ";
			lb.Show();
			break;
		case Search:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "검색 값 = " << eno << " 데이터가 없습니다.";
			else
				cout << "검색 값 = " << eno << " 데이터가 존재합니다.";
			break;
		case Merge:
			lc = la + lb;
			cout << "리스트 lc = ";
			lc.Show();
			cout << "리스트 la를 삭제" << endl;
			la.Erase();
			cout << "리스트 lb를 삭제" << endl;
			lb.Erase();
			cout << "리스트 la = ";
			la.Show();
			cout << endl << "리스트 lb = ";
			lb.Show();
			break;
		case SUM:  cout << "sum() = " << sum(la) << endl; break;
		case AVG:  cout << "avg() = " << avg(la) << endl; break;
		case MIN:  cout << "min() = " << min(la) << endl; break;
		case MAX:  cout << "max() = " << max(la) << endl; break;
		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

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

    if(eno != emp.eno) { //eno만으로 같고 다름을 비교한다.
        return false;
    } else {
        return true;
    }

}
bool Employee::operator<(Employee& emp) {
    if(eno.empty()){
        return true;
    }
    if(emp.eno.empty()){
        return false;
    }

    if(stoi(eno) < stoi(emp.eno)){
        return true;
    } else {
        return false;
    }
}
bool Employee::operator>(Employee& emp) {
    if(eno.empty()){
        return false;
    }
    if(emp.eno.empty()){
        return true;
    }

    if(stoi(eno) > stoi(emp.eno)){
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

    if(av == nullptr){ // av가 지정되어있지않는 경우
        return new DoublyListNode<T>; //그냥 새로 만들어서 준다.
    } else {
        DoublyListNode<T> * getN = av;
        av = av->rlink;

        return getN;
    }

}
template<class T>
void CircularDoublyList<T>::RetNode(DoublyListNode<T>* x)
{ //free the node pointed to by x
    av->llink = x;
    x->rlink = av;
    x->llink = nullptr;
    av = x;


    //현재 av에서 왼쪽에 x를 연결해주고
    //반환받은 x노드의 오른쪽에 현재 av를 연결하고
    //x의 왼쪽을 nullptr로 초기화해주고
    //av를 이동시켜준다.

}
template<class T>
void CircularDoublyList<T>::Show() { // 전체 리스트를 순서대로 출력한다.

    DoublyListNode<T>* p = last->rlink;

    cout<<"[ ";

    while(p != last){
        cout<<p->data;
        if(p->rlink != last){
            cout<<", ";
        }
        p = p->rlink;
    }
    cout<<p->data;

    cout<<" ]";
}
template<class T>
void CircularDoublyList<T>::Add(T* element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	DoublyListNode<T>* newNode = GetNode(); newNode->data = *element;
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;

    //무조건 노드는 1개이상 있게 된다 -> 생성자의 영향
    //하지만 내부가 null일 수 있다.
    //template이므로, 어떤 형식의 객체가 올 지 모른다.

    if(first->data.eno.empty()){ //즉, nullptr인 경우에
        last = newNode;
        last->rlink = newNode;
        last->llink = newNode;
        return;

    } else if(newNode->data<first->data || newNode->data == first->data){ // 첫 시작 부분보다 작은 경우
        last->rlink = newNode;
        newNode->rlink = first;
        newNode->llink = last;
        first->llink = newNode;

        first = newNode;
        last = first->llink;
        return;
    } else {
        while(p != first){
            if(p->llink->data<newNode->data && (p->data>newNode->data || p->data==newNode->data)){ // llink < newNode <= p
                p->llink->rlink = newNode;
                newNode->llink = p->llink;
                newNode->rlink = p;
                p->llink = newNode;
                return;
            } else {
                p = p->rlink;
            }
        }
        //리스트 내부의 모든 값보다 newNode가 큰 경우
        last->rlink = newNode;
        newNode->llink = last;
        newNode->rlink = first;
        first->llink = newNode;

        last = newNode;
        return;
    }

}
template<class T>
bool CircularDoublyList<T>::Search(string eno) { // sno를 갖는 레코드를 찾기
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;

    if(first->data.eno == eno){
        return true;
    } else{
        while(p != first){
            if(p->data.eno == eno){
                return true;
            } else {
                p = p->rlink;
            }
        }
    }

    return false;

}
template<class T>
bool CircularDoublyList<T>::Delete(string eno) // delete the element
{
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;

    while(p != first){
        if(p->llink->data.eno == eno){

            p->rlink->llink = p->llink;
            p->llink->rlink = p->rlink;

            RetNode(p);
            return true;
        } else {
            p = p->rlink;
        }
    }
    return false;

}
template<class T>
void CircularDoublyList<T>::Erase() {
    //전체 노드 삭제

    DoublyListNode<T>* first = last->rlink;
    DoublyListNode<T>* p = first->rlink;

    while(p != first){
        RetNode(p->llink);
        p = p->rlink;
    }
    last = new DoublyListNode<T>();
}

template<class T>
ostream& operator<<(ostream& os, CircularDoublyList<T>& l)
{
    CircularDoublyListIterator<T> li(l);

    os<<"[ ";
    while(li.NotNull()){
        os<<li.GetCurrent();
        if(li.NextNotNull()){
            os<<", ";
        }
        li.Next();
    }
    os<<" ]";
    return os;

}
template<class T>
CircularDoublyList<T>& CircularDoublyList<T>::operator+(CircularDoublyList<T>& lb) {
	T* p, * q;
	CircularDoublyListIterator<T> Aiter(*this); CircularDoublyListIterator<T> Biter(lb);
	CircularDoublyList<T> lc;
	p = Aiter.First(); q = Biter.First();

    while(Aiter.NotNull()){
        lc.Add(p);
        p = Aiter.Next();
    }
    while(Biter.NotNull()){
        lc.Add(q);
        q = Biter.Next();
    }

    return lc;
}

template<class T>
bool CircularDoublyListIterator<T>::NotNull() {
    if(current != list.last->rlink){
        return true;
    } else {
        return false;
    }
}
template<class T>
bool CircularDoublyListIterator<T>::NextNotNull() {
    if(current->rlink != list.last->rlink){
        return true;
    } else {
        return false;
    }
}
template<class T>
T* CircularDoublyListIterator<T>::First() {
    //Employee타입의 포인터를 반환해야한다.
    return &list.last->rlink->data;

}
template<class T>
T* CircularDoublyListIterator<T>::Next() {
    current = current->rlink;
    return &current->data;
}
template<class T>
T* CircularDoublyListIterator<T>::GetCurrent() {
    return &current->data;
}
template<class T>
CircularDoublyListIterator<T>::~CircularDoublyListIterator() {
}

//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습
template<class T>
int sum(const CircularDoublyList<T>& l)
{
    CircularDoublyListIterator<T> li(l);

    int ans = 0;

    while(li.NotNull()){
        ans += li.GetCurrent()->getSalary();
        li.Next();
    }
    return ans;
}
template<class T>
double avg(const CircularDoublyList<T>& l)
{
    CircularDoublyListIterator<T> li(l);

    int ans = 0;
    int counter = 0;

    while(li.NotNull()){
        counter +=1;
        ans += li.GetCurrent()->getSalary();
        li.Next();
    }

    return ((double)ans)/counter;
}
template<class T>
int min(const CircularDoublyList<T>& l)
{
    CircularDoublyListIterator<T> li(l);

    int minPrice = li.First()->getSalary();

    while(li.NotNull()){
        if(minPrice > li.GetCurrent()->getSalary()){
            minPrice = li.GetCurrent()->getSalary();
        }
        li.Next();
    }

    return minPrice;
}
template<class T>
int max(const CircularDoublyList<T>& l)
{
    CircularDoublyListIterator<T> li(l);

    int maxPrice = li.First()->getSalary();

    while(li.NotNull()){
        if(maxPrice < li.GetCurrent()->getSalary()){
            maxPrice = li.GetCurrent()->getSalary();
        }
        li.Next();
    }

    return maxPrice;
}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};
template<class T>
DoublyListNode<T>* CircularDoublyList<T>::av = 0;
/*
Node* CircularDoublyList::av = NULL;//static 변수의 초기화 방법을 기억해야 한다
*/
int main() {
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

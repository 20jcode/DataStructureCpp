//
// Created by 이영준 on 2023-10-21.
//
/*
3단계-객체 연결 리스트의 iterator 버젼
*/
#include <iostream>
#include <time.h>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
	friend class ListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
	char compare(const Employee*)const;
	int getSalary() const {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {

    os<<"[ eno : "<<emp.eno<<" ename : "<<emp.ename<<" salary : "<<emp.salary<<" ]"<<endl;

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
    if(stoi(eno) <stoi(emp.eno)){
        return true;
    } else {
        return false;
    }
}
char Employee::compare(const Employee* emp) const { //문자열을 반환해서 대소관계를 나타낸다.
    if(this<emp){
        return '<';
    } else if(this==emp){
        return '==';
    } else{
        return '>';
    }

}
class Node {
	friend class ListIterator;
	friend class LinkedList;
	Employee data;
	Node* link;
public:
	Node() {}
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};
class ListIterator;
class LinkedList {
	friend class ListIterator;
	Node* first;
public:
	LinkedList() {
		first = nullptr;
	}
	bool Delete(string);
	void Show();
	void Add(Employee);//sno로 정렬되도록 구현
	bool Search(string);
	LinkedList& operator+(LinkedList&);
};
class ListIterator {
public:
	ListIterator(const LinkedList& lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	Employee* First();
	Employee* Next();
	Employee& operator*() const;
	Employee* operator->()const;
	ListIterator& operator++(); //Next()
	ListIterator operator ++(int);
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	Employee* GetCurrent();
private:
	Node* current; //pointer to nodes
	const LinkedList& list;//existing list
};
ListIterator::ListIterator(const LinkedList& lst) : list(lst), current(lst.first) {
	cout << "List Iterator is constructed" << endl;
}
void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first;

    while(p != nullptr){
        cout<<p->data<<endl;
        p = p->link;
    }
}
void LinkedList::Add(Employee element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = new Node(element);
    Node* p = first;

    if(first == nullptr){
        first = newNode;
        return;
    } else {
        if(newNode->data<p->data || newNode->data == p->data){
            newNode->link = p;
            first = newNode;
            return;
        } else{
            while(p->link != nullptr){
                if(newNode->data < p->link->data){
                    newNode->link = p->link;
                    p->link = newNode;
                    return;
                } else {
                    p = p->link;
                }
            }
            p->link = newNode;
        }
    }

}
bool LinkedList::Search(string eno) { // sno를 갖는 레코드를 찾기
	Node* ptr = first;

    while(ptr != nullptr){
        if(ptr->data.eno == eno){
            return true;
        } else {
            ptr = ptr->link;
        }
    }
    return false;

}
bool LinkedList::Delete(string eno) // delete the element
{
	Node* q, * current = first;
	q = current;

    while(current != nullptr){
        if(current->data.eno == eno){
            q->link = current->link;
            return true;
        } else {
            q = current;
            current = current->link;
        }
    }

    return false;

}
LinkedList& LinkedList::operator+(LinkedList& lb) { //ok
	Employee* p, * q;
	ListIterator Aiter(*this); ListIterator Biter(lb);
	LinkedList lc;
	p = Aiter.First(); q = Biter.First();

    //두가지 Iterator에서 작은 값은 lc first에서 시작된 포인터로 연결시켜주기
    //큰 값은 그대로 두면서 앞으로 진행해가는 방향

    //더하는 연산을 하는 두가지 리스트 전부 null이 아니다. (리스트를 생성하는 순간 입력데이터가 없는 경우 newNode를 진행하므로)
    //아니다. Null일 수 있다.

    //lc에 Add 메소드를 사용해서 연산을 해야할까 -> 새로운 메모리 할당으로 인한 손해 + 다시 정렬상태를 위한 연산 진행

    //lc에 그냥 Node메모리를 할당해서 first와 포인터로 연결해주어야하나?



    while(Aiter.NotNull() && Biter.NotNull()){
        if(p>q){
            lc.Add(*q);
            q  = Biter.Next();
        } else if (p == q){
            lc.Add(*p);
            lc.Add(*q);
            p = Aiter.Next();
            q = Biter.Next();
        } else { // p<q
            lc.Add(*p);
            p = Aiter.Next();
        }
    }

    if(Aiter.NotNull()){
        while(Aiter.NotNull()){
            lc.Add(*Aiter.GetCurrent());
            Aiter.Next();
        }
    } else {
        while(Biter.NotNull()){
            lc.Add(*Biter.GetCurrent());
            Biter.Next();
        }
    }

    return lc;

}

bool ListIterator::NotNull() {
    if(current != nullptr){
        return true;
    } else {
        return false;
    }
}
bool ListIterator::NextNotNull() {
    if(current->link != nullptr){
        return true;
    } else {
        return false;
    }
}
Employee* ListIterator::First() {
	return &list.first->data;
}
Employee* ListIterator::Next() {
	current = current->link;
	Employee* e = &current->data;
	return e;
}

Employee* ListIterator::GetCurrent() {
	return &current->data;
}

ListIterator::~ListIterator() {
}

Employee& ListIterator::operator*() const {
	return current->data;
}

Employee* ListIterator::operator->()const {
	return &current->data;
}

ListIterator& ListIterator::operator++() {
	current = current->link;
	return *this;
}

ListIterator ListIterator::operator ++(int) {
	ListIterator old = *this;
	current = current->link;
	return old;
}

bool ListIterator::operator != (const ListIterator right) const {
	return current != right.current;
}

bool ListIterator::operator == (const ListIterator right) const {
	return current == right.current;
}
//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습

int printAll(const LinkedList& l){
    ListIterator li(l);

    while(li.NotNull()){
        cout<<li.GetCurrent()<<endl;
        li.Next();
    }

    return 0;
}

//각 salary에 15를 곱한다음 전부 더해서 반환
int sumProductFifthElement(const LinkedList& l){
    ListIterator li(l);
    int ans = 0;

    while(li.NotNull()){
        ans += li->getSalary()*15;
        li.Next();
    }

    return ans;
}

int sum(const LinkedList& l)//올바른지 코드 점검이 필요함
{
	ListIterator li(l);

    int ans = 0;

    while(li.NotNull()){
        ans = ans + li->getSalary();
        li.Next();
    }

    return ans;

}

double avg(const LinkedList& l)//올바른지 코드 점검이 필요함
{
	ListIterator li(l);

    int ans = 0;
    int counter = 0;

    while(li.NotNull()){
        ans += li->getSalary();
        counter++;
        li.Next();
    }

    return ((double)ans)/counter;

}

int min(const LinkedList& l)//올바른지 코드 점검이 필요함
{
	ListIterator li(l);

    int ans = li->getSalary();

    while(li.NotNull()){
        if(ans>li->getSalary()){
            ans = li->getSalary();
        }
        li.Next();
    }

    return ans;

}

int max(const LinkedList& l)//올바른지 코드 점검이 필요함
{
	ListIterator li(l);

    int ans = li->getSalary();

    while(li.NotNull()){
        if(ans<li->getSalary()){
            ans = li->getSalary();
        }
        li.Next();
    }
    return ans;
}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

int main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	LinkedList la, lb, lc;
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
			la.Add(*data);
			break;
		case Add1:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			lb.Add(*data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "삭제 완료";
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
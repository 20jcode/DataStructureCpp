//
// Created by 이영준 on 2023-10-15.
// 가용공간리스트

#include <iostream>
#include <time.h>
using namespace std;

class Employee {
	friend class Node;
	friend class CircularList;
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
	int getSalary() const {
		return salary;
	}
};

ostream& operator<<(ostream& os, Employee& em){
    os<<"[ no : "<<em.eno<<" name : "<<em.ename<<" salary : "<<em.salary<<" ]";

    return os;
}

bool Employee::operator<(Employee& em){
    if(salary<em.salary){
        return true;
    } else {
        return false;
    }
}

bool Employee::operator==(Employee & em) {

    if(eno != em.eno){
        return false;
    }
    if(ename != em.ename){
        return false;
    }
    if(salary != em.salary){
        return false;
    }
    return true;
}

class Node {
	friend class ListIterator;
	friend class CircularList;
	Employee data;
	Node* link;
public:
	Node() { }
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class CircularList {
	friend class ListIterator;
	Node* last;
    //사용할 수 있는 노드를 가리키고 있는 포인터
	static Node* av;
public:
	CircularList() {
		last = new Node();
        last->link = last;
	}
	bool Delete(string);
	void Show();
	void Add(Employee*);
	bool Search(string);
	Node* GetNode();
	void RetNode(Node*);
	friend ostream& operator<<(ostream& os, CircularList& l);
};
class ListIterator {
public:
	ListIterator(const CircularList& lst);
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
	const CircularList& list;//existing list
};

//return av
Node* CircularList::GetNode(){
    if(av== nullptr){ //가용 리스트가 비어있을 경우
        av = new Node(); //새 노드를 만들고
        av->link = last->link; //만들어진 새 노드는 첫번째를 가리키게 하고
        last->link = av; //마지막 노드는 새 노드를 가리키게 한다.
        return av;
    } else{ //av가 nullptr이 아닌 경우 - 즉, GetNode로 사용되었다고 생각하자.

        Node* buf = av;
        av = av->link;
        return buf;
    }
}

//현재 노드를 사용가능하게 변경
void CircularList::RetNode(Node* x){
    /*
     * 0번, 1번 노드가 사용중이고 2번 노드가 사용가능 노드일 경우
     * 1번 노드를 반환한다고 할 때
     * 현재 av 는 2번 노드에 위치해있다.
     *
     * 1번 노드의 link를 av에 연결하고 (이때 av는 0번노드를 가리키고 있다)
     * 2번 노드(av)를 1번 노드가 되도록 한다
     *
     * 그럼 그냥 노드를 새로 만들고 제거하고 하는 것 아닌가?
     */
    x->link = av;
    av = x;

}
ostream& operator<<(ostream& os, CircularList& l)
{
	ListIterator li(l);

    if(li.NotNull()){
        os<<li.GetCurrent()<<endl;
    } else {
        os<<"NULL입니다"<<endl;
    }

    return os;

}
void CircularList::Show() {
	Node* first = last->link;
	Node* p = first->link;
    cout<<endl;
    cout<<"[ ";
    while(p->link != first){ //원형을 순환해서 처음이 될 때까지 반복한다.
        cout<<p->data;
        p = p->link;
    }
    cout<<" ]"<<endl;
}

//새로운 노드를 더한다.
void CircularList::Add(Employee* element)
{
	Node* newNode = GetNode();
    newNode->data = *element;
	Node* first = last->link; //처음 노드
	Node* p = first->link; //처음의 다음 노드
	Node* q = first; //처음 노드



}
bool CircularList::Search(string eno) {
	Node* first = last->link;
	Node* p = first->link;

    while(p->link != first){
        if(p->data.eno == eno){
            return true;
        }
    }

    return false;

}
//삭제 성공 시 true 반환
bool CircularList::Delete(string eno) // delete the element
{
	Node* first = last->link;
	Node* p = first->link;
	Node* q = first;
    if(q->data.eno != eno){ //처음이 아닐 때
       while(p->link != first){
           if(p->data.eno == eno){ //삭제할 em을 찾았다면
               q->link = p->link; //이전의 q가 지금의 다음을 가리키도록 하여서 제거
           }
       }
       //리스트 전체에서 찾지 못한 경우
       return false;
    } else { //first의 값이 삭제하고자 하는 것일 경우
        last->link = p;
        return true;
    }


}

ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.last->link->link) {
}
bool ListIterator::NotNull() {
	if (current != list.last->link)
		return true;
	else
		return false;
}
bool ListIterator::NextNotNull() {
	if (current->link != list.last->link)
		return true;
	else
		return false;
}
Employee* ListIterator::First() {
	return &list.last->link->link->data;
}
Employee* ListIterator::Next() { //TODO : 완성시켜야함...?
	Employee* e = &current->data;
	current = current->link;
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
//int printAll(const List& l);
//int sumProductFifthElement(const List& l);
int sum(const CircularList& l)
{
	ListIterator li(l);

    int ans = 0;

    if(li.NotNull()){
        while(li.NextNotNull()){
            ans += li->getSalary();
        }
    }
    return ans;
}

double avg(const CircularList& l)
{
	ListIterator li(l);

    if(li.NotNull()){
        int sumAll = sum(l);
        int counter = 0;
        counter++; //1개 존재하는 경우
        while(li.NextNotNull()){
            counter++;
        }

        return (double)sumAll/counter;
    } else {
        return 0;
    }

}

int min(const CircularList& l)
{
	ListIterator li(l);

    int ans = 0;

    while(li.NextNotNull()){
        if(ans<li->getSalary()){
            ans = li->getSalary();
        }
    }

    return ans;
}

int max(const CircularList& l)
{
	ListIterator li(l);

    int ans = 0;

    while(li.NextNotNull()){
        if(ans>li->getSalary()){
            ans = li->getSalary();
        }
    }

    return ans;

}

enum Enum {
	Add, Delete, Show, Search, SUM, AVG, MIN, MAX, Exit
};

Node* CircularList::av = NULL;



int main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	srand(time(NULL));
	CircularList* l = new CircularList();
	Employee* s;
	do {
		cout << endl << "0.ADD, 1.Delete, 2.Show, 3.Search, 4. sum, 5.avg, 6.min, 7.max, 8.exit ����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add:
			cout << "eno을 입력하시오: ";
			cin >> eno;
			cout << "ename을 입력하시오: ";
			cin >> ename;
			cout << "월급을 입력하시오 ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			l->Add(data);
			break;
		case Delete:
			cout << "삭제할 eno을 입력하시오: ";
			cin >> eno;
			result = l->Delete(eno);
			if (result)
				cout << "eno = " << eno << " 삭제되었습니다.";
			break;
		case Show:
			l->Show();
			break;
		case Search:
			cout << "검색할 eno를 입력하세요 ";
			cin >> eno;
			result = l->Search(eno);
			if (!result)
				cout << "검색실패 = " << eno << " 입니다.";
			else
				cout << "검색성공 = " << eno << " 입니다.";
			break;
		case SUM:  cout << "sum() = " << sum(*l) << endl; break;
		case AVG:  cout << "avg() = " << avg(*l) << endl; break;
		case MIN:  cout << "min() = " << min(*l) << endl; break;
		case MAX:  cout << "max() = " << max(*l) << endl; break;
		case Exit:
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

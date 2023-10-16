//
// Created by 이영준 on 2023-10-15.
//

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
    os<<"no : "<<em.eno<<" name : "<<em.ename<<" salary : "<<em.salary<<endl;

    return os;
}

bool Employee::operator<(Employee& em){
    if(this->salary<em.salary){
        return true;
    } else {
        return false;
    }
}

bool Employee::operator==(Employee & em) {
    if(this->eno != em.eno){
        return false;
    }
    if(this->ename != em.ename){
        return false;
    }
    if(this->salary != em.salary){
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

Node* CircularList::GetNode(){

}

void CircularList::RetNode(Node* x){

}
ostream& operator<<(ostream& os, CircularList& l)
{
	ListIterator li(l);

}
void CircularList::Show() {
	Node* first = last->link;
	Node* p = first->link;

}
void CircularList::Add(Employee* element)
{
	Node* newNode = GetNode(); newNode->data = *element;
	Node* first = last->link;
	Node* p = first->link;
	Node* q = first;



}
bool CircularList::Search(string eno) {
	Node* first = last->link;
	Node* p = first->link;

}
bool CircularList::Delete(string eno) // delete the element
{
	Node* first = last->link;
	Node* p = first->link;
	Node* q = first;

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
Employee* ListIterator::Next() {
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


}

double avg(const CircularList& l)
{
	ListIterator li(l);

}

int min(const CircularList& l)
{
	ListIterator li(l);

}

int max(const CircularList& l)
{
	ListIterator li(l);

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
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			l->Add(data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = l->Delete(eno);
			if (result)
				cout << "eno = " << eno << " ���� �Ϸ�.";
			break;
		case Show:
			l->Show();
			break;
		case Search:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = l->Search(eno);
			if (!result)
				cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�.";
			else
				cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�.";
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

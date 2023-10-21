//
// Created by 이영준 on 2023-10-17.
//
/*
2단계- 객체 연결 리스트: 단순한 linked list에서 insert는 올림차순으로 정렬되도록 처리, delete하는 알고리즘을 코딩
*/
#include <iostream>
#include <time.h>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
	string eno;
	string ename;
public:
	Employee() {}
	Employee(string sno, string sname) :eno(sno), ename(sname) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
};
ostream& operator<<(ostream& os, Employee& emp) {
    os<<"[ 사원 번호 : "<<emp.eno<<", 사원 이름 : "<<emp.ename<<" ]"<<endl;
    return os;
}
bool Employee::operator==(Employee& emp) {
    if(eno != emp.eno) {
        return false;
    }
    if(ename != emp.ename) {
        return false;
    }
    return true;
}
bool Employee::operator<(Employee& emp) {
    if(eno < emp.eno) {
        return true;
    }
    return false;
}
class Node {
	friend class LinkedList;
	Employee data;
	Node* link;
public:
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class LinkedList {
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

void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first;

    while(p != nullptr) {
        cout << p->data;
        /*
        if (p->link != nullptr) {
            cout << ", ";
        }
         */
        p = p->link;
    }

}
void LinkedList::Add(Employee element){ // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다

	Node* newNode = new Node(element);

    Node* p = first;

    if(p == nullptr) {
        first = newNode;
        return;
    } else {
        if(newNode->data < p->data || newNode->data == p->data) {
            newNode->link = p;
            first = newNode;
            return;
        } else {
            while(p->link != nullptr) {
                if(newNode->data <p->link->data) {
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
        }
        ptr = ptr->link;
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
        }
        q = current;
        current = current->link;
    }
    return false;

}
LinkedList& LinkedList::operator+(LinkedList& lb) {
	LinkedList lc;
	Node* a = first, * b = lb.first;

    while(a->link != nullptr && b->link != nullptr){
        if(a->data < b->data){
            lc.Add(a->data);
            a = a->link;
        } else if(a->data == b->data){
            lc.Add(a->data);
            lc.Add(a->data);
            a = a->link;
            b = b->link;
        } else {
            lc.Add(b->data);
            b = b->link;
        }
    }

    if(a->link == nullptr){
        while(b->link != nullptr){
            lc.Add(b->data);
            b = b->link;
        }
    } else {
        while(a->link != nullptr){
            lc.Add(a->data);
            a = a->link;
        }
    }


}
enum Enum {
	Add1, Add2, Delete, Show, Search, Merge, Exit
};

int main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	bool result = false;
	LinkedList la, lb, lc;
	Employee* data;
	do {
		cout << "0.ADD0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit 선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			la.Add(*data);
			break;
		case Add2:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
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

		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

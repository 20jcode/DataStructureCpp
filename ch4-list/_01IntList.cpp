//
// Created by leeyoungjun on 2023/10/16.
//

//완성

#include <iostream>
#include <time.h>
using namespace std;

class Node {
	friend class LinkedList;
	int data;
	Node* link;
public:
	Node(int element) {
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
	bool Delete(int);
	void Show();
	void Add(int element);
	bool Search(int data);
	LinkedList& operator+(LinkedList&);
};

// $전체 리스트를 순서대로 출력
void LinkedList::Show() { //리스트 내부의 전체 목록을 보여준다.
	Node* p = first;

    if(p == nullptr){ //내부에 아무것도 없는 경우
        cout<<"비었습니다"<<endl;
    } else {
        cout<<"[ ";
        while(p != nullptr){ //다음 노드가 없을때까지 반복한다.
            cout<<p->data;
            if(p->link != nullptr){
                cout<<", ";
            }
            p = p->link;
        }
        cout<<" ]";
	    cout << endl;
    }
}
void LinkedList::Add(int element)
{
	Node* newNode = new Node(element);
    Node* p = first;

    if(p == nullptr){
        first = newNode;
    } else if(newNode->data<p->data){ //원소가 1개이면서 newNode가 더 작을때
        newNode->link = first;
        first = newNode;
    } else{
        while(p->link != nullptr){
            if(newNode->data<=p->data){ // newNode <= p <= p->link
                newNode->link = p;
                if(p == first){
                    first = newNode;
                }
                return;
            } else if(newNode->data<=p->link->data){ // p < newNode <= p->link
                newNode->link = p->link;
                p->link = newNode;
                return;

            } else { // p <= p->link < newNode
                p = p->link;
            }
        }
        p->link = newNode;


    }


}
//발견하면 true 반환
bool LinkedList::Search(int data) {
	Node* ptr = first;

    if(ptr == nullptr){
        return false;
    }
    while(ptr->data != data){
        ptr = ptr->link;
        if(ptr->link==nullptr){
            return false;
        }
    }
	return true;
}
//삭제에 성공하면 true를 반환
bool LinkedList::Delete(int element) // delete the element
{
	Node* q, * current = first;

    if (first->data == element){ //처음이 element인 경우, 삭제
        first = first->link;
        return true;
    }

    while(current->data != element){ // current가 element가 나올때까지 반복
        q = current;
        current = current->link;
        if(current == nullptr){
            return false;
        }
    }

    if(current->link == nullptr){ //삭제하려는 원소가 마지막인경우
        q->link = nullptr;
    } else { //마지막이 아닌 경우
        q->link = current->link;
    }

    return true;

}
LinkedList& LinkedList::operator+(LinkedList& lb) {
	LinkedList lc;
	Node* a = first, * b = lb.first;

    lc.first = a;

    while(a->link != nullptr){
        a=a->link;
    }
    a->link = b; //a의 마지막에 b의 노드를 이어주고


	return lc;
}
enum Enum {
	Add1, Add2, Delete, Show, Search, Merge, Exit
};
int main() {
	Enum menu;
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;
	int data = 0;
	do {
		cout << "0.ADD0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit º±≈√::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			data = rand() % 49;
            cout <<"추가값 : "<<data<<endl;
			la.Add(data);
			break;
		case Add2:
			data = rand() % 49;
			lb.Add(data);
			break;
		case Delete:
			cin >> data;
			result = la.Delete(data);
			if (result)
				cout << "삭제성공"<<endl;
			break;
		case Show:
			la.Show();
            lb.Show();
			break;
		case Search:
			int n; cin >> n;
			result = la.Search(n);
			if (!result)
				cout << "찾기 실패 = " << n << " 입니다.";
			else
				cout << "찾기 성공 = " << n << " 입니다.";
			break;
		case Merge:
			lc = la + lb;
            lc.Show();
			break;
		case Exit:
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


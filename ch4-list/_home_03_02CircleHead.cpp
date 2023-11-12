//
// Created by leeyoungjun on 2023/11/10.


/*다항식 리스트: Polynomial Linked List
//지수는 정수 0<= 지수 <= 5, 난수로 생성한다
//계수는 double로 난수 생성한다.  -9.0 < 계수 < 9.0
- 지수 내림 차순으로 정렬한다.
- c = a.Add(b) 구현한다.
- singly linked list, circular linked list, circular linked list with head node
*/
#include <iostream>
#include<string>
#include <assert.h>
using namespace std;

template<class T> class Term {
public:
	//All members of Term are public by default
	T coef; //coefficient
	int exp; //exponent
	Term() { coef = 0; exp = 0; }
	Term(T c, T e) :coef(c), exp(e) { }
	Term Set(int c, int e) { coef = c; exp = e; return *this; };
};

template<class T> class Chain; //forward declaration
template<class T> class ChainIterator;

template<class T>
class ChainNode {
	friend class Chain<T>;
	friend class ChainIterator<T>;
public:
	ChainNode() { }
	ChainNode(const T&);
private:
	T data;
	ChainNode<T>* link;
};

template<class T> class Chain {
public:
	Chain() { last = 0; };
	void Delete(void); //delete the first element after first
	int Length();
	void Add(const T& element); //add a new node after first
	void Invert();
	void Concatenate(Chain<T> b);
	void InsertBack(const T& element);
	void displayAll();

	ChainIterator<T> begin() const { return ChainIterator<T>(head->link); }
	ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }
private:
	ChainNode<T>* last; //last로 수정
    ChainNode<T>* head; //head노드 추가
};

template<class T> class ChainIterator {
private:
	const Chain<T>* list; //refers to an existing list
	ChainNode<T>* current; //points to a node in list
public:
	ChainIterator<T>(const Chain<T> &l) :Chain<T>(l), current(l.first) { }; //Chain에 대해서 Iterator를 생성
	ChainIterator() { }
	ChainIterator(ChainNode<T>* node) :current(node) { }
	//dereferencing operators
	T& operator *() const { return current->data; }
	T* operator->()const { return &current->data; }
	bool operator && (ChainIterator<T> iter)const {
		return current != NULL && iter.current != NULL;
	}
	bool isEmpty() const { return current == NULL; }
	//increment
	ChainIterator& operator ++(); //preincrement, Iterator를 현재 연산 이후 다음으로 이동한다.
	ChainIterator<T> operator ++(int); //post increment, Iterator를 다음으로 이동하고 현재 연산을 진행한다.
	bool NotNull(); //check the current element in list is non-null
	bool NextNotNull(); //check the next element in list is non-null
	T* First( ) { //return a pointer to the first element of list
		if (list->first) return &list->first->data;
		else return 0;
	}
	T* Next();//return a pointer to the next element of list
};

/*
class Polynomial
*/
template<class T> class Polynomial {
public:
	Polynomial() { }
	Polynomial(Chain<Term<T> >* terms) :poly(terms) { }
	Polynomial<T> operator+(const Polynomial<T>& b) const;
	void add(T coef, T exponent);
	void addAll(Polynomial<T>* poly);
	void display();

	T Evaluate(T&) const;//f(x)에 대하여 x에 대한 값을 구한다
	Polynomial<T> Multiply(Polynomial<T>&); //f(x) * g(x)
	Polynomial(const Polynomial& p); //copy constructor
	friend istream& operator>>(istream&, Polynomial&);//polynomial 입력
	friend ostream& operator<<(ostream&, Polynomial&);//polynomial 출력
	//const Polynomial& operator=(const Polynomial&) const;
	//~Polynomial( );
	//Polynomial operator-(const Polynomial&)const;

private:
	Chain<Term<T> > poly;
};

template <typename valType>
inline ostream& operator<< (ostream& os, const Term<valType>& term) {
    os<<"[ coef : "<<term.coef<<", exp : "<<term.exp<<" ]";
    return os;
}

template <class T>
ChainNode<T>::ChainNode(const T& element) {
    data = element;
    link = nullptr;
}

template <class T>
void Chain<T>::Delete(void) //delete the first element after first
{
    if(last != head && last->link == head){
        //노드 내부에 head노드와 1개의 실제 노드가 들어있는 경우
        head->link = head;
        last = head;

    } else {
        //실제 노드가 2개 이상인 경우 : head -> 노드 1 -> 노드 2(last) -> head
        head->link = head->link->link;
    }

}

template <class T>
void Chain<T>::Add(const T& element) //add a new node after first
{
    ChainNode<T>* newNode = new ChainNode<T>(element);
    ChainNode<T>* p = head;

    if(last == head){ //헤드노드만 존재하는 경우
        head->link = newNode;
        newNode->link = head;
        last = newNode;
    } else { //노드가 1개 이상이고, 중간에 존재하는 경우
        while(p->link != head){ //다음 노드가 head가 아닌 경우에만
            if(newNode->data.exp > p->link->data.exp){ // newNode > p->link
                newNode->link = p->link;
                p->link = newNode;
                return;
            } else if (newNode->data.exp == p->link->data.exp){
                p->link->data.coef += newNode->data.coef; // 지수가 같으므로 더해준다.
                return;
            } else {
                p = p->link;
            }
        } // p == last 이지만, newNode가 더 작은 지수를 가지고 있는 경우

        newNode->link = head;
        p->link = newNode;
        last = newNode;
    }
}

template <class T>
void Chain<T>::Invert() { //다항식을 뒤집지만, 헤드노드는 유지되어야한다.

    //TODO : 정상작동하는가?
    if(head->link == head){ //빈노드이면 할 필요가 없음.
        return;
    }

	ChainNode<T>* p = head->link, * q = head; //q trails p
	last = p;

    while (p != head) {
		ChainNode<T>* r = q; q = p; //r trails q
		p = p->link; //p moves to next node
		q->link = r; //link q to preceding node
	}

}

template <class T>
void Chain<T>::Concatenate(Chain<T> b) { //연결시키는 것.

	//현재 체인이 없을 경우 b를 가지고 끝낸다.

    if(head->link == head){
        head->link = b.head->link;
        last = b.last;
        return;
    } else {
        ChainNode<T>* p = b.head->link;

        if(p->link!= b.head){ //b를 순환하며 Add메서드를 실행한다.
            Add(p->data);
            p = p->link;
        }
    }
}

template <class T>
void Chain<T>::InsertBack(const T& element) { //노드의 제일 마지막에 특정 노드를 추가한다.
    //정렬이 되지 않게 됨. 참고

	ChainNode<T>* newNode = new ChainNode<T>(element);
	if(head->link == head){
        head->link = newNode;
        newNode->link = head;
        last = newNode;
        return;
    } else {
        newNode->link = head;
        last->link = newNode;
        last = newNode;
        return;
    }
}

template <class T>
void Chain<T>::displayAll() {

    ChainNode<T>* p = head->link;

    cout<<"[ ";

    while(p != head){
        cout<<p->data;
        if(p->link != head){
            cout<<", ";
        }
        p = p->link;
    }

    cout<<" ]"<<endl;
}

template <class T>
ChainIterator<T>& ChainIterator<T>::operator ++() //preincrement
{
    //next하고 반환한다.

    current = current->link;
    return current;
}

template <class T>
ChainIterator<T> ChainIterator<T>::operator ++(int) //post increment
{
    //current를 반환하고, next한다.
    ChainNode<T> temp(*this); //현재 상태를 복사해서 생성
    current = current->link;
    return temp;
}

template <class T>
bool ChainIterator<T>::NotNull() { //check the current element in list is non-null
    if(current != nullptr){ //data가 0이 아닌경우 null이 아니므로.
        return true;
    } else {
        return false;
    }
}

template <class T>
bool ChainIterator<T>::NextNotNull() { //check the next element in list is non-null

    if(current != nullptr){
        return true;
    } else {
        return false;
    }
}

template <class T>
T* ChainIterator<T>::Next() {//return a pointer to the next element of list
    current = current->link;
    return &current->data;
}

template<class T>
void Polynomial<T>::add(T coef, T exponent) {
	Term<T>* newTerm = new Term<T>(coef, exponent);
	this->poly.Add(*newTerm);
}

template<class T> void Polynomial<T>::addAll(Polynomial<T>* b) {
	ChainIterator<Term<T>> iterB = b->poly.begin();

	while (iterB.NotNull()) {
		Term<T> dataB = *iterB;
		add(dataB.coef, dataB.exp);
		iterB.Next();
	}
}

template<class T>
T Polynomial<T>::Evaluate(T &e) const {
    ChainIterator<Term<T>> li = poly.begin();
    T ans;

    while(li.NotNull()){
        ans += li.coef*pow(e,li.exp);
        li.Next();
    }

    return ans;
}
template<class T>
Polynomial<T> Polynomial<T>::Multiply(Polynomial<T> & b) {
    Term<T> temp;
	ChainIterator<Term<T>> ai = poly.begin(), bi = b.poly.begin();
	Polynomial<T> c;

    while(ai.NotNull()){
        while(bi.NotNull()){
            c.add(ai.coef*bi.coef,ai.exp*bi.exp);
            bi.Next();
        }
        ai.Next();
    }

    return c;
}

template<class T> void Polynomial<T>::display() {
	poly.displayAll();
	cout << endl;
}

template<class T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& b) const {
	Term<T> temp;
	ChainIterator<Term<T>> ai = poly.begin(), bi = b.poly.begin();
	Polynomial<T> c;

    while(ai.NotNull()){
        c.add(ai->coef,ai->exp);
        ai.Next();
    }
    while(bi.NotNull()){
        c.add(bi->coef,bi->exp);
        bi.Next();
    }
    return c;

}

template <class T>
Polynomial<T>::Polynomial(const Polynomial<T> &p){
    ChainIterator<Term<T>> li = p.poly.begin();

    while(li.NotNull()){
        add(li->coef,li->exp);
        li.Next();
    }

}

template <typename U>
istream& operator>>(istream& os,const Polynomial<U>& p){
    os>>p;
    return os;
}

template <typename U>
ostream& operator<<(ostream& os, Polynomial<U>& p){
    os<<p.poly<<endl;
    return os;
}




int main(void) {

    //계수부분은 double 형식으로
	Polynomial<double> a, b, sum;

	char select;
	Term<double>* tempTerm;
	ChainNode<Term<double>> cn;
	Chain<Term<double>> ca, cb;
	ChainIterator<Term<double>> iter;
	double c;
    int e; //지수는 그대로 int형식

    //난수 생성
    srand(0); //시드 0으로 초기화


	cout << endl << "명령 선택: a: Add_a, b: Add_b, p: a + b, d: DisplayAll, q: exit" << endl;
	cin >> select;
	while (select != 'q')
	{
		switch (select)
		{
		case 'a':

			cout<<"auto input c,e data"<<endl;
            c = (rand()/static_cast<double>(RAND_MAX)*2-1)*9; //-9~9까지 double형 변수 생성
            e = rand()%6; //0~5 사이의 난수 생성

            cout<<"c : "<<c<<", e : "<<e<<endl;

			a.add(c, e);//지수를 임의 숫자로 입력하여도 지수 내림 차순으로 정렬

            a.display();

            break;
		case 'b':

			cout<<"auto input c,e data"<<endl;
            c = (rand()/static_cast<double>(RAND_MAX)*2-1)*9; //-9~9까지 double형 변수 생성
            e = rand()%6; //0~5 사이의 난수 생성

            cout<<"c : "<<c<<", e : "<<e<<endl;

			b.add(c, e);//지수를 임의 숫자로 입력하여도 지수 내림 차순으로 정렬
            b.display();



			break;
		case 'p': //a+b
			cout << "a+b: ";
			//a.addAll(&b);
			a.display();
			b.display();
			sum = a + b;
			sum.display();
			//cout << sum;
			break;
		case 'd':
			cout << "display all: " << endl;
			a.display();
			b.display();
			break;
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
		}
		cout << endl << "Select command: a: Add_a, b: Add_b, p: Plus, d: DisplayAll, q: exit" << endl;
		cin >> select;
	}
	system("pause");
	return 0;
}

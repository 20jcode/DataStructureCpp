//
// Created by leeyoungjun on 2023/11/10.
//

//싱글 링크드 리스트 버전.

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
	T data; //사용시에는 Term타입을 가리키는 포인터를 사용하게됨.
	ChainNode<T>* link;
};

template<class T> class Chain {
public:
	Chain() { first = 0; };
	void Delete(void); //delete the first element after first
	int Length();
	void Add(const T& element); //add a new node after first
	void Invert();
	void Concatenate(Chain<T> b);
	void InsertBack(const T& element);
	void displayAll();

	ChainIterator<T> begin() const { return ChainIterator<T>(first); }
	ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }
private:
	ChainNode<T>* first;
};

template<class T> class ChainIterator {
private:

	ChainNode<T>* current; //points to a node in list
public:
	//ChainIterator<T>(const Chain<T> &l) :Chain(l), current(l.first) { };
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
	ChainIterator& operator ++(); //preincrement
	ChainIterator<T> operator ++(int); //post increment
	bool NotNull(); //check the current element in list is non-null
	bool NextNotNull(); //check the next element in list is non-null
	//T* First( ) { //return a pointer to the first element of list
	//	if (list->first) return &list->first->data;
	//	else return 0;
	//}
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
    /*
	T Evaluate(T&) const;//f(x)에 대하여 x에 대한 값을 구한다
	Polynomial<T> Multiply(Polynomial<T>&); //f(x) * g(x)
	Polynomial(const Polynomial& p); //copy constructor
	friend istream& operator>>(istream&, Polynomial&);//polynomial 입력
	friend ostream& operator<<(ostream&, Polynomial&);//polynomial 출력
	const Polynomial& operator=(const Polynomial&) const;
	~Polynomial( );
	Polynomial operator-(const Polynomial&)const;

    */
private:
	Chain<Term<T> > poly;
};

template <typename valType>
inline ostream& operator<< (ostream& os, const Term<valType>& term) {
    os<<"[ coef : "<<term.coef<<", exp : "<<term.exp<<" ]";
    return os;
}

template <class T>
ChainNode<T>::ChainNode(const T& element) {//ChainNode 생성자?
    data = element;
    link = nullptr;
}

template <class T>
void Chain<T>::Delete(void) //delete the first element after first
{
    //처음의 다음 항을 지운다?
    first->link = first->link->link;
}

template <class T>
void Chain<T>::Add(const T& element) //add a new node after first
{   //TODO : 지수가 같은 경우 서로 계수를 더해줄 수 있어야한다.
    //TODO : 가끔 무한루프로 링크가 연결되는 경우가 있다.

    ChainNode<T>* newNode =new ChainNode<T>(element);

    //first가 NULL인 경우
    if(first == nullptr){
        first = newNode;
        return;
    }

    ChainNode<T>* p = first;

    //지수를 비교해서 지수순으로 정렬한다.

    //만약 first보다 newNode의 지수가 큰 경우
    if(newNode->data.exp>first->data.exp){
        newNode->link = first;
        first = newNode;
    } else if(newNode->data.exp == first->data.exp){ //first와 newNode 의 exp가 동일한경우
        first->data.coef += newNode->data.coef;
        return;
    } else {
       while(p->link != nullptr){//p의 다음 링크가 null이 아닐때까지 돈다.
           if(p->data.exp>newNode->data.exp && newNode->data.exp > p->link->data.exp){
               // 이전 노드의 p > newNode > p->link
               // 제일 마지막 노드보다 작은 경우, while문을 탈출하고 삽입하게 된다.
               // if문 조건이 성립하는 경우에는

               newNode->link = p->link;
               p->link = newNode;
               return;
           } else if(p->link->data.exp == newNode->data.exp){
               // p->link == newNode
               // 제일 마지막 exp와 같은 경우를 처리해주기위해
               p->link->data.coef += newNode->data.coef;
               return;

           } else {
               p = p->link;

           }
       }
       //newNode가 제일 작은 경우
       p->link = newNode;
       //newNode->link는 nullptr이므로 변경할 필요가 없다.
    }
}

template <class T>
void Chain<T>::Invert() {
	ChainNode<T>* p = first, * q = 0; //q trails p
	while (p) {
		ChainNode<T>* r = q; q = p; //r trails q
		p = p->link; //p moves to next node
		q->link = r; //link q to preceding node
	}
	first = q;
}

template <class T>
void Chain<T>::Concatenate(Chain<T> b) {
	if (!first) { first = b.first; return; }
	if (b.first) {
		for (ChainNode<T>* p = first; p->link; p = p->link) {
			p->link = b.first;
		}
	}
}

template <class T>
void Chain<T>::InsertBack(const T& element) {
	ChainNode<T>* newnode = new ChainNode<T>(element);
	if (!first) //insert into empty list
	{
		first = newnode;
		return;
	}
	ChainNode<T>* curr = first;
	while (curr->link != NULL) {
		curr = curr->link;
	}
	curr->link = newnode;
}

template <class T>
void Chain<T>::displayAll() {

    ChainNode<T>* p = first;
    cout<<"[ ";
    while(p != nullptr){
        cout<<p->data;
        if(p->link != nullptr){
            cout<<", ";
        }
        p = p->link;
    }
    cout<<" ]";
}

template <class T>
ChainIterator<T>& ChainIterator<T>::operator ++() //preincrement
{

}

template <class T>
ChainIterator<T> ChainIterator<T>::operator ++(int) //post increment
{

}

template <class T>
bool ChainIterator<T>::NotNull() { //check the current element in list is non-null
    if(current != nullptr){
        return true;
    } else {
        return false;
    }
}

template <class T>
bool ChainIterator<T>::NextNotNull() { //check the next element in list is non-null
    if(current->link != nullptr){
        return true;
    } else {
        return true;
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

template<class T> void Polynomial<T>::display() {
	poly.displayAll();
	cout << endl;
}

template<class T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& b) const {
	Term<T> temp;
	ChainIterator<Term<T>> ai = poly.begin(), bi = b.poly.begin();
	Polynomial<T> c;

    //단순하게 a와 b 전부 순환하면서 더하는 작업을 진행하도록 한다.?
    //c.addAll(b);//TODO : 이게 왜 안되는 것일까?


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


int main(void) {

	Polynomial<int> a, b, sum;

	char select;
	Term<int>* tempTerm;
	ChainNode<Term<int>> cn;
	Chain<Term<int>> ca, cb;
	ChainIterator<Term<int>> iter;
	int c;
    int e;

    //난수생성부분
    //지수는 정수 0<= 지수 <= 5, 난수로 생성한다
    //계수는 double로 난수 생성한다.  -9.0 < 계수 < 9.0
    srand(0);



	cout << endl << "명령 선택: a: Add_a, b: Add_b, p: a + b, d: DisplayAll, q: exit" << endl;
	cin >> select;
	while (select != 'q')
	{
		switch (select)
		{
		case 'a':
			cout<<"자동으로 난수를 생성해서 입력합니다"<<endl;
            //c = (rand()/static_cast<double>(RAND_MAX)*2-1)*9; //-9~9까지 double형 변수 생성
            c = rand()%19-9;
            e = rand()%6; // 0~5 사이의 난수 생성
            cout<<"c, e : [ "<<c<<", "<<e<<" ]"<<endl;
			a.add(c, e);//지수를 임의 숫자로 입력하여도 지수 내림 차순으로 정렬
			break;
		case 'b':
			cout<<"자동으로 난수를 생성해서 입력합니다"<<endl;
            //c = (rand()/static_cast<double>(RAND_MAX)*2-1)*9; //-9~9까지 double형 변수 생성
            c = rand()%19-9;
            e = rand()%6; // 0~5 사이의 난수 생성
			b.add(c, e);
			break;
		case 'p': //a+b
			cout << "a+b: ";
			//a.addAll(&b);
			cout << " a : ";
            a.display();
            cout << " b : ";
			b.display();
            cout << "결과 : ";
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
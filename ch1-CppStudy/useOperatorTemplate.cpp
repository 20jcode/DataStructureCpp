//
// Created by leeyoungjun on 2023/10/13.
//

#include "iostream"

using namespace std;

class InsideObj {
private:
    int num1;
    int num2;

public:
    InsideObj() {
        num1 = 0; num2 = 0;
    }

    int getNum1() {
        return num1;
    }

    friend ostream& operator<<(ostream& os, InsideObj obj);
};

ostream& InsideObj::operator<<(ostream& os, InsideObj obj){
    os<< obj.num1 << endl;

    return os;
}
// 해당 오버라이딩에 대한 설명
/*
 * friend 선언으로 외부에서 InsideObj의 내부에 접근할 수 있음
 * 기본적으로 구현되어있는 ostream의 << 연산자에 대해서 특수한 타입으로 정의
 *
 * 자바의 Object에서 구현된 toString()을 다시 오버라이딩하는 것과 같은 것
 */

/*
 * 일반적으로 std::cout<< InsideObj; 이라고 사용하는 경우를 생각해보자.
 * 이는 함수를 호출하는 것이다.
 *
 * operator<<(std::cout,InsideObj);
 * 그러면 내가 오버라이딩한 함수가 호출되고 실행되는 것.
 * std::cout은 ostream의 객체이며, 프로그램 시작 시 생성되는 객체
 * 참조방식으로 해당 객체가 전달되고, 내가만든 객체도 전달됨
 *
 * 프랜드로 정의되었기에 private멤버에 접근가능
 *
 * 나는 os<< obj.num1 << endl; 이라고 하였으니까
 * os 객체에 obj.num1 을 전달 -> int형식이니까 기본 <<에 정의된 방식으로 값이 넘어가게 되는것
 * 다시 해당 객체의 수정된 참조를 반환하므로 종료
 *
 */

template <class T>
// 이는 <typename T>와도 같다. cpp 버전 상승하며 표현의 명확성을 위해 typename을 쓰기로함
// 하지만 하위 호환성을 위해서 그대로 class 로 사용하는 것도 지원해줌
class Stack {
private:
    T* stack;
    int capacity;

public:
    Stack(int stackCapacity = 10);
    friend ostream& operator<<<T>(ostream& os, Stack<T>&);
	friend istream& operator>><T>(istream& os, Stack<T>&);
};

template <class T>
ostream& Stack<T>::operator<<(ostream& os, Stack<T>& s) {

    os<<s.capacity<<endl;

    return os;
}
template <class T>
istream& operator>>(istream& os, Stack<T>& s) {
	return os;
}

template <class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity){
    stack = new T[capacity];
}

int main(void){

    Stack<InsideObj> s;


    return 0;
}
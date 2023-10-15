//
// Created by leeyoungjun on 2023/10/15.
//

#include "iostream"

using namespace std;

template <class T>
class TestA{
private:
    T name;
    string s;

public:
    TestA(){
        s = "첫번째 테스트 입니다";
    }

    template<class U>
    friend ostream& operator<<(ostream&, const TestA<U>&);
};

template<class U>
ostream& operator<<(ostream& os, TestA<U> t){

    os<<t.s<<endl;
    return os;
}

int main(void){

    TestA t= TestA<int>();

    cout<<t<<endl;
}
# Ch1

## 템플릿의 동작방식

템플릿은 컴파일에서 해당 사용하는 자료형에 맞춰서
코드를 만들어준다.

## include 에서의 <> 와 ""의 차이

< > 이 표시를 사용하면 컴파일러와 같은 폴더에서 찾기

" " 이 표시를 사용하면 환경변수나 프로젝트 설정 등을 참고해서 찾기

## 템플릿과 operator<< 오버라이딩

```
template <class T>
class Stack {
    ...
    
public:
    friend ostream& operator<<<T>(ostream& os, Stack<T>&);
```

이런식으로 코드가 존재할 수 있는 지 모르겠다.

템플릿에 대해서 friend 선언하는 방식은 두가지가 있다.

참고 : https://www.devoops.kr/126

### N:N관계?

```
template<class T>
class TestA{
...

public:
    template<class U>
    friend ostream& operator<<(ostream&, const TestA<U>&);
    
}
```

만약 int 타입과 float타입으로 TestA 클래스를 만들어서 사용하는 경우

operator는 int와 float 둘 다 생성되며, int형 오퍼레이터에 대한 코드는 float 내부에도
접근 가능한 방식?

TestA의 선언에서, template으로 선언 되었기떄문에 어떤 형식이던지 operator<< 는 내부의
private에 접근할 수 있으므로

### 방법 2

```
template<class T>
class TestB{
...

public:
    friend ostream& operator<<(ostream&, const TestB<T>&);
    
//함수 외부에서 구현할 경우
ostream& operator<<(ostream& os,TestB<내가사용할클래스지정>& s){

}

```

여기서 외부에서 구현할 경우에는 직접 내가 사용할 클래스 입력해야한다. (int를 할려면 TestB<int>로 구현)

friend는 해당 TestB에 속해있는 것이 아니기에, 내가 int형식 사용을 위해서 TestB<int>로 만들어서
컴파일하는 경우 operator는 구현이 안되기 때문.

그렇다면, 외부에서 U로 받아서 해도 되나?

그냥 내부에서 진행하는 것이 좋을 것 같다는 생각이 든다.

```
template<class T>
class TestC{
...

public:
    friend ostream& operator<<(ostream& os,const TestC<T>& t){
        ...
        return os;
    }
}

```
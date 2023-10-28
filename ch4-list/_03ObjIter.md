# iterator

사용 시 장점은 무엇이 있을까?

일단 어떤 형태로 구현된 리스트인지 상관없이 iterator를 사용해서 일괄되게 처리할 수 있다?

## 이 둘의 차이는 무엇일까?

ListIterator li (l);
이라고 하였을 때,

li.GetCurrent()->getSalary();
li->getSalarry();

결과적으로 동작은 같다. 하지만 아래의 문장을 사용하기 위해서는 -> 연산자에 대해서 현재 data를 반환하도록
오버라이딩이 되어있는 상태에서만 사용 가능하다.


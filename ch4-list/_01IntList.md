# 내용정리

## 정수 연결 리스트
[_01IntList.cpp](_01IntList.cpp)

리스트는 내부에 순서를 가지고 연결된 자료구조이다.

중복을 허용

Add()에서 정렬된 상태를 유지하면서 동작한다.

리스트에서는 3가지 상황을 기반으로 생각한다.

1. 리스트 내부가 비었을 때
2. 리스트 내부의 원소가 1개 있을 때
3. 리스트 내부의 원소가 2개 이상 있을 때

### Add()에서의 동작

newNode : 더할 element
p : first를 가리키는 포인터
q : p->link를 가리키는 포인터

1. 상황에서 : first를 newNode로 만든다.

2. p==first && p->link == nullptr 일때
    p->data 와 입력받은 element의 대소비교를 하여 삽입한다.
    first는 작은 값이 되고, first->link는 큰 값이 된다.

3. newNode<=p 일떄, p<newNode<q 일때
    while(p != nullptr) 일떄까지 반복한다.

2번과 3번은 항상 로직으로 처리할 수 있다.

```
void LinkedList::Add(int element)
{
	Node* newNode = new Node(element);

    Node* p = first;
    Node* q = first->link;

    if(p == nullptr){
        first = newNode;
    } else {
        while(p != nullptr){
            if(newNode<=p){ // newNode<=p
                newNode->link = p;
                if(p == first){ //원소가 하나만 있는 경우
                    first = newNode;
                }
            } else if(newNode<=q){ // p<newNode<=q
                p->link = newNode;
                newNode->link = q;
            } else { // p<=q<newNode
                p = p->link;
                q = q->link;
            }
        }
    }

}
```

그럼 여기서 제일 마지막 순환으로 p->link == nullptr이고
q == nullptr일 때 q = q->link가 동작할 수 있는가?

오류가 발생한다.

if 문으로 조건을 걸어줬다.

---

다시 생각해보니, 원형 링크드 리스트가 아니라면, q를 사용하지 않는 것이
성능 상 이점과 코딩의 편리성을 줄 것 같다. q가 nullptr인 순간마다
새로운 조건문을 걸어주는 것은 본질적으로 옳지 않다.

링크드리스트를 직접 구현하는 것은 메모리와 성능의 극한의 최적화를 위해서인데
새로운 포인터나 조건문을 더 거는 것은 극한의 이득을 취할 수 없기떄문이다.

---


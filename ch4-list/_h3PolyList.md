# 다항식 리스트

circular linked list with headnode 버전으로 구현하도록 한다.



## Term

템플릿 내부에 다항식을 담기 위한 틀이 되도록 함.

Term 내부에서도 계수에 다양한 자료형을 담을 수 있도록 템플릿으로 받도록 한다.

## Chain

ChainNode를 관리하기 위한 클래스이다.


Delete(void) : first를 제거한다.

## Polynomial

다항식 리스트가 된다.
Chain의 ChainNode로 Term을 가리키게 된다.

---

# _home_03_02

헤드노드가 있는 서큘러 링크드 리스트.

## void Chain<T>::Delete(void)

헤드노드가 last이자 first인 경우 -> 아무 삭제 안해도 됨.

헤드노드 + 실제노드 1개 인 경우 -> 삭제하고 헤드노드 == last

헤드노드 + 실제노드 2개 이상인 경우 -> head->link = head->link->link;
이때 last는 조작하지 않아도 됨.


## void Chain<T>::Add(const T& element)

### 궁금증

?? ChainNode<T>* newNode = new ChainNode<T>(element); 와

그냥 new ChainNode(element) 의 차이는? 

위는 특정 데이터 타입 T를 개체에 생성자로 전달해서 인스턴스화 시키고

아래는 클래스가 특정 타입으로 정의된 경우 사용 가능한 듯?

### 아무튼 구현

1. 헤드노드만 존재하는 경우
2. 노드 중간에 element가 위치하는 경우
3. 제일 마지막 값보다 element가 큰 경우

```
while(p->link != head){ //다음 노드가 head가 아닌 경우에만
    if(p->data.exp>newNode->data.exp && p->data.exp < newNode->data.exp){
        // p의 exp > newNode의 exp > p->link의 exp
        
    }
}

```

head -> exp3 인 체인이 존재하는 경우를 생각해보자.

p = 3이고, p->link = head 이므로 while을 돌지 않게 된다.

이때 newNode = 2 인 경우에는 ?

안됨.

다음이 head가 아니고, 다음것보다 크면 삽입, 같으면 더하기?





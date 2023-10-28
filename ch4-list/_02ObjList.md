# 객체 연결 리스트

```c++
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
                if(newNode->data <p->link->data || newNode->data == p->link->data) {
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
```

Add 메소드를 더 간단하게 하였다.

1. 내부가 null인 경우 -> first를 바로 newNode로 만들어줌
2. null이 아니면서 newNode가 제일 작은 경우 바로 처리해줌
3. while 내부에서 p와 p->link 사이에 newNode가 존재하는 경우 넣어줌
4. newNode가 제일 크다면 while을 지나서 마지막에 연결해줌

OR 연산은 반드시 필요한듯? -> while문은 포인터가 제일 마지막에 도달하기 전까지 멈추지않으므로? 아니다. 결국 다음 값을 만나면 newNode가
더 작아진다.

11, 13, 15 에 13을 넣어보겠다.

while 내부에서 OR 연산은 필요없었다.

---

노드를 추가하거나 삭제할때는 node->link 에 대해 null검사를 해서 이전 노드에 대한 포인터를 유지해야한다.

merge나 검색, 삭제에 대해서는 단순하게 nullptr 검사를 바로 하는 것이 좋은 듯 하다.

---

객체에서 내부 데이터의 값을 비교할 때, eno의 타입이 char로 되어있어서 대소비교에서 제대로 동작하지 않는 버그를 발견

stoi()를 이용해서 string을 int형식으로 바꿔서 대소비교를 하도록 operator<를 수정함.


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


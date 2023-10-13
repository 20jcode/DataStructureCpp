//
// Created by leeyoungjun on 2023/10/13.
//

// 8*8 체스판에서 퀸을 최대로 배치하는 경우, 몇가지의 경우의 수가 나올 수 있는가?

// Stack을 사용해서 재귀가 아닌 방식으로  표현해보자


#include <iostream>
#define ROW 8
#define COL 8
using namespace std;
class Point {
private:
	int ix;
	int iy;
public:
	Point() { ix = 0; iy = 0; }
	Point(int x, int y) {
		ix = x;
		iy = y;
	}
	int getX() {
		return ix;
	}
	int getY() {
		return iy;
	}
	void setX(int x) {
		ix = x;
	}
	void setY(int y) {
		iy = y;
	}
	friend ostream& operator<<(ostream& os, Point px);
};

ostream& operator<<(ostream& os, Point px) {
	os << "(" << px.ix << ", " << px.iy << ")" << endl;
	return os;
}
template <class T>
class Stack {
public:
	Stack(int stackCapacity = 10);
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& item);
	T& Pop();
	friend ostream& operator<<<T>(ostream& os, Stack<T>&);
	friend istream& operator>><T>(istream& os, Stack<T>&);
private:
	T* stack;
	int top;
	int capacity;
};


template <class T>
istream& operator>>(istream& os, Stack<T>& s) {
	return os;
}
template <class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = oldSize;
	if (oldSize > newSize) number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, number);
	delete[] a;
	a = temp;
}

template <class T>
inline bool Stack<T>::IsEmpty() const { return top == -1; }

template <class T>
inline T& Stack<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[top];
}

template <class T>
void Stack<T>::Push(const T& x)
{
	if (top == capacity - 1)
	{
		ChangeSizeID(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template <class T>
T& Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete.";
	return stack[top--];
}


//가로열에 퀸을 둘 수 있다면 true, 아니면 false
bool checkRow(int d[][COL], int crow) {
    for(int i = 0; i<ROW;i++){
        if(d[crow][i] == 1){
            return false;
        }
    }
    return true;
}

//세로열에 퀸을 둘 수 있다면 true, 아니면 false
bool checkCol(int d[][COL], int ccol) { //세로에 들어갈 수 있는지 확인

    for(int i = 0; i<ccol; i++){
        if(d[i][ccol] == 1){
            return false;
        }
    }
    return true;
}

//대각선 왼쪽 위아래로 퀸을 둘 수 있다면 true, 아니면 false
bool checkDiagSW(int d[][COL], int cx, int cy) { // x++, y-- or x--, y++ where 0<= x,y <= 7

    for(int i = 0; (i<ROW-cx)||(i>cy);i++){
        if(d[cx+i][cy-i] == 1){
            return false;
        }
    }
    for(int i = 0; (i<cx)||(i>COL-cy);i++){
        if(d[cx-i][cy+i] == 1){
            return false;
        }
    }
    return true;
}

bool checkDiagSE(int d[][COL], int cx, int cy) {// x++, y++ or x--, y--

    for(int i = 0; (i<ROW-cx)||(i<COL-cy);i++){
        if(d[cx+i][cy+i] == 1){
            return false;
        }
    }

    for(int i = 0; (i<cx)||(i<cy); i++){
        if(d[cx-i][cy-i] == 1){
            return false;
        }
    }
    return true;
}

bool checkMove(int d[][COL], int x, int y) {// (x,y)로 이동 가능한지를 check

    if(checkRow(d,x)&& checkCol(d,y)&&checkDiagSW(d,x,y)&&checkDiagSE(d,x,y)){
        return true;
    }

    return false;
}
int nextMove(int d[][COL], int row, int col) {// 현재 row, col에 대하여 이동할 col을 return

    for(int i=0;i<ROW;i++){
        for(int j=col+1;j<COL;j++){
            if(checkMove(d,i,j)){
                return j;
            }
        }
    }

    return -1; //이동할 수 있는 곳이 없다면 -1 리턴



}

void showQueens(int data[][COL]) {

}
void solveQueen(int d[][COL]) {
	int ans = 0;
    Stack<Point> s;
    int sSum = 0;
    Point target;

    for(int i = 0; i<ROW; i++){
        for(int j = 0; j<COL; j++){

            s.Push(Point(i,j));
            d[i][j]=1;
            sSum=1;

            while(!s.IsEmpty()){

                target = s.Top();

                nextMove(d,target.getX(),target.getY());

                if(checkMove(d,i,j)){
                    s.Push(Point(i,j));
                    d[i][j] = 1;
                    sSum+=1;
                }
                if(sSum == 8){
                    target = s.Pop();
                    ans+=1;
                    d[target.getX()][target.getY()]=0;
                }

                sSum +=1;
            }
        }
    }

    cout<<ans<<endl;

}



int main(void) {
	const int row = ROW, col = COL;
	int data[row][col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			data[i][j] = 0;

	solveQueen(data);
	system("pause");
	return 0;
}
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
	friend ostream& operator<<(ostream& os, Stack<T>& s){
        os<<s.top<<endl;
    }
	friend istream& operator>>(istream& os, Stack<T>& s){
        return os; //입력은 받지 않아도 되는 듯 싶다.
    }
private:
	T* stack;
	int top;
	int capacity;
};

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

//return stack[top--]
template <class T>
T& Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete.";
	return stack[top--];
}


//가로열에 퀸을 둘 수 있다면 true, 아니면 false
bool checkRow(int d[][COL], int crow) {
    for(int i = 0; i<COL;i++){
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

//대각선 오른쪽 위 왼쪽 아래 퀸을 둘 수 있다면 true, 아니면 false
bool checkDiagSW(int d[][COL], int cx, int cy) { // x++, y-- or x--, y++ where 0<= x,y <= 7

    for(int i = 0; (i<ROW-cx)&&(i>cy);i++){
        if(d[cx+i][cy-i] == 1){
            return false;
        }
    }
    for(int i = 0; (i<cx)&&(i>COL-cy);i++){
        if(d[cx-i][cy+i] == 1){
            return false;
        }
    }
    return true;
}

//대각선 왼쪽 위 오른쪽 아래로 퀸을 둘 수 있다면 true, 아니면 false
bool checkDiagSE(int d[][COL], int cx, int cy) {// x++, y++ or x--, y--

    for(int i = 0; (i<ROW-cx)&&(i<COL-cy);i++){
        if(d[cx+i][cy+i] == 1){
            return false;
        }
    }

    for(int i = 0; (i<=cx)&&(i<=cy); i++){
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

    if(row+1==ROW){
        return -1;
    }

    for(int j=0;j<COL;j++){
        if(checkMove(d,row+1,j)){ //다음 row에 대해서 0부터 들어갈 수 있는 지 확인함.
            return j;
        }
    }

    return -1; //이동할 수 있는 곳이 없다면 -1 리턴



}

void showQueens(int data[][COL]) {

    for(int i=0; i<ROW;i++){
        cout<<i<<"번째 : ";
        for(int j=0; j<COL;j++){
            cout<<j<<": ["<<data[i][j]<<"]";
        }
        cout<<endl;
    }
    cout<<endl<<endl;

}
void solveQueen(int d[][COL]) {
	int ans = 0;
    Stack<Point> s;
    int sSum = 0;
    Point target;
    Point lastPop;

    for(int i = 0; i<ROW; i++){
        for(int j = 0; j<COL; j++){



            cout<<i<<" "<<j<<endl;

            s.Push(Point(i,j));
            d[i][j]=1;
            sSum=1;

            while(!s.IsEmpty()){

                target = s.Top();

                int nextCol = nextMove(d,target.getX(),target.getY());

                if(nextCol == -1){
                    if(sSum == ROW){
                        ans+=1;
                    }
                    lastPop = s.Pop();

                    sSum-=1;
                } else{
                    if(lastPop.getY()==nextCol){//Pop이 되면 target은 계속 top을 가리키며, 다만 Pop된 자리는 다시 둘 수 없다.
                        for(int py=nextCol;py<COL;py++){ //같은 줄에서 퀸을 놓을 수 있는 다음 자리가 있는지 확인
                            if(checkMove(d,target.getX(),py)){
                                s.Push(Point(target.getX(),py));

                            } else{ //더이상 퀸을 놓을 수 있는 자리가 그 줄에 없다면
                                lastPop = s.Pop();

                                sSum-=1;
                            }
                        }
                    } else{
                        s.Push(Point(target.getX()+1,nextCol));
                        sSum+=1;

                    }

                }


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


	return 0;
}
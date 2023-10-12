//
// Created by 이영준 on 2023-10-12.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

//cpp을 위해서 헤더파일

using namespace std; //cout, cin에서 namespace 없이 바로 사용하기 위해

#define AROWS 3
#define ACOLS 4


// 헤더파일

class Matrix;

class Term {
    friend Matrix;

private:
    float coef;
    int exp;
};

class Matrix {

private:
    int rows,cols;
    static Term* TermElement; //2차원 행렬을 1차원 객체배열에서 관리하기 위하여
    static int free; //남아있는 배열의 칸을 가리키기 위해서
    int start,finish;
    int terms;

public:
    Matrix(int row, int col) : rows(row),cols(col) {
        start = finish = terms = 0;
    }

    int get_data();
    int show_data();
    Matrix& addMatrix(Matrix&);
};

int Matrix::get_data() {

	start = free;

	terms = rows * cols;

	finish = start + terms;

	free += finish;

	for (int i = start; i < finish; i++) {

		TermElement[i].coef = rand() % 20;

		TermElement[i].exp = rand() % 5;

	}

	return 1;

}

int Matrix::show_data() {

	cout << endl;

	for (int i = start; i < finish; i++) {

		if ((i - start) % cols == 0)

			cout << endl;

		cout << TermElement[i].coef << "x" << TermElement[i].exp<<"  ";

	}

	cout << endl;

	return 1;

}

Matrix& Matrix::addMatrix(Matrix& m){

	Matrix ans(rows,cols);

	ans.get_data();

	for (int i = ans.start; i < ans.finish; i++){

		int j = i-ans.start;

		TermElement[i].coef = TermElement[j+start].coef + TermElement[j+m.start].coef;

		if (false){ // exp는 항상 일치한다는 가정하게 조건 검사 skip

		} else {
			TermElement[i].exp = TermElement[j+start].exp;
		}
	}

	return ans;

}


int Matrix::free = 0;

Term* Matrix::TermElement = new Term[100];

int main(void)

{

	Matrix matrixA(AROWS, ACOLS);

	Matrix matrixB(AROWS, ACOLS);

	Matrix matrixC(AROWS, ACOLS);

	srand(time(NULL));

	matrixA.get_data();

	matrixA.show_data();

	matrixB.get_data();

	matrixB.show_data();

	matrixC = matrixA.addMatrix(matrixB);

	matrixC.show_data();

	system("pause");

	return 0;

}
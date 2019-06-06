#include "Matrix.h"

#ifdef DEBUG
#define PRT(A) std::cout<<A<<std::endl
#define EQUAL(A,B) if((A)==(B)) PRT("Success    "<<(A)<<"=="<<(B));else PRT("Failed    "<<(A)<<"=="<<(B))
#else
#define PRT(A)
#define EQUAL(A,B)
#endif

Matrix::Matrix():ROW_NUM(3),COL_NUM(3){
    arr = new Bignum[ROW_NUM*COL_NUM];
}

Matrix::Matrix(int row, int col):ROW_NUM(row),COL_NUM(col){
    arr = new Bignum[ROW_NUM*COL_NUM];
}

Matrix::Matrix(int *array){
    ROW_NUM = 3;
    COL_NUM = 3;
    arr = new Bignum[ROW_NUM*COL_NUM];
    for(int i = 0; i < ROW_NUM*COL_NUM; i++){
        arr[i] = array[i];
    }
}

Matrix::Matrix(string *array){
    ROW_NUM = 3;
    COL_NUM = 3;
    arr = new Bignum[ROW_NUM*COL_NUM];
    for(int i = 0; i < ROW_NUM*COL_NUM; i++){
        arr[i] = array[i].c_str();
    }
}

Matrix::Matrix(string *array,int row, int col):ROW_NUM(row),COL_NUM(col){
    arr = new Bignum[ROW_NUM*COL_NUM];
    for(int i = 0; i < ROW_NUM*COL_NUM; i++){
        arr[i] = array[i].c_str();
    }
}

Matrix::Matrix(string number):ROW_NUM(1),COL_NUM(1){
    arr = new Bignum[ROW_NUM*COL_NUM];
    arr[0] = number.c_str();
}

Matrix::~Matrix(){
    delete []arr;
}

Matrix::Matrix(const Matrix& matrix):ROW_NUM(matrix.ROW_NUM),COL_NUM(matrix.COL_NUM){
    arr = new Bignum[ROW_NUM*COL_NUM];
    for(int i = 0; i < ROW_NUM*COL_NUM; i++){
        arr[i] = matrix.arr[i];
    }
}

void Matrix::print() const{
    using namespace std;
    // cout<<"print matrix"<<endl;
    for(int i = 0; i < ROW_NUM; i++){
        for(int j = 0; j < COL_NUM; j++){
            cout<<arr[i*ROW_NUM+j].getVal()<<" ";
        }
        cout<<endl;
    }
}

string Matrix::to_string() const{
    string res;
    for(int i = 0; i < ROW_NUM; i++){
        for(int j = 0; j < COL_NUM; j++){
            res+=arr[i*ROW_NUM+j].getVal();
            if(j != COL_NUM-1){
                res += " ";
            }
        }
        res+='\n';
    }
    return res;
}

Matrix Matrix::operator~() const{
    Matrix m(COL_NUM,ROW_NUM);
    for(int i = 0; i < ROW_NUM; i++){
        for(int j = 0; j < COL_NUM; j++){
            m.arr[j*COL_NUM+i] = arr[i*ROW_NUM+j];
        }
    }
    return m;
}

Matrix Matrix::operator+() const{
    Matrix m(*this);
    return m;
}

Matrix Matrix::operator-() const{
    Matrix m(COL_NUM,ROW_NUM);
    for(int i = 0; i < ROW_NUM; i++){
        for(int j = 0; j < COL_NUM; j++){
            m.arr[j*COL_NUM+i] = -arr[j*COL_NUM+i];
        }
    }
    return m;
}

Matrix& Matrix::operator=(const Matrix& m){
    if(&m == this){
        return *this;
    }
    ROW_NUM = m.ROW_NUM;
    COL_NUM = m.COL_NUM;
    for(int i = 0; i < COL_NUM*ROW_NUM; i++){
        arr[i] = m.arr[i];
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m){
    if(ROW_NUM != m.ROW_NUM || COL_NUM != m.COL_NUM){
        Matrix_error("Add matrices error ");
    }
    int number = ROW_NUM*COL_NUM;
    for(int i = 0; i < number; i++){
        arr[i] += m.arr[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m){
    if(ROW_NUM != m.ROW_NUM || COL_NUM != m.COL_NUM){
        Matrix_error("Add matrices error ");
    }
    int number = ROW_NUM*COL_NUM;
    for(int i = 0; i < number; i++){
        arr[i] -= m.arr[i];
    }
    return *this;
}

Matrix operator+(const Matrix& m1,const Matrix& m2){
    Matrix m(m1.ROW_NUM,m1.COL_NUM);
    if(m1.ROW_NUM != m2.ROW_NUM || m1.COL_NUM != m2.COL_NUM){
        Matrix_error("Add matrices error ");
    }
    int number = m.ROW_NUM*m.COL_NUM;
    for(int i = 0; i < number; i++){
        m.arr[i] = m1.arr[i] + m2.arr[i];
    }
    return m;
}

Matrix operator-(const Matrix& m1,const Matrix& m2){
    Matrix m(m1.ROW_NUM,m1.COL_NUM);
    if(m1.ROW_NUM != m2.ROW_NUM || m1.COL_NUM != m2.COL_NUM){
        Matrix_error("Add matrices error ");
    }
    int number = m.ROW_NUM*m.COL_NUM;
    for(int i = 0; i < number; i++){
        m.arr[i] = m1.arr[i] - m2.arr[i];
    }
    return m;
}

Matrix operator*(const Matrix& m1,const Matrix& m2){
    int n,m,k;
    n = m1.ROW_NUM;
    k = m1.COL_NUM;
    m = m2.COL_NUM;
    if((n == 1 && k == 1)){
        Matrix m(m2.ROW_NUM,m2.COL_NUM);
        m = m1.arr[0]*m2;
        return m;
    }
    if((m == 1 && m2.ROW_NUM == 1)){
        Matrix m(m1.ROW_NUM,m1.COL_NUM);
        m = m2.arr[0]*m1;
        return m;
    }
    if(k != m2.ROW_NUM){
        Matrix_error("Multiplication of matrices error");
    }
    Matrix mat(m2.ROW_NUM,m1.COL_NUM);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            Bignum res;
            for(int t = 0; t < k; t++){
                res += m1.arr[i * k + t] * m2.arr[t * m + j];
            }
            mat.arr[i * m + j] = res;
        }
    }
    return mat;
}

Matrix operator*(const Bignum& num,const Matrix& m){
    Matrix mat(m.ROW_NUM,m.COL_NUM);
    int number = m.ROW_NUM*m.COL_NUM;
    for(int i = 0; i < number; i++){
        mat.arr[i] = num * m.arr[i];
    }
    return mat;
}

bool operator==(const Matrix& m1,const Matrix& m2){
    if(m1.ROW_NUM != m2.ROW_NUM || m1.COL_NUM != m2.COL_NUM){
        return false;
    }
    int size = m1.ROW_NUM*m1.COL_NUM;
    for(int i = 0; i < size; i++){
        if(m1.arr[i] == m2.arr[i]){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

#ifdef DEBUG
int main(){
    int A[] = {
        1,2,3,
        4,5,6,
        7,8,9
    };
    int B[] = {
        1,1,1,
        1,1,1,
        1,1,1
    };
    int C[] = {
        2,2,2,
        2,2,2,
        2,2,2
    };
    string D[] = {
        "1","2","3",
        "1","2","3",
        "1","2","3"
    };
    int E[] = {
        1,4,7,
        2,5,8,
        3,6,9
    };
    int F[] = {
        2,3,4,
        5,6,7,
        8,9,10
    };
    int G[] = {
        14,32,50,
        32,77,122,
        50,122,194
    };
    string H[] = {
        "2"
    };

    /* test constructor */
    PRT("test constructor");
    Matrix mat1(A);
    Matrix mat2(B);
    Matrix mat3(C);
    Matrix mat4(D);
    mat1.print();

    /* test assignment */
    PRT("test assignment");
    Matrix mat5;
    mat5 = mat1;
    mat5.print();

    /* test unary connective */
    PRT("test unary connective");
    Matrix mat6(E);
    Matrix mat7 = ~mat1;
    mat7.print();
    Matrix m10;
    m10 = -mat7;
    m10.print();
    Matrix m11;
    m11 = +mat7;
    m11.print();
    EQUAL(mat6==mat7,true);

    /* test binary connective */
    PRT("test binary connective");
    Matrix mat8(F);
    Matrix mat9 = mat1 + mat2;
    mat9.print();
    EQUAL(mat8==mat9,true);
    Matrix mat10 = mat3 - mat2;
    mat10.print();
    EQUAL(mat10==mat2,true);
    Matrix mat11(G);
    mat10 = mat1*mat6;
    mat10.print();
    EQUAL(mat11==mat10,true);
    Matrix mat100(H,1,1);
    mat10 = mat2*mat100;
    EQUAL(mat3==mat10,true);
    mat10 = mat100*mat2;
    EQUAL(mat3==mat10,true);

    /* test assignment opeartion */
    PRT("test assignment opeartion");
    mat1 += mat2;
    EQUAL(mat1==mat8,true);
    mat3 -= mat2;
    EQUAL(mat3==mat2,true);

    /* test error */
    PRT("test error");

    return 0;
}
#endif

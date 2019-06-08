#include "../src/Matrix.h"

#ifdef DEBUG
#define PRT(A) std::cout<<A<<std::endl
#define EQUAL(A,B) if((A)==(B)) PRT("Success    "<<(A)<<"=="<<(B));else PRT("Failed    "<<(A)<<"=="<<(B))
#else
#define PRT(A)
#define EQUAL(A,B)
#endif

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

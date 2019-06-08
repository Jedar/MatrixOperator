#include "../src/Polish.h"
#include <iostream>

using namespace std;

#ifdef DEBUG
int main(){
    cout<<"test RPN"<<endl;
    string A = "100*A-B*100";
    string B = "A+~B*C-D";
    string C = "A*B*~C+D*F";
    vector<string> m;
    m.push_back(A);
    m.push_back(B);
    m.push_back(C);
    POLISH::RPN(m);
    for(string rpn:m){
        cout<<rpn<<endl;
    }
    /* test OP */
    cout<<"test OP"<<endl;
    int D[] = {
        1,1,1,
        1,1,1,
        1,1,1
    };

    int E[] = {
        2,2,2,
        2,2,2,
        2,2,2
    };

    Matrix m1(D);
    Matrix m2(E);
    vector<Matrix *> ms;
    // vector<Matrix *> stack;
    ms.push_back(&m1);
    ms.push_back(&m2);
    // stack.push_back(&m1);
    // stack.push_back(&m2);
    // OP(stack,"-",ms);
    // stack[0]->print();
    m1.print();
    m2.print();
    (m1 - m2).print();
    // delete stack[0];

    /* test analyse RPN */
    cout<<"test analyse RPN"<<endl;
    vector<string> name;
    name.push_back("A");
    name.push_back("B");
    string exp = "~A*B+A+=A";
    exp = POLISH::RPN(exp);
    Matrix m3 = POLISH::analyseRPN(name,ms,exp);
    m3.print();

    return 0;
}
#endif//DEBUG


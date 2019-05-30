#include "Polish.h"
#include <iostream>

using namespace std;

static bool isOperator(char ch);
static bool isSingleOperator(char ch);
static bool isNumber(char ch);
static int findIndex(const vector<string>& names, string who);
static void OP(vector<Matrix *>& stack, string op, const vector<Matrix *>& matrices);
static bool exists(const vector<Matrix *>& matrices, Matrix *m);

void POLISH::RPN(vector<string>& exps){
    for(int j = 0; j < exps.size(); j++){
        string exp = exps[j];
        exps[j] = RPN(exp);
    }
}

void POLISH::analyseRPN(const vector<string>& names, const vector<Matrix *>& matrices, const vector<string>& exps, vector<Matrix *>& answers){
    /* stack */
    vector<Matrix *> stack;
    for(string exp:exps){
        Matrix *m = new Matrix();
        /* transfer matrix must be new one, then 
         * delete matrices in result wouldn't cause error */
        *m = analyseRPN(names,matrices,exp);
        answers.push_back(m);
    }
}

Matrix POLISH::analyseRPN(const vector<string>& names, const vector<Matrix *>& matrices, const string exp){
    Matrix res;
    /* stack */
    vector<Matrix *> stack;
    int len = exp.size();
    int start = 0, count = 0;
    /* operator:true name:flase */
    bool flag;
    for(int i = 0; i < len; i++){
        char ch = exp.at(i);
        if(count == 0){
            start = i;
            count++;
            flag = isOperator(ch)||isSingleOperator(ch);
        }
        else if(ch == ' '){
            if(flag){
                OP(stack,exp.substr(start,count),matrices);
            }
            else{
                int idx = findIndex(names,exp.substr(start,count));
                if(idx == -1){
                    stack.push_back(new Matrix(exp.substr(start,count)));
                }
                else{
                    stack.push_back(matrices[idx]);
                }
            }
            count =0;
        }
        else {
            count++;
        }
    }
    res = *stack[0];
    if (!exists(matrices,stack[0])){
        delete stack[0];
    }
    stack.clear();

    return res;
}

string POLISH::RPN(string exp){
    /* stack */
    vector<string> ops;
    int len = exp.size();
    string buf,result;
    int start = 0, count = 0;
    /* current letter is operator ? true:yes flase:no */
    bool flag;
    for(int i = 0; i < len; i++){
        char ch = exp.at(i);
        if(count == 0){
            if(isSingleOperator(ch)){
                buf = ch;
                while(!ops.empty()){
                    string cmp = ops[ops.size()-1];
                    if(priority(buf)<=priority(cmp)){
                        result.append(cmp+" ");
                        ops.pop_back();
                    }
                    else{
                        break;
                    }
                }
                ops.push_back(buf);
            }
            else{
                flag = isOperator(ch);
                start = i;
                count++;
            }
                
        }
        else if(flag == isOperator(ch)){
            count++;
        }
        /* reset start and count value */
        else if(flag || isSingleOperator(ch)){
            buf = exp.substr(start,count);
            while(!ops.empty()){
                string cmp = ops[ops.size()-1];
                if(priority(buf)<=priority(cmp)){
                    result.append(cmp+" ");
                    ops.pop_back();
                }
                else{
                    break;
                }
            }
            ops.push_back(buf);
            count = 0;
            i--;
        }
        else{
            buf = exp.substr(start,count);
            result.append(buf+" ");
            count = 0;
            i--;
        }
    }
    if(count != 0){
        buf = exp.substr(start,count);
        result.append(buf+" ");
    }
    while(!ops.empty()){
        string cmp = ops[ops.size()-1];
        result.append(cmp+" ");
        ops.pop_back();
    }
    return result;
}

int POLISH::priority(string conn){
    if(conn == "+" || conn == "-"){
        return 2;
    }
    else if(conn == "*" || conn == "/"){
        return 3;
    }
    else if(conn == "~"){
        return 4;
    }
    else if(conn == "+=" || conn == "-="){
        return 1;
    }
    else{
        return 0;
    }
}

static bool isOperator(char ch){
    return (ch == '+')||(ch == '-')||(ch == '*')||(ch == '/')||(ch == '=');
}

static bool isSingleOperator(char ch){
    return (ch == '~');
}

static bool isNumber(char ch){
    return (ch >= '0')&&(ch <= '9');
}

static int findIndex(const vector<string>& names, string who){
    int size = names.size();
    for(int i = 0; i < size; i++){
        string str = names[i];
        if(who == str){
            return i;
        }
    }
    return -1;
}

static bool exists(const vector<Matrix *>& matrices, Matrix *m){
    for(Matrix *mat:matrices){
        if(m == mat){
            return true;
        }
    }
    return false;
}

static void OP(vector<Matrix *>& stack, string op, const vector<Matrix *>& matrices){
    if(op == "~"){
        Matrix *mat = new Matrix();
        *mat = ~*stack[stack.size()-1];
        stack.pop_back();
        stack.push_back(mat);
        return;
    }
    bool mat1Used = false;
    Matrix *mat2 = stack[stack.size()-1];
    stack.pop_back();
    Matrix *mat1 = stack[stack.size()-1];
    stack.pop_back();
    if(op == "+"){
        Matrix *ans = new Matrix();
        *ans = *mat1 + *mat2;
        stack.push_back(ans);
    }
    else if(op == "-"){
        Matrix *ans = new Matrix();
        *ans = *mat1 - *mat2;
        stack.push_back(ans);
    }
    else if(op == "*"){
        Matrix *ans = new Matrix();
        *ans = *mat1 * *mat2;
        stack.push_back(ans);
    }
    else if(op == "+="){
        *mat1 += *mat2;
        mat1Used = true;
        stack.push_back(mat1);
    }
    else if(op == "-="){
        *mat1 -= *mat2;
        mat1Used = true;
        stack.push_back(mat1);
    }
    else{
        cerr<<"Wrong operation \""<<op<<"\""<<endl;
        exit(0);
    }
    if(!exists(matrices,mat1)&&!mat1Used){
        delete mat1;
    }
    if(!exists(matrices,mat2)){
        delete mat2;
    }
}

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
    vector<Matrix *> stack;
    ms.push_back(&m1);
    ms.push_back(&m2);
    stack.push_back(&m1);
    stack.push_back(&m2);
    OP(stack,"-",ms);
    stack[0]->print();
    // m1.print();
    // m2.print();
    // (m1 - m2).print();
    delete stack[0];

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

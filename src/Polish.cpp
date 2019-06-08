#include "Polish.h"
#include <iostream>

using namespace std;

static bool isOperator(char ch);
static bool isSingleOperator(char ch);
static bool isNumber(char ch);
static int findIndex(const vector<string>& names, string who);
static void OP(vector<Matrix *>& stack, string op, const vector<Matrix *>& matrices);
static bool exists(const vector<Matrix *>& matrices, Matrix *m);
static void popOperationStack(vector<std::string>& ops, const string& conn, string& result);
static const string getOperation(const string& exp, int& idx);
static const string getMatrix(const string& exp, int& idx);
static const string convertSingleOperation(const string& op);
static void free_matrices(vector<Matrix *>& ms);
static vector<Matrix *> copy(const vector<Matrix *>& m);

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
        /* copy matrices to avoid changing input matrices */
        vector<Matrix *> copyMat = copy(matrices);
        /* transfer matrix must be new one, then 
         * delete matrices in result wouldn't cause error */
        *m = analyseRPN(names,copyMat,exp);
        answers.push_back(m);
        free_matrices(copyMat);
    }
}

Matrix POLISH::analyseRPN(const vector<string>& names, const vector<Matrix *>& matrices, const string exp){
    /* this function will affect input matrix */
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
    /* current letter is operator ? true:yes false:no */
    bool flag;
    /* a binary connective must stand between two matrix */
    bool isMatrixBefore = false;

    /* current index */
    int idx = 0;
    /* current character */
    char ch;
    /* loop to analyse the expression */
    while(idx < len){
        ch = exp.at(idx);
        if(isOperator(ch)){
            buf = getOperation(exp,idx);
            if(!isMatrixBefore){
                buf = convertSingleOperation(buf);
            }
            popOperationStack(ops,buf,result);
            isMatrixBefore = false;
        }
        else{
            buf = getMatrix(exp,idx);
            result.append(buf+" ");
            isMatrixBefore = true;
        }
    }
    /* pop all operation out */
    while(!ops.empty()){
        string cmp = ops[ops.size()-1];
        result.append(cmp+" ");
        ops.pop_back();
    }
    return result;
}

int POLISH::priority(string conn){
    /* binary + and - */
    if(conn == "+" || conn == "-"){
        return 2;
    }
    else if(conn == "*" || conn == "/"){
        return 3;
    }
    else if(conn == "~"){
        return 4;
    }
    /* unary + and - */
    else if(conn == "+++" || conn == "---"){
        return 5;
    }
    else if(conn == "+=" || conn == "-="){
        return 1;
    }
    else{
        return 0;
    }
}

static bool isOperator(char ch){
    return (ch == '+')||(ch == '-')||(ch == '*')||(ch == '/')||(ch == '=')||(ch == '~');
}

static bool isSingleOperator(char ch){
    return (ch == '~')||(ch == '-')||(ch == '+');
}

static bool isNumber(char ch){
    return (ch >= '0')&&(ch <= '9');
}

static int findIndex(const vector<string>& names, string who){
    /* search index of name */
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
    /* operate unary connective */
    Matrix *mat2 = stack[stack.size()-1];
    stack.pop_back();
    if(op == "~"){
        Matrix *mat = new Matrix();
        *mat = ~*mat2;
        stack.push_back(mat);
        if(!exists(matrices,mat2)){
            delete mat2;
        }
        return;
    }
    /* unary - */
    else if(op == "---"){
        Matrix *mat = new Matrix();
        *mat = -*mat2;
        stack.push_back(mat);
        if(!exists(matrices,mat2)){
            delete mat2;
        }
        return;
    }
    /* unary + */
    else if(op == "+++"){
        Matrix *mat = new Matrix();
        *mat = +*mat2;
        stack.push_back(mat);
        if(!exists(matrices,mat2)){
            delete mat2;
        }
        return;
    }
    bool mat1Used = false;
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
    /* delete matrix when used */
    if(!exists(matrices,mat1)&&!mat1Used){
        delete mat1;
    }
    if(!exists(matrices,mat2)){
        delete mat2;
    }
}

static void popOperationStack(vector<std::string>& ops, const string& conn, string& result){
    /* get operation which has lower priority than conn */
    while(!ops.empty()){
        string cmp = ops[ops.size()-1];
        if(POLISH::priority(conn)<=POLISH::priority(cmp)){
            result.append(cmp+" ");
            ops.pop_back();
        }
        else{
            break;
        }
    }
    /* push conn into stack */
    ops.push_back(conn);
}

static const string getOperation(const string& exp, int& idx){
    /* get operation from idx of string */
    int size = exp.size();
    if(idx >= size){
        return "";
    }
    char ch = exp.at(idx);
    idx++;
    if(idx >= size){
        return ""+ch;
    }
    switch(ch){
        case '+':
            ch = exp.at(idx);
            if(ch == '='){
                idx++;
                return "+=";
            }
            else if(ch == '+'){
                idx++;
                return "++";
            }
            else{
                return "+";
            }
            break;
        case '-':
            ch = exp.at(idx);
            if(ch == '='){
                idx++;
                return "-=";
            }
            else if(ch == '-'){
                idx++;
                return "--";
            }
            else{
                return "-";
            }
            break;
        case '*':
            ch = exp.at(idx);
            if(ch == '='){
                idx++;
                return "*=";
            }
            else{
                return "*";
            }
            break;
        case '=':
            ch = exp.at(idx);
            if(ch == '='){
                idx++;
                return "==";
            }
            else{
                return "=";
            }
            break;
        case '~':
            return "~";

        default:
            idx--;
            return "";
    }
}

static const string getMatrix(const string& exp, int& idx){
    /* search next name, may string or number */
    char ch;
    int size = exp.size();
    if(idx >= size){
        return "";
    }
    int start = idx,count = 0;
    ch = exp.at(idx);
    while(idx < size){
        ch = exp.at(idx);
        if(isOperator(ch)){
            break;
        }
        idx++;
        count++;
    }
    return exp.substr(start,count);
}

static const string convertSingleOperation(const string& op){
    if(op == "~"){
        return "~";
    }
    /* unary connective of - */
    else if(op == "-"){
        return "---";
    }
    /* unary connective of + */
    else if(op == "+"){
        return "+++";
    }
    return "";
}

static vector<Matrix *> copy(const vector<Matrix *>& m){
    vector<Matrix *> ret;
    for(Matrix *mptr:m){
        Matrix *mat = new Matrix();
        *mat = *mptr;
        ret.push_back(mat);
    }
    return ret;
}

static void free_matrices(vector<Matrix *>& ms){
    for(Matrix *m:ms){
        delete m;
    }
    ms.clear();
}


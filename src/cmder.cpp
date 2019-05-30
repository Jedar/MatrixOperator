#include "FileUtil.h"
#include "Polish.h"
#include <cstring>

#define PRT(A) std::cout<<A<<std::endl
#define WAIT std::cout<<'>'

static void cmd(const string in, string& out1, string& out2);

static void free_matrices(vector<Matrix *>& ms){
    for(Matrix *m:ms){
        delete m;
    }
    ms.clear();
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

int main(){
    vector<string> names;
    vector<Matrix *> matrices;
    vector<string> exps;
    vector<Matrix *> answers;

    const int BUFSIZE = 500;
    char buf[BUFSIZE];
    string order, argument, expression;

    WAIT;
    while(cin.getline(buf,BUFSIZE)){
        string buffer(buf);
        cmd(buffer,order,argument);
        if(order == "read"){
            FILEUTIL::initMatrixMap(names,matrices,argument);
            for(string name: names){
                cout<<name<<' ';
            }
            cout<<endl;
        }
        else if(order == "calexps"){
            FILEUTIL::initExpressions(exps,argument);
            POLISH::RPN(exps);
            POLISH::analyseRPN(names,matrices,exps,answers);
            cout<<"print answers"<<endl;
            for(Matrix *m:answers){
                m->print();
            }
            exps.clear();
            free_matrices(answers);
        }
        else if(order == "cal"){
            string rpn = POLISH::RPN(argument);
            Matrix mat = POLISH::analyseRPN(names,matrices,rpn);
            PRT(argument);
            mat.print();
        }
        else if(order == "quit" || order == "exit"){
            break;
        }
        else if(order == "print"){
            int idx = findIndex(names,argument);
            if(idx == -1){
                PRT("Matrix "<<argument<<" not found");
            }
            else{
                PRT(argument);
                matrices[idx]->print();
            }
        }
        else if(order == "rpn"){
            string res = POLISH::RPN(argument);
            PRT(res);
        }
        else if(order == "help"){
            PRT("usage:\n1)help: show this message");
            PRT("2)read: read input matrix file\n    read ../data/matrix.in ");
            PRT("3)calexps: read expressions from file and calculate\n    calexps ../data/expression.in");
            PRT("4)cal: calculate expression\n    cal A+B");
            PRT("5)print: print matrix\n    print A");
            PRT("6)rpn: convert expression into Reverse Polish Notation\n    rpn A+~B");
            PRT("7)quit: quit cmder");
            PRT("8)exit: same with quit");
        }
        else{
            PRT(buffer<<":  Cmd error!");
        }
        WAIT;
    }


    free_matrices(matrices);

    free_matrices(answers);
}

static void cmd(const string in, string& out1, string& out2){
    int start = 0,count = 0;
    int size = in.size();
    char ch;
    int i;
    for(i = 0; i < size; i++){
        ch = in.at(i);
        if(ch != ' '){
            count++;
        }
        else{
            out1 = in.substr(start,count);
            count = 0;
            break;
        }
    }
    if(count != 0){
        out1 = in.substr(start,count);
    }
    if(i == size){
        out2 = "";
    }
    else{
        out2 = in.substr(i+1,size - i - 1);
    }
    // PRT(out1<<" "<<out2);
}

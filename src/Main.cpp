#include "FileUtil.h"
#include "Polish.h"

void free_matrices(vector<Matrix *>& ms){
    for(Matrix *m:ms){
        delete m;
    }
    ms.clear();
}

int main(){
    vector<string> names;
    vector<Matrix *> matrices;
    vector<string> exps;
    vector<Matrix *> answers;
    
    FILEUTIL::initMatrixMap(names,matrices,MATR_IN);
    
    FILEUTIL::initExpressions(exps,EXP_IN);

    POLISH::RPN(exps);

    POLISH::analyseRPN(names,matrices,exps,answers);

    cout<<"print answers"<<endl;
    for(Matrix *m:answers){
        m->print();
    }

    FILEUTIL::outputAnswer(answers,RES_OUT);

    free_matrices(matrices);

    free_matrices(answers);
    
    return 0;
}

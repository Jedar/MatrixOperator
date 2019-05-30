#include "FileUtil.h"
#include <iostream>
#include <fstream>

using namespace std;

#define PRT(A) std::cout<<A<<std::endl

void FILEUTIL::initMatrixMap(vector<string>& names, vector<Matrix *>& matrices, string path){
    const int ROW = 3;
    const int COL = 3;
    char buf[SIZE];
    string mat[ROW*COL];
    ifstream is(path);// STR(MATR_IN)
    // assure(is);
    if(!is.is_open()){
        PRT("Open file failed");
        return;
        // exit(1);
    }
    is.getline(buf,SIZE);
    // is.getline(buf,SIZE);
    int number = atoi(buf);

    for(int i = 0; i < number; i++){
        string buffer;
        getline(is,buffer);
        string name(buffer);
        int idx = 0;
        for(int j = 0; j < ROW; j++){
            getline(is,buffer);
            int size = buffer.size();
            int start = 0,count = 0;
            for(int t = 0; t < size; t++){
                if(buffer.at(t) != ' '){
                    count++;
                }
                /* two or more blanks */
                else if(count == 0){
                    start = t+1;
                }
                else{
                    mat[idx++] = buffer.substr(start,count);
                    start = t + 1;
                    count = 0;
                }
            }
            if(count != 0){
                mat[idx++] = buffer.substr(start,count);
            }
        }
        names.push_back(name);
        matrices.push_back(new Matrix(mat));
    }

    is.close();
}

void FILEUTIL::initExpressions(vector<string>& exps, string path){
    ifstream is(path);
    // assure(is);
    if(!is.is_open()){
        PRT("Open file failed");
        return;
        // exit(1);
    }

    string buffer;
    while(getline(is,buffer)){
        exps.push_back(buffer);
    }
    is.close();
}

void FILEUTIL::outputAnswer(const vector<Matrix *>& mat, string path){
    ofstream os(path,ios::out);
    // assure(is);
    if(!os.is_open()){
        PRT("Open file failed");
        return;
        // exit(1);
    }

    for(Matrix *m:mat){
        string msg = m->to_string();
        os.write(msg.c_str(),msg.size());
    }

    os.close();
}


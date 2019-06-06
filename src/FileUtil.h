#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <string>
#include <vector>
#include "Matrix.h"

#define DATA_DIR "../data"
#define MATR_IN DATA_DIR"/testcase_matrix.in"
#define EXP_IN DATA_DIR"/testcase_expression.in"
#define RES_OUT DATA_DIR"/my_result.out"

namespace FILEUTIL{
    /* buffer size */
    static const int SIZE = 1000;

    void initMatrixMap(vector<string>& name, vector<Matrix *>& matrices, string path);

    void initExpressions(vector<string>& exps, string path);

    void outputAnswer(const vector<Matrix *>& mat, string path);
}


#endif//FILE_UTIL_H

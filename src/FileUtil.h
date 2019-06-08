#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <string>
#include <vector>
#include "Matrix.h"

/* default data path */
#define DATA_DIR "../data"
#define MATR_IN DATA_DIR"/matrix.in"
#define EXP_IN DATA_DIR"/expression.in"
#define RES_OUT DATA_DIR"/result.out"

namespace FILEUTIL{
    /* buffer size */
    static const int SIZE = 1000;

    /* initialize map by input file, result store in matrices */
    void initMatrixMap(vector<string>& name, vector<Matrix *>& matrices, string path);

    /* initialize expressions by file, result store in exps */
    void initExpressions(vector<string>& exps, string path);

    /* output matrices in file */
    void outputAnswer(const vector<Matrix *>& mat, string path);
}


#endif//FILE_UTIL_H

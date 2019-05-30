#ifndef POLISH_H
#define POLISH_H

#include <string>
#include <vector>
#include "Matrix.h"

/* Reverse Polish notation,RPN */

namespace POLISH{
    using namespace std;

    void analyseRPN(const vector<string>& names, const vector<Matrix *>& matrices, const vector<string>& exps, vector<Matrix *>& answers);

    Matrix analyseRPN(const vector<string>& names, const vector<Matrix *>& matrices, const string exp);

    void RPN(vector<string>& a);

    string RPN(string exp);

    int priority(string conn);
};

#endif// POLISH_H

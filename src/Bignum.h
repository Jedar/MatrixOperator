#ifndef BIGNUM_H
#define BIGNUM_H

#include <string>
#include <cstdlib>
#include <cstring>

namespace BIGNUM{
    using namespace std;

    static void arr_add(const int *src1, const int *src2, int *dst, int len, int nary);
    static bool arr_subtract(const int *src1, const int *src2, int *dst, int len, int nary, int maxLen);

    class Bignum{
    private:
        /* n-ary to story number */
        static const int NARY = 10000;
        /* byte of each position */
        static const int NARY_LEN = 4;
        /* MAX length of Bignum */
        static const int MAXLEN = 300;
        /* array to story number */
        int arr[MAXLEN];
        /* exact length of Bignum */
        int len;
        /* sign true:+ false:- */
        bool sign;
    public:
        Bignum();

        Bignum(const int& num);

        Bignum(const char* str);

        ~Bignum();

        Bignum(const Bignum& num);

        Bignum(const Bignum& num, bool s);

        const string getVal() const;

        const Bignum& operator+() const;

        const Bignum operator-() const;

        const Bignum& operator=(const Bignum& num);

        const Bignum operator+(const Bignum& num) const;

        const Bignum operator-(const Bignum& num) const;

        const Bignum operator*(const Bignum& num) const;

        const Bignum operator/(const Bignum& num);

        bool operator==(const Bignum& num) const;

        bool operator<(const Bignum& num) const;

        bool operator<=(const Bignum& num) const;

        bool operator>(const Bignum& num) const;

        bool operator>=(const Bignum& num) const;

        const Bignum& operator+=(const Bignum& num);

        const Bignum& operator-=(const Bignum& num);

        const Bignum& operator*=(const Bignum& num);

        const Bignum& operator/=(const Bignum& num);

    };

}

#endif//BIGNUM_H

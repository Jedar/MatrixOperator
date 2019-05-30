#include <iostream>
#include "Bignum.h"

#ifdef DEBUG
#define PRT(A) std::cout<<A<<std::endl
#define EQUAL(A,B) if((A)==(B)) PRT("Success    "<<(A)<<"=="<<(B));else PRT("Failed    "<<(A)<<"=="<<(B))
#else
#define PRT(A)
#define EQUAL(A,B)
#endif

using namespace BIGNUM;

BIGNUM::Bignum::Bignum(){
    memset(arr,0,sizeof(int)*MAXLEN);
    len = 1;
    sign = true;
}

BIGNUM::Bignum::Bignum(const int& num){
    memset(arr,0,sizeof(int)*MAXLEN);
    len = 0;
    int temp;
    if(num >= 0){
        sign = true;
        temp = num;
    }
    else{
        sign = false;
        temp = -num;
    }
    /* tear the number apart
     * like 56489165155 ===> 564//8916//5155*/
    while(temp >= NARY){
        arr[len++] = temp % NARY;
        temp /= NARY;
    }
    arr[len++] = temp;
}

BIGNUM::Bignum::Bignum(const char* str){
    const string num(str);
    /* 10*10*10... */
    int tens = 1;
    /* segment value */
    int segVal = 0;
    len = 0;
    memset(arr,0,sizeof(int)*MAXLEN);

    int size = num.size();
    int end = 0;
    if(num.at(0) == '-'){
        end = 1;
        sign = false;
    }
    else{
        sign = true;
    }
    /* tear the number apart
    * like 56489165155 ===> 564//8916//5155*/
    for(int i = size-1; i >= end; i--){
        char ch = num.at(i);
        int val = ch - '0';
        segVal += val * tens;
        tens *= 10;
        /* check whether length is bigger than nary */
        if(tens == NARY){
            arr[len++] = segVal;
            segVal = 0;
            tens = 1;
        }
    }
    if(segVal != 0){
        arr[len++] = segVal;
    }
}

BIGNUM::Bignum::~Bignum(){
    /* destructor */
}

BIGNUM::Bignum::Bignum(const Bignum& num):len(num.len),sign(num.sign){
    memcpy(arr,num.arr,sizeof(arr));
}

BIGNUM::Bignum::Bignum(const Bignum& num, bool s):len(num.len),sign(s){
    memcpy(arr,num.arr,sizeof(arr));
}

const string BIGNUM::Bignum::getVal() const{
    string str;
    if(!sign){
        str += '-';
    }
    for(int i = len-1; i >= 0; i--){
        str += to_string(arr[i]);
    }
    return str;
}

const Bignum& BIGNUM::Bignum::operator+() const{
    return *this;
};

const Bignum BIGNUM::Bignum::operator-() const{
    return Bignum(*this,!(this->sign));
};

const Bignum& BIGNUM::Bignum::operator=(const Bignum& num){
    /* handle self assignment */
    if(this == &num){
        return *this;
    }
    sign = num.sign;
    len = num.len;
    memcpy(arr,num.arr,sizeof(int)*MAXLEN);
    return *this;
};

const Bignum BIGNUM::Bignum::operator+(const Bignum& num) const{
    Bignum res;
    int length = (len >= num.len)?len:num.len;
    if((sign&&num.sign)||(!sign&&!num.sign)){
        arr_add(arr,num.arr,res.arr,length,NARY);
        res.len = (res.arr[length] == 0)?length:length+1;
        res.sign = sign;
    }
    else{
        bool ret = arr_subtract(arr,num.arr,res.arr,length,NARY,MAXLEN);
        // res.len = length;
        while(length > 1 && res.arr[length-1] == 0){
            length--;
        }
        res.len = length;
        res.sign = (sign)?(ret):(!ret);
    }
    return res;
}

const Bignum BIGNUM::Bignum::operator-(const Bignum& num) const{
    Bignum neg_num(num,!num.sign);
    return *this+neg_num;
}

const Bignum BIGNUM::Bignum::operator*(const Bignum& num) const{
    Bignum res;
    int nary = NARY;
    // printf("%d\n",nary);
    int length = (len >= num.len)?len:num.len;
    // printf("\n%d   %d\n",res.arr[0], res.arr[1]);
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length; j++){
            int mul = arr[i]*num.arr[j];
            int idx = i + j;
            if(mul >= nary){
                res.arr[idx+1] += mul/nary;
                mul = mul%nary;
            }
            res.arr[idx] += mul;
        }
    }
    // printf("\n%d   %d\n",res.arr[0], res.arr[1]);
    int i;
    /* search length */
    for(i = len+num.len; i > 0 ; i--){
        if(res.arr[i] != 0){
            break;
        }
    }
    res.len = i + 1;
    /* check is there overflow elements */
    int carryBit = 0;
    for(i = 0; i < res.len; i++){
        res.arr[i] += carryBit;
        if(res.arr[i] >= nary){
            carryBit = res.arr[i] / nary;
            res.arr[i] = res.arr[i] % nary;
        }
        else{
            carryBit = 0;
        }
    }
    if(carryBit != 0){
        res.arr[res.len++] = carryBit;
    }
    res.sign = !(sign^num.sign);

    return res;
}

const Bignum BIGNUM::Bignum::operator/(const Bignum& num){
    return Bignum(num);
}

bool BIGNUM::Bignum::operator==(const Bignum& num) const {
    bool flag = (sign == num.sign)&&(len == num.len);
    if(!flag){
        return false;
    }
    for(int i = 0; i < len; i++){
        if(arr[i] != num.arr[i]){
            return false;
        }
    }
    return true;
}

bool BIGNUM::Bignum::operator<(const Bignum& num) const {
    // printf("\nthis:%s  num:%s\n",this->getVal().c_str(),num.getVal().c_str());
    if(sign && !num.sign){
        return false;
    }
    else if(!sign && num.sign){
        return true;
    }
    else if(sign && num.sign){
        if(len > num.len){
            return false;
        }
        else if(len < num.len){
            return true;
        }
        else{
            return (num.arr[len-1] > arr[len-1]);
        }
    }
    else{
        if(len > num.len){
            return true;
        }
        else if(len < num.len){
            return false;
        }
        else{
            return (num.arr[len-1] < arr[len-1]);
        }
    }
}

bool BIGNUM::Bignum::operator<=(const Bignum& num) const {
    return (*this<num)||(*this==num);
}

bool BIGNUM::Bignum::operator>(const Bignum& num) const {
    return !(*this<=num);
}

bool BIGNUM::Bignum::operator>=(const Bignum& num) const {
    return (*this>num)||(*this==num);
}

const Bignum& BIGNUM::Bignum::operator+=(const Bignum& num){
    *this = *this+num;
    return *this;
}

const Bignum& BIGNUM::Bignum::operator-=(const Bignum& num){
    *this = *this - num;
    return *this;
}

const Bignum& BIGNUM::Bignum::operator*=(const Bignum& num){
    *this = *this * num;
    return *this;
}

const Bignum& BIGNUM::Bignum::operator/=(const Bignum& num){
    return num;
}

static void BIGNUM::arr_add(const int *src1, const int *src2, int *dst, int len, int nary){
    int res,carryBit = 0;
    int i;
    for(i = 0; i < len; i++){
        res = src1[i] + src2[i] + carryBit;
        if(res >= nary){
            carryBit = 1;
            res -= nary;
        }
        else{
            carryBit = 0;
        }
        dst[i] = res;
    }
    dst[i] = carryBit;
}

static bool BIGNUM::arr_subtract(const int *src1, const int *src2, int *dst, int len, int nary ,int maxLen){
    bool flag = (src1[len-1] >= src2[len-1]);
    const int *src;
    if(flag){
        memcpy(dst,src1,sizeof(int)*maxLen);
        src = src2;
    }
    else{
        memcpy(dst,src2,sizeof(int)*maxLen);
        src = src1;
    }
    for(int i = len-1; i >= 0; i--){
        dst[i] -= src[i];
        if(dst[i]<0){
            dst[i+1]--;
            dst[i] += nary;
        }
    }
    return flag;
}

#ifdef DEBUG
int main(){
    /* test constructor */
    PRT("test constructor");
    Bignum num(123);
    Bignum num1(123456);
    Bignum num2("1234");
    Bignum num3("1234567");
    Bignum num4(-123456);
    Bignum num5("-1234569");

    EQUAL(num.getVal(),"123");
    EQUAL(num1.getVal(),"123456");
    EQUAL(num2.getVal(),"1234");
    EQUAL(num3.getVal(),"1234567");
    EQUAL(num4.getVal(),"-123456");
    EQUAL(num5.getVal(),"-1234569");
    /*  */
    PRT("test copy constructor");
    Bignum num6 = 12345678;
    Bignum num7 = "-894568465478894651651651";
    EQUAL(num6.getVal(),"12345678");
    EQUAL(num7.getVal(),"-894568465478894651651651");

    /* test assign */
    PRT("test assign");
    Bignum num8;
    EQUAL(num8.getVal(),"0");
    num8 = num7;
    EQUAL(num8.getVal(),"-894568465478894651651651");

    /* test unary connective */
    PRT("test unary connective");
    Bignum num9("1234567984651651");
    num9 = -num9;
    EQUAL(num9.getVal(),"-1234567984651651");
    num9 = +num9;
    EQUAL(num9.getVal(),"-1234567984651651");
    num9 = -num9;
    EQUAL(num9.getVal(),"1234567984651651");

    /* test binary connective */
    PRT("test binary connective");
    Bignum num10("123456");
    Bignum num11("-1234568");
    Bignum num12("564845");
    Bignum num13("-89544");
    Bignum temp1("0");
    Bignum temp2("9999999999");
    EQUAL((num10+num12).getVal(),to_string(123456+564845));
    EQUAL((num13+num11).getVal(),to_string(-89544-1234568));
    EQUAL((num10+num11).getVal(),to_string(123456-1234568));
    EQUAL((num12-num10).getVal(),to_string(564845-123456));
    EQUAL((temp1*temp2).getVal(),to_string(0*9999999999));
    EQUAL((num12*num10).getVal(),to_string(564845l*123456l));
    EQUAL((num10*num11).getVal(),to_string(123456l*(-1234568l)));
    EQUAL((num13*num11).getVal(),to_string((-89544l)*(-1234568l)));

    /* test compare operation */
    PRT("test compare operation");
    EQUAL(num10>num11,true);
    EQUAL(num11==-1234568,true);
    EQUAL(num13<num12,true);
    EQUAL(num11>0,false);
    EQUAL((num11>=num12),false);
    EQUAL(num12>=num10,true);

    /* test operation assignment */
    PRT("test operation assignment");
    Bignum num14(123456);
    num14 += 111111;
    EQUAL(num14.getVal(),"234567");
    num14 -= 1000000;
    EQUAL(num14.getVal(),to_string(-1000000+234567));
}
#endif

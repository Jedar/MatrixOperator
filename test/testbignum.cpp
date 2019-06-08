#include "../src/Bignum.h"
#include <iostream>

using namespace BIGNUM;

#ifdef DEBUG
#define PRT(A) std::cout<<A<<std::endl
#define EQUAL(A,B) if((A)==(B)) PRT("Success    "<<(A)<<"=="<<(B));else PRT("Failed    "<<(A)<<"=="<<(B))
#else
#define PRT(A)
#define EQUAL(A,B)
#endif

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

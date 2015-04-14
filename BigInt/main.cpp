/* 
 * File:   main.cpp
 * Author: jeremydaigneau
 *
 * Created on April 10, 2015, 6:46 PM
 */

#include <cstdlib>
#include "Bigint.h"
using namespace std;

/*
 * 
 */
int main()
{
    /*
BigInt a("-1000");
BigInt b("+999");
cout << b << "+" << a << endl << "= " << b+a << endl;
a = BigInt("1000");
b = BigInt("999");
cout << a << "-" << b << endl << "= " << a - b << endl;
a = BigInt("99999999999999999999999999999999999999999999999999999999999999999999999999999999");
b = BigInt("1");
cout << " " << a << "+" << b << endl << "= " << a+b << endl;
cout << "Expecting 1, got: " << (BigInt("-30") < BigInt("-1")) << endl;
cout << "Expecting 0, got: " << (BigInt("30") < BigInt("-1")) << endl;
cout << "Expecting 1, got: " << (BigInt("30") < BigInt("300")) << endl;
cout << "Expecting 0, got: " << (BigInt("-30") < BigInt("-300")) << endl;
    
   */
    BigInt a(1111);
    BigInt b(-1111);
    
    if( a == b)
        cout << "They do equal" << endl;
    
    else
        cout << "They don't equal" << endl;
    return 0;
}


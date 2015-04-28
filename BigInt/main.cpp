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
    
   BigInt a(150);
   BigInt b(2);

   cout << a/b << endl;
   
return 0;
}

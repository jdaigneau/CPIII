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
    //TEST 1//
	cout << "Test 1:" << endl;
	BigInt a("-1000");
	BigInt b("+999");
	cout << b << "+" << a << endl << "= " << b + a << endl;
	cout << "expecting: " << -1 << "\n\n";


	//TEST 2//
	cout << "Test 2:" << endl;
	a = BigInt("1000");
	b = BigInt("999");
	cout << a << "-" << b << endl << "= " << a - b << endl;
	cout << "expecting: " << 1 << "\n\n";


	//TEST 3//
	cout << "Test 3:" << endl;
	a = BigInt("99999999999999999999999999999999999999999999999999999999999999999999999999999999");
	b = BigInt("1");
	cout << " " << a << "+" << b << endl << "= " << a + b << endl;


	//TEST 4//
	cout << "Test 4:" << endl;
	a = BigInt("-500");
	b = BigInt("-500");
	cout << " " << a << "+" << b << endl << "= " << a + b << endl;
	cout << "expecting: " << -1000 << "\n\n";


	//TEST 5//
	cout << "Test 5:" << endl;
	a = BigInt("-500");
	b = BigInt("-501");
	cout << " " << a << "-" << b << endl << "= " << a - b << endl;
	cout << "expecting: " << 1 << "\n\n";


	//TEST 6//
	cout << "Test 6:" << endl;
	a = BigInt("-999");
	b = BigInt("-1");
	cout << " " << a << "+" << b << endl << "= " << a + b << endl;
	cout << "expecting: " << -1000 << "\n\n";


	//TEST 7//
	cout << "Test 7:" << endl;
	a = BigInt("-999");
	b = BigInt("-1");
	cout << " " << a << "+" << b << endl << "= " << a - b << endl;
	cout << "expecting: " << -998 << "\n\n";
	

	//TEST 8//
	cout << "Test 8:" << endl;
	cout << "Expecting 1, got: " << (BigInt("-30") < BigInt("-1")) << endl;
	cout << "Expecting 0, got: " << (BigInt("30") < BigInt("-1")) << endl;
	cout << "Expecting 1, got: " << (BigInt("30") < BigInt("300")) << endl;
	cout << "Expecting 0, got: " << (BigInt("-30") < BigInt("-300")) << endl;
/*
    BigInt a(8);
    BigInt b(2);
    
    cout << a/b << endl;
  */  
return 0;
}

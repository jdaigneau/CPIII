/* 
 * File:   Bigint.h
 * Author: jeremydaigneau
 *
 * Created on April 10, 2015, 7:54 PM
 */

#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>

using namespace std;

class BigInt
{
public:
	BigInt();					// Initializes the BigInt to zero.
	BigInt(int x);				//Initializes the BigInt to have the same value as x
	explicit BigInt(string x);	//Initalizes the BigInt to have the value of the given string BUT must check that the string is valid or exit(1) otherwise.

	friend BigInt operator+(const BigInt& left, const BigInt& right);
	friend BigInt operator-(const BigInt& left, const BigInt& right);
	friend bool operator<(const BigInt& left, const BigInt& right);
								
	friend ostream& operator<<(ostream& out, const BigInt& right);

private:

	BigInt addHelper(BigInt& left, BigInt& right);
	BigInt subHelper(BigInt& left, BigInt& right);
	friend bool magnitude(const BigInt& left, const BigInt& right);
	string data;
	bool isNegative;
};

#endif



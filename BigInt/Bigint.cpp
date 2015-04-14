#include "Bigint.h"

bool isNum(char c);

BigInt::BigInt()
{
	data = "0";
	isNegative = false;
}

BigInt::BigInt(int x)
{
	if (x < 0)
            isNegative = true;

	else isNegative = false;

	data = to_string(abs(x));
	
}

BigInt::BigInt(string x)
{
	data = "";
	bool invalid = false;

	int start = x.find_first_not_of(" ");

	if (x[start] == '-')
	{
		start++ ;
		isNegative = true;
	}

	else if (x[start] == '+')
            start++;

        else if (isNum(x[start]))
            isNegative = false;
        
	else invalid = true;
        
        if(x.length() - 1 > 1)
        {
            if (!isNum(x[start + 1]))
                invalid = true;
            
        }
        
	for (int i = start; i < x.length(); i++)
	{
		if (isNum(x[i]))
		{
			data += x[i];
			continue;
		}

		if (x[i] != ' ')
			invalid = true;

		break;
	}

	if (invalid)
	{
		cout << "Value " << x << " is invalid" << endl;
		exit(1);
	}
	
}

ostream& operator<<(ostream& out, const BigInt& right)
{
	if (right.isNegative) out << '-';
	out << right.data;

	return out;
}

BigInt operator+(const BigInt& left, const BigInt& right)
{
	BigInt newLeft, newRight, answer;
        
	newLeft.data = left.data;
	newRight.data = right.data;
        
	if (left.isNegative == right.isNegative)
	{
		answer = newLeft.addHelper(newLeft, newRight);
		answer.isNegative = left.isNegative;
	}

	else if (right.isNegative)
        {
            if(left.magnitude(newLeft, newRight))
            {
                answer = newLeft.subHelper(newLeft, newRight);
                answer.isNegative = false;
            }
            else 
            {
                answer = newLeft.subHelper(newRight, newLeft);
                answer.isNegative = true;
            }    
        }
		
        else
        {
            if(left.magnitude(newRight, newLeft))
            {
                answer = newLeft.subHelper(newRight, newLeft);
                answer.isNegative = false;
            }
            else 
            {
                answer = newLeft.subHelper(newLeft, newRight);
                answer.isNegative = true;
            }
        }
	return answer;
}

BigInt operator-(const BigInt& left, const BigInt& right)
{
	BigInt newLeft, newRight, answer;
	
	newLeft.data = left.data;
	newRight.data = right.data;

	if (!left.isNegative && !right.isNegative)
        {   
            if(left.magnitude(newLeft, newRight))
            {   
		answer = newLeft.subHelper(newLeft, newRight);
                answer.isNegative = false;
            }
            else 
            {
                answer = newLeft.subHelper(newRight, newLeft);
                answer.isNegative = true;
            }    
        } 
        
        else if( left.isNegative && right.isNegative)
        {   
            answer = newLeft.addHelper(newLeft, newRight);
            answer.isNegative = true;
        }
        
        else if( left.isNegative && !right.isNegative)
        {
            if(left.magnitude(newLeft, newRight))
            {
                answer = newLeft.addHelper(newLeft, newRight);
                answer.isNegative = true;
            }
            
            else
            { 
                answer = newLeft.subHelper(newLeft, newRight);
                answer.isNegative = false;
            }
        }
        else
        {
            if(left.magnitude(newRight,newLeft))
            {
                answer = newLeft.addHelper(newRight, newLeft);
                answer.isNegative = false;
            }
            
            else
            {cout << "dont go here8" << endl;
                answer = newLeft.addHelper(newLeft, newRight);
                answer.isNegative = false;
            }
        }
	return answer;
}
bool operator<(const BigInt& left, const BigInt& right)
{
        BigInt newLeft, newRight;
        
        newLeft.data = left.data;
        newRight.data = right.data;
        
	if (right.isNegative && !left.isNegative)
		return false;

	if (left.isNegative && !right.isNegative)
		return true;

	if (!left.isNegative && !right.isNegative)
	{
            if (newLeft.magnitude(newLeft, newRight))     
                return false;
              
            else return true;
        }
        
        if (left.isNegative && right.isNegative)
        {
            if (newLeft.magnitude(newLeft, newRight))
                return true;
            
            else return false;
        }
        return false;
}

bool operator>(const BigInt& left, const BigInt& right)
{
    BigInt newLeft, newRight;
    
    newLeft.data = left.data;
    newRight.data = right.data;
    
    if(!left.isNegative && !right.isNegative)
    {
        if(left.magnitude(newLeft, newRight))
            return true;
        
        return false;
    }
    
    if(left.isNegative && right.isNegative)
    {
        if(left.magnitude(newLeft, newRight))
            return false;
   
        return true;
    }
    
    if( left.isNegative && !right.isNegative)
        return false;
        
    else return true;
}

bool operator==(const BigInt& left, const BigInt& right)
{
    BigInt newLeft, newRight;
    
    newLeft.data = left.data;
    newRight.data = right.data;
    
    if ((left.data.length() != right.data.length()) || (left.isNegative != right.isNegative))
            return false;
    
    else
    {
        for (int i = 0; i < left.data.length(); i++)
        {
            if (newLeft.data[i] != newRight.data[i])
                return false;
        }
        return true;
    }
}
BigInt BigInt::addHelper(BigInt& left, BigInt& right)
{
	int digit1, digit2, over = 0, i = 0;
	BigInt answer;
	answer.data = "";
	
	while ((i < left.data.length()) && (i < right.data.length()))
	{
		digit1 = left.data[left.data.length() - i - 1] - '0';
		digit2 = right.data[right.data.length() - i - 1] -'0';

		answer.data.push_back(((digit1 + digit2 + over)%10) + '0');
		
		over = (digit1 + digit2) / 10;
		
		i++;
	}
	
	while (i < left.data.length())
	{
		digit1 = left.data[left.data.length() - i - 1] - '0';

		answer.data.push_back(((digit1 + over)%10) + '0');
		over = (digit1 + over)/10;
		i++;
	}
	
	while (i < right.data.length())
	{
		digit1 = right.data[right.data.length() - i - 1] - '0';

		answer.data.push_back(((digit1 + over)%10) + '0');
		over = (digit1 + over)/10;
		i++;
	}
        
        if( over != 0)
            answer.data.push_back(over + '0');
        
        answer.stringFlip();
	return answer;
}

BigInt BigInt::subHelper(BigInt& left, BigInt& right)
{
	int digit1, digit2, over = 0, i = 0;
	BigInt answer;
	answer.data = "";

	while ((i < left.data.length()) && (i < right.data.length()))
	{
		digit1 = left.data[left.data.length() - i - 1] - '0';
		digit2 = right.data[right.data.length() - i - 1] - '0';
                
		if (digit1 - digit2 + over < 0)
		{
                    answer.data.push_back(digit1 - digit2 + over + 10 + '0');
                    over = -1;

		}

		else
		{
			answer.data.push_back(digit1 - digit2 + over + '0');
                        over = 0;
		}
		i++;
	}

	while (i < left.data.length())
	{
		digit1 = left.data[left.data.length() - i - 1] - '0';
              
		answer.data.push_back((((digit1 + over) + 10)%10) + '0');
               
		over = 0;
		i++;
	}

	while (i < right.data.length())
	{
		digit1 = right.data[right.data.length() - i - 1] - '0';
               
		answer.data.push_back((((digit1 + over) + 10)%10) + '0');
                
		over = 0;
		i++;
	}
        
        
        answer.stringFlip();
	return answer;
}

bool BigInt::magnitude(BigInt& left, BigInt& right) const
{
	if (left.data.length() == right.data.length())
	{   
		for (int i = 0; i < left.data.length(); i++)
		{       
			if (left.data[i] != right.data[i])
                        {
                            if (left.data[i] > right.data[i])
                                return true;
                            
                            else return false;
                            
                        }   

		}
                return false;
	}

	else if (left.data.length() > right.data.length())
		return true;

	else
		return false;
        
        return false;
}

void BigInt:: stringFlip()
{
    string temp;
    temp.resize(data.length(), '0');
    
    for( int i = 0; i < data.length(); i++)
        temp[i] = data[data.length() - i  - 1];
    
    data = temp;
}
bool isNum(char c)
{
	return (c >= '0' && c <= '9');
}

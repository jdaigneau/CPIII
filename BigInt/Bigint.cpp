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
    int start = 0;
     BigInt temp;
     temp.data = right.data;
     
     for (int i = 0; i < temp.data.length(); i++)
     {
         if (temp.data[i] == '0')
             start++;
         
         else break;
     }
     
    if (right.isNegative) out << '-';
	
     for (int i = start; i < temp.data.length(); i++)
         out << temp.data[i];
    
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
            if(left.magnitude(newLeft, newRight))
            {  
                answer = newLeft.subHelper(newLeft, newRight);
                answer.isNegative = true;
            }
            
            else
            {
                answer = newLeft.subHelper(newRight, newRight);
                answer.isNegative = false;
            }
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
            {
                answer = newLeft.addHelper(newLeft, newRight);
                answer.isNegative = false;
            }
        }
	return answer;
}
BigInt operator*(const BigInt& left, const BigInt& right)
{
    BigInt newLeft, newRight, temp, temp2, answer;
    temp2.data = "";
    int digit1, digit2, over, count = 0; 
    
    newLeft.data = left.data;
    newRight.data = right.data;
    
    if(left.isNegative == right.isNegative)
        answer.isNegative = false;
    
    else answer.isNegative = true;
    
    for (int i = left.data.length() - 1; i >= 0; i--)
    {  
        over = 0;
        temp.data = "";
        digit1 = newLeft.data[i] - '0';
        
        for ( int j = right.data.length() - 1; j >= 0; j--)
        {
            digit2 = newRight.data[j] - '0';
            temp.data.push_back(((digit1 * digit2 + over)%10) + '0');
            over = (digit1 * digit2 + over)/10;
           
        }
       
        if( over != 0)
            temp.data.push_back(over + '0');
        
        temp.stringFlip();
        
        for (int k = count; k > 0; k--)
        {   
            temp.data.push_back('0');
        }
        
        temp2 = temp + temp2;
        
        count++;
    }
 
    answer.data = temp2.data;
    return answer;
}

BigInt operator/(const BigInt& left, const BigInt& right)
{
    BigInt dividend, divisor, answer, temp;
    int j = 0;
    
    temp.data = "";
    dividend.data = left.data;
    divisor.data = right.data;
    
    if( divisor > dividend)
    {
        answer.data.push_back('0');
        return answer;
    }
    if(left.isNegative == right.isNegative)
        answer.isNegative = false;
    
    else answer.isNegative = true;
    
    for ( int i = divisor.data.length() - 1; i >= 0; i--)
        temp.data.push_back(dividend.data[i]);
    
   // cout << "Temp is " << temp << endl;
    for (int i = dividend.data.length() - divisor.data.length(); i < dividend.data.length(); i++ )
    {
        while ((temp > divisor) || (temp == divisor))
        {
            cout << "Temp is " << temp << endl;
            cout << "divisor is " << divisor << endl;
            temp = temp - divisor;
            j++;
        }
        cout << "J is " << j << endl;
        answer.data.push_back(j + '0');
        temp.data.push_back(dividend.data[i + divisor.data.length()]);
        //cout << "Temp is " << temp << endl;
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
                
		over = (digit1 + digit2 + over) / 10;
		
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

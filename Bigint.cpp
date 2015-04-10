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
	if (isNegative)
		cout << "I'm negative!" << endl;
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
		//|| isNum(x[start]))
		start++;

	else invalid = true;

	if (!isNum(x[start + 1]))
		invalid = true;

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
	cout << x[start] << endl;
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

	else if (magnitude(newLeft, newRight))
		answer = newLeft.subHelper(newLeft, newRight);
		
	return answer;
}

BigInt operator-(const BigInt& left, const BigInt& right)
{
	BigInt newLeft, newRight, answer;
	
	newLeft.data = left.data;
	newRight.data = right.data;

	if (left.isNegative == right.isNegative)
		answer = newLeft.subHelper(newLeft, newRight);

	return answer;
}
bool operator<(const BigInt& left, const BigInt& right)
{
	int	length1 = left.data.length();
	int length2 = right.data.length();
	int y = 0;

	if (!isNum(right.data[0]))
		length2 -= 1;

	if (!isNum(left.data[0]))
		length1 -= 1;

	if (right.isNegative && !left.isNegative)
		return false;

	if (left.isNegative && !right.isNegative)
		return true;

	if (left.isNegative == right.isNegative)
	{
		if (length1 < length2)
			return true;

		if (length2 < length1)
			return false;

		if (length1 == length2)
		{
			for (int i = 0; i < length1; i++)
			{
				if (!isNum(left.data[i]) || !isNum(right.data[i]))
					continue;
				 
				if (left.data[i] != right.data[i])
				{
					y = i;
					break;
				}
			}
			return left.data[y] < right.data[y];
		}
		
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
		cout << answer.data[i]  << endl;
		cout << "Over is " << over << endl;
		i++;
	}
	
	while (i < left.data.length())
	{
		digit1 = left.data[left.data.length() - i - 1] - '0';

		answer.data.push_back(digit1 + over + '0');
		over = 0;
		i++;
	}
	
	while (i < right.data.length())
	{
		digit1 = right.data[right.data.length() - i - 1] - '0';

		answer.data.push_back(digit1 + over + '0');
		over = 0;
		i++;
	}

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
			answer.data.push_back(digit1 - digit2 + over + 10);
			over = -1;

		}

		else
		{
			answer.data.push_back(digit1 - digit2 + over);
			over = 0;
		}
		i++;
	}

	while (i < left.data.length())
	{
		digit1 = left.data[left.data.length() - i - 1] - '0';

		answer.data.push_back(digit1 + over + '0');
		over = 0;
		i++;
	}

	while (i < right.data.length())
	{
		digit1 = right.data[right.data.length() - i - 1] - '0';

		answer.data.push_back(digit1 + over + '0');
		over = 0;
		i++;
	}

	return answer;
}

bool magnitude(const BigInt& left, const BigInt& right)
{
	if (left.data.length() == right.data.length())
	{
		for (int i = 0; i < left.data.length(); i++)
		{
			if (left.data[i] != right.data[i])
				return left.data[i] > right.data[i];

			else i++;

		}
	}

	else if (left.data.length() > right.data.length())
		return true;

	else
		return false;
}
bool isNum(char c)
{
	return (c >= '0' && c <= '9');
}

#include "Bigint.h"

bool isNum(char c);

BigInt::BigInt()
{
	data = '0';
	isNegative = false;
}

BigInt::BigInt(int x)
{
	data = to_string(x);

	if (x < 0)
		isNegative = true;

	else isNegative = false;
}

BigInt::BigInt(string x)
{
	data = "";
	bool invalid = false;

	int start = x.find_first_not_of(" ");

	if (x[start] == '-')
	{
		//x[start] = x[start + 1];
		isNegative = true;
	}

	else if (x[start] == '+' || isNum(x[start]))
		isNegative = false;

	else invalid = true;

	if (!isNum(x[start + 1]))
		invalid = true;

	for (int i = start + 1; i < x.length(); i++)
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
	int	length1 = left.data.length() - 1;
	int length2 = right.data.length() - 1;
	int over = 0;
	char temp;
	BigInt newLeft, newRight, answer;
	int size = newLeft.data.size();
	newLeft.data.resize(size + (length1 + 1), 0);
	newRight.data.resize(size + (length1 + 1), 0);
	answer.data.resize(size + (length1 + 1), 0);
	
	newLeft.data = left.data;
	newRight.data = right.data;
	
	if ((!left.isNegative && !right.isNegative) || left.isNegative && right.isNegative)
	{
		if (length1 == length2)
		{

			for (int i = length1; i >= 0; i--)
			{
				temp = (newLeft.data[i]) + (newRight.data[i]) + over;

				answer.data[i] = temp - '0';

				if (answer.data[i] > '9')
				{
					answer.data[i] -= 10;
					over = 1;
				}

				else over = 0;
			}

		}
	}
	if (right.isNegative)
	{
		cout << "Wat." << endl;
		//int carry;
		if (length1 < length2)
		{
			for (int i = length1 + 1; i >= 0; i--)
			{
				if (newLeft.data[i] < newRight.data[i])
				{
					newLeft.data[i] += 1;
					newRight.data[i - 1] -= 1;
				}
				cout << newRight.data[i] << endl;
				temp = left.data[i] - right.data[i];
				//cout << temp << endl;
				answer.data = temp -'0';
			}
		}
	}
	return answer;
}

BigInt operator-(const BigInt& left, const BigInt& right)
{
	int	length1 = left.data.length() - 1;
	int length2 = right.data.length() - 1;

	BigInt newLeft, newRight, answer;
	int size = newLeft.data.size();
	newLeft.data.resize(size + (length1 + 1), 0);
	newRight.data.resize(size + (length2 + 1), 0);
	answer.data.resize(size + (length1 + 1), 0);

	newLeft.data = left.data;
	newRight.data = right.data;
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

	if (!left.isNegative && !right.isNegative)
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

	if (left.isNegative && right.isNegative)
	{
		
		if (length1 < length2)
			return false;

		if (length2 < length1)
			return true;

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
			
		}
		return left.data[y] > right.data[y];
	}
	
}

BigInt BigInt::addHelper(BigInt& left, BigInt& right)
{
	int digit1, digit2, over = 0, i = 0;
	BigInt answer;
	answer.data = "";

	while ((i < left.data.length()) && (i < right.data.length()))
	{
		digit1 = left.data[i];
		digit2 = right.data[i];

		answer.data.push_back(((digit1 + digit2 + over)%10) - '0');
		over = (digit1 + digit2) / 10;
		i++;
	}

	while (i < left.data.length())
	{
		digit1 = left.data[i];

		answer.data.push_back(((digit1) % 10) - '0');
		i++;
	}

	while (i > right.data.length())
	{
		digit1 = right.data[i];

		answer.data.push_back(((digit1)%10) - '0');
		i++;
	}

	return answer;
}

bool isNum(char c)
{
	return (c >= '0' && c <= '9');
}

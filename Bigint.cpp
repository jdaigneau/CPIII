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
	string newData;
	BigInt newBig;

	int size = newBig.data.size();
	newBig.data.resize(size + (length1 + 1), 0);
	
	if ((!left.isNegative && !right.isNegative) || left.isNegative && right.isNegative)
	{
		if (length1 == length2)
		{

			for (int i = length1; i >= 0; i--)
			{
				temp = (left.data[i]) + (right.data[i]) + over;

				newBig.data[i] = temp - '0';

				if (newBig.data[i] > '9')
				{
					newBig.data[i] -= 10;
					over = 1;
				}

				else over = 0;
			}

		}
	}
	if (left.isNegative && right < left )
	{
		//int carry;
		if (length1 == length2)
		{
			for (int i = length1; i >= 0; i--)
			{
				//if (left.data[i] < right.data[i])
				//{
				//	left.data[i] += 1;
					//right.data[i - 1] -= 1;
			//	}

				temp = left.data[i] - right.data[i];
				cout << temp << endl;
				newBig = temp - '0';
			}
		}
	}
	return newBig;
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

bool isNum(char c)
{
	return (c >= '0' && c <= '9');
}

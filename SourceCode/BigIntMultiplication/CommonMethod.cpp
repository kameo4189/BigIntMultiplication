#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "CommonMethod.h"
using namespace std;

void GetBaseFromFile(string fileName)
{
	ifstream fin(fileName, ios::in);
	while (!fin.eof())
	{
		string line;
		fin >> line;
		if (line == BASE_CONFIG_NAME)
		{
			string strBase;
			fin >> strBase;
			InitializeBaseConfig(stoul(strBase));
		}
	}
	fin.close();
}

void InitializeBaseConfig(unsigned int base)
{
	BASE = base;
	INVERT_BASE = 1.0 / BASE;
	string strBase = to_string(base);
	NDIGIT = strBase.size() - 1;
}

void PrintBigInt(vector<unsigned int>& digits, unsigned int nDigit)
{
	cout << ConvertBigIntToString(digits, nDigit);
}

string ConvertBigIntToString(vector<unsigned int>& digits, unsigned int nDigit)
{
	string result;
	for (int i = digits.size() - 1; i >= 0; i--)
	{
		string strDigit = to_string(digits[i]);
		if (i != digits.size() - 1)
		{
			while (strDigit.size() < nDigit)
			{
				strDigit.insert(strDigit.begin(), '0');
			}
		}
		result += strDigit;
	}
	return result;
}

void NormalizeBigInt(vector<unsigned int>& digits, unsigned int base, double invertBase)
{
	size_t size = digits.size();
	unsigned int carry = 0;

	for (size_t i = 0; i < size; ++i)
	{
		unsigned int x = digits[i] + carry;
		carry = static_cast<unsigned int>(floor(x * invertBase));
		digits[i] = x - carry * base;
	}

	if (carry != 0)
	{
		while (carry != 0)
		{
			digits.resize(size + 1);
			unsigned int x = carry;
			carry = static_cast<unsigned int>(floor(x * invertBase));
			digits[size] = x - carry * base;
		}
	}
	else
	{
		while (digits.size() > 0 && digits.back() == 0)
		{
			digits.pop_back();
		}
	}
}

void PrintComplexVector(vector<complex<double>>& inputs)
{
	for (size_t i = 0; i < inputs.size(); ++i)
	{
		cout << inputs[i] << " ";
	}
}

void MultipyComplexVector(vector<complex<double>>& leftMultiplier, vector<complex<double>>& rightMultiplier)
{
	for (size_t i = 0; i < leftMultiplier.size(); ++i)
	{
		leftMultiplier[i] *= rightMultiplier[i];
	}
}

void NormalizeSize(size_t inputSize, size_t& outputSize)
{
	outputSize = 1;
	while (outputSize < inputSize) outputSize <<= 1;
}

unsigned int CountBitFromSize(size_t size)
{
	unsigned int bitNum = 0;
	while (size != 1)
	{
		size >>= 1;
		bitNum++;
	}
	return bitNum;
}

size_t ReverseBit(unsigned int bitNum, size_t input)
{
	unsigned int count = bitNum;
	size_t revBitOutput = 0;
	while (input > 0)
	{
		revBitOutput <<= 1;
		revBitOutput |= input & 1;
		input >>= 1;
		count--;
	}
	revBitOutput <<= count;
	return revBitOutput;
}

void ReadBigIntFromString(string stringOfNumber, unsigned int nDigit, vector<unsigned int>& digits)
{
	digits.clear();
	if (stringOfNumber.size() < nDigit)
	{
		string digitString = stringOfNumber.substr(0, nDigit);
		digits.push_back(stoul(digitString));
		return;
	}

	int i = stringOfNumber.size() - nDigit;
	for (; i >= 0; i -= nDigit)
	{
		string digitString = stringOfNumber.substr(i, nDigit);
		digits.push_back(stoul(digitString));
		if (i > 0 && int(i - nDigit) < 0)
		{
			digitString = stringOfNumber.substr(0, i);
			digits.push_back(stoul(digitString));
		}
	}
}

void ReadBigIntFromFile(vector<unsigned int>& leftMultiplier, vector<unsigned int>& rightMultiplier, unsigned int nDigit, string fileName)
{
	ifstream fin(fileName, ios::in);

	string strLeftMultiplier;
	fin >> strLeftMultiplier;
	string strRightMultiplier;
	fin >> strRightMultiplier;

	ReadBigIntFromString(strLeftMultiplier, nDigit, leftMultiplier);
	ReadBigIntFromString(strRightMultiplier, nDigit, rightMultiplier);
}

void ReadMultiBigIntFromFile(vector<vector<unsigned int>>& leftMultipliers, vector<vector<unsigned int>>& rightMultipliers, unsigned int nDigit, string fileName)
{
	ifstream fin(fileName, ios::in);

	leftMultipliers.clear();
	rightMultipliers.clear();
	while (!fin.eof())
	{
		string strLeftMultiplier;
		fin >> strLeftMultiplier;
		string strRightMultiplier;
		fin >> strRightMultiplier;

		vector<unsigned int> leftMultiplier;
		ReadBigIntFromString(strLeftMultiplier, nDigit, leftMultiplier);
		leftMultipliers.push_back(leftMultiplier);

		vector<unsigned int> rightMultiplier;
		ReadBigIntFromString(strRightMultiplier, nDigit, rightMultiplier);
		rightMultipliers.push_back(rightMultiplier);
	}
	fin.close();
}
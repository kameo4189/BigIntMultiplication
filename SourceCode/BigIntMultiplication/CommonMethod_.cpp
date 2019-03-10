#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "CommonMethod.h"
using namespace std;

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

void PrintBigInt(vector<unsigned int>& digits, unsigned int nDigit)
{
	for (int i = digits.size() - 1; i >= 0 ; i--)
	{
		string strDigit = to_string(digits[i]);
		if (i != digits.size() - 1)
		{
			while (strDigit.size() < nDigit)
			{
				strDigit.insert(strDigit.begin(), '0');
			}
		}
		cout << strDigit;
	}
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

unsigned int ReverseBit(unsigned int bitNum, unsigned int input)
{
	unsigned int count = bitNum;
	unsigned int revBitOutput = input;
	input >>= 1;
	while (input != 0)
	{
		revBitOutput <<= 1;
		revBitOutput |= input & 1;
		input >>= 1;
		count--;
	}
	revBitOutput <<= count;
	//unsigned int revBitOutput = 0;
	//unsigned int bitLoop = bitNum ;
	//for (unsigned int i = 0; i < bitLoop; i++)
	//{
	//	revBitOutput |= input & 1; // putting the set bits of num
	//	input >>= 1;               //shift the tmp Right side 
	//	revBitOutput <<= 1;        //shift the tmp left side 
	//}

	//unsigned int revBitOutput = 0;
	//unsigned int count = bitNum;
	//// traversing bits of 'n' from the right 
	//while (input > 0)
	//{
	//	// bitwise left shift  
	//	// 'rev' by 1 
	//	revBitOutput <<= 1;

	//	// if current bit is '1' 
	//	if ((input & 1) == 1)
	//		revBitOutput ^= 1;

	//	// bitwise right shift  
	//	// 'n' by 1 
	//	input >>= 1;
	//	count--;
	//}
	//revBitOutput <<= count;
	return revBitOutput;
}

void PrintComplexVector(vector<complex<double>>& inputs)
{
	for (size_t i = 0; i < inputs.size(); ++i)
	{
		cout << inputs[i] << " ";
	}
}

void MultipyComplexVector(vector<complex<double>>& leftMultiplier, vector<complex<double>>& rightMultiplier, vector<complex<double>>& result)
{
	size_t size = max(leftMultiplier.size(), rightMultiplier.size());
	leftMultiplier.resize(size);
	rightMultiplier.resize(size);
	result.resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		result[i] = leftMultiplier[i] * rightMultiplier[i];
	}
}

void NormalizeSize(size_t inputSize, size_t& outputSize)
{
	outputSize = 1;
	while (outputSize < inputSize) outputSize <<= 1;
}

void ReadBigIntFromFile(vector<unsigned int>& leftMultiplier, vector<unsigned int>& rightMultiplier, char* fileName)
{
	ifstream fin(fileName, ios::in);
	string strLeftMultiplier;
	fin >> strLeftMultiplier;
	string strRightMultiplier;
	fin >> strRightMultiplier;

	leftMultiplier.clear();
	for (int i = strLeftMultiplier.size() - 1; i >= 0 ; --i)
	{
		leftMultiplier.push_back(static_cast<unsigned int>(strLeftMultiplier[i] - '0'));
	}

	rightMultiplier.clear();
	for (int i = strRightMultiplier.size() - 1; i >= 0; --i)
	{
		rightMultiplier.push_back(static_cast<unsigned int>(strRightMultiplier[i] - '0'));
	}
}
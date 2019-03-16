#pragma once
#include <vector>
#include <complex>
#include <string>
#include "CommonValue.h"
using namespace std;

void GetBaseFromFile(string fileName);
void InitializeBaseConfig(unsigned int base);

void PrintBigInt(vector<unsigned int>& digits, size_t nDigit);
string ConvertBigIntToString(vector<unsigned int>& digits, size_t nDigit);
void NormalizeBigInt(vector<unsigned int>& digits, unsigned int base, double invertBase);

void PrintComplexVector(vector<complex<double>>& inputs);
void MultipyComplexVector(vector<complex<double>>& leftMultiplier, vector<complex<double>>& rightMultiplier);

void NormalizeSize(size_t inputSize, size_t& outputSize);
void InitializeFFTInputVector(vector<unsigned int>& leftMultipliers,
	vector<unsigned int>& rightMultipliers,
	vector<complex<double>>& fftLeftMultiplier,
	vector<complex<double>>& fftRightMultiplier,
	vector<unsigned int>& result);
unsigned int CountBitFromSize(size_t input);
size_t ReverseBit(unsigned int bitNum, size_t input);

void ReadBigIntFromString(string stringOfNumber, size_t nDigit, vector<unsigned int>& digits);
void ReadBigIntFromFile(vector<unsigned int>& leftMultiplier, vector<unsigned int>& rightMultiplier, unsigned int nDigit, string fileName);
void ReadMultiBigIntFromFile(vector<vector<unsigned int>>& leftMultipliers, vector<vector<unsigned int>>& rightMultipliers, size_t nDigit, string fileName);


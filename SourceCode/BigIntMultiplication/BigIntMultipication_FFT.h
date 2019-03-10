#pragma once
#include <vector>
#include <complex>
using namespace std;

void MultiplyBigInt_RecusiveFFT(vector<unsigned int>& leftMultiplier, vector<unsigned int>& rithtMultiplier, vector<unsigned int>& result, unsigned int base, double invertBase);
void MultiplyBigInt_NonRecusiveFFT(vector<complex<double>>& leftMultiplier, vector<complex<double>>& rithtMultiplier, vector<unsigned int>& result, unsigned int base, double invertBase);


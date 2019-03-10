#include "BigIntMultipication_FFT.h"
#include "CommonMethod.h"
#include "FFT.h"
#include <algorithm>
using namespace std;

void MultiplyBigInt_RecusiveFFT(vector<unsigned int>& leftMultiplier, vector<unsigned int>& rithtMultiplier, vector<unsigned int>& result, unsigned int base, double invertBase)
{
	size_t maxSize = max(leftMultiplier.size(), rithtMultiplier.size());
	size_t fftSize = 1;
	NormalizeSize(maxSize, fftSize);
	fftSize <<= 1;
	leftMultiplier.resize(fftSize);
	rithtMultiplier.resize(fftSize);

	vector<complex<double>> fftLeftMultiplier;
	ExecuteRecusiveFFT(leftMultiplier, fftLeftMultiplier);
	vector<complex<double>> fftRightMultiplier;
	ExecuteRecusiveFFT(rithtMultiplier, fftRightMultiplier);

	vector<complex<double>> fftMultiplicationResult;
	MultipyComplexVector(fftLeftMultiplier, fftRightMultiplier);

	ExecuteRecusiveInvertFFT(fftLeftMultiplier, result);

	NormalizeBigInt(result, base, invertBase);
}

void MultiplyBigInt_NonRecusiveFFT(vector<complex<double>>& leftMultiplier,
	vector<complex<double>>& rithtMultiplier,
	vector<unsigned int>& result,
	unsigned int base,
	double invertBase)
{
	NonRecusiveFFT(leftMultiplier);
	NonRecusiveFFT(rithtMultiplier);

	MultipyComplexVector(leftMultiplier, rithtMultiplier);

	NonRecusiveInvertFFT(leftMultiplier, result);

	NormalizeBigInt(result, base, invertBase);
}
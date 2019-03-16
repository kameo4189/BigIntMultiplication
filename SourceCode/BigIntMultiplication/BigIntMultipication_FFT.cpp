#include "BigIntMultipication_FFT.h"
#include "CommonMethod.h"
#include "FFT.h"
#include <algorithm>
using namespace std;

void MultiplyBigInt_RecusiveFFT(vector<complex<double>>& leftMultiplier, vector<complex<double>>& rithtMultiplier, vector<unsigned int>& result, unsigned int base, double invertBase)
{
	vector<complex<double>> fftLeftMultiplier(leftMultiplier.size());
	ExecuteRecusiveFFT(leftMultiplier, fftLeftMultiplier);
	vector<complex<double>> fftRightMultiplier(rithtMultiplier.size());
	ExecuteRecusiveFFT(rithtMultiplier, fftRightMultiplier);

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
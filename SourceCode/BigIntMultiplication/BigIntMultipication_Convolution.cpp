#include "BigIntMultipication_Convolution.h"
#include "CommonMethod.h"
#include "VectorConvolution.h"

void MultiplyBigInt_Convolution(vector<unsigned int>& leftMultiplier, vector<unsigned int>& rithtMultiplier, vector<unsigned int>& result, unsigned int base, double invertBase)
{
	VectorConvolution(leftMultiplier, rithtMultiplier, result);
	NormalizeBigInt(result, base, invertBase);
}
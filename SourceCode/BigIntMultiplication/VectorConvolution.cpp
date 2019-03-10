#include "VectorConvolution.h"
#include <algorithm>

void VectorConvolution(vector<unsigned int>& vector1, vector<unsigned int>& vector2, vector<unsigned int>& result)
{
	for (size_t i = 0; i < vector1.size() - 1; ++i)
	{
		result[i] = 0;
		for (size_t j = 0; j <= i; ++j)
		{
			result[i] += vector1[j] * vector2[i - j];
		}
	}
}
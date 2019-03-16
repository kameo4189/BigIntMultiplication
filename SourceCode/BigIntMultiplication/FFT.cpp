#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "FFT.h"
#include "CommonMethod.h"

void ExecuteRecusiveFFT(vector<complex<double>>& inputs, vector<complex<double>>& outputs)
{
	double angle = 2 * M_PI / inputs.size(); //2*PI/ n;
	complex<double> omega(cos(angle), sin(angle));

	RecusiveFFT(inputs, outputs, omega);
}

void ExecuteRecusiveInvertFFT(vector<complex<double>>& inputs, vector<unsigned int>& outputs)
{
	double angle = -2 * M_PI / inputs.size(); //2*PI/ n;
	complex<double> invertOmega(cos(angle), sin(angle));

	vector<complex<double>> invertFFTOutput(inputs.size());
	RecusiveInvertFFT(inputs, invertFFTOutput, invertOmega);

	for (size_t i = 0; i < outputs.size(); ++i)
	{
		outputs[i] = static_cast<unsigned int>(invertFFTOutput[i].real() + 0.5);
	}
}

void RecusiveFFT(vector<complex<double>>& inputs, vector<complex<double>>& outputs, complex<double>& omega)
{
	if (inputs.size() == 1)
	{
		outputs[0] = inputs[0];
		return;
	}

	// devide step
	size_t divideSize = inputs.size() / 2;
	vector<complex<double>> inputsEven(divideSize);
	vector<complex<double>> inputsOdd(divideSize);
	for (size_t i = 0; i < inputs.size(); i++)
	{
		if (i % 2 == 0)
		{
			inputsEven[i / 2] = inputs[i];
		}
		else
		{
			inputsOdd[i / 2] = inputs[i];
		}
	}

	// recursive call with omega^2 as (n/2)th primitive root of unity 
	complex<double> currentOmega = pow(omega, 2);
	vector<complex<double>> outputsEven(divideSize);
	RecusiveFFT(inputsEven, outputsEven, currentOmega);
	vector<complex<double>> outputsOdd(divideSize);
	RecusiveFFT(inputsOdd, outputsOdd, currentOmega);

	complex<double> x = 1; // storing power of omega
	// combine step, using x = omega^i
	//outputs.resize(size);
	for (size_t i = 0; i < divideSize; ++i)
	{
		outputs[i] = outputsEven[i] + x * outputsOdd[i];
		outputs[i + divideSize] = outputsEven[i] - x * outputsOdd[i];
		x = x * omega;
	}
}

void NonRecusiveFFT(vector<complex<double>>& inputs)
{
	size_t size = inputs.size();
	if (size == 1)
	{
		return;
	}

	unsigned int bitNum = CountBitFromSize(size);
	complex<double> tmp;
	size_t revertIndex;
	for (size_t i = 0; i < size; ++i)
	{
		revertIndex = ReverseBit(bitNum, i);
		if (i < revertIndex)
		{
			tmp = inputs[revertIndex];
			inputs[revertIndex] = inputs[i];
			inputs[i] = tmp;
		}
	}

	vector<complex<double>> nextInputs(size);
	vector<complex<double>> W(size);

	for (size_t step = 1; step < size; step <<= 1)
	{
		complex<double> x = 1;
		double angle = M_PI / step;
		complex<double> curentOmega(cos(angle), sin(angle));
		for (unsigned int i = 0; i < step; ++i)
		{
			W[i] = x;
			x *= curentOmega;
		}

		size_t startEven = 0;
		size_t startOdd = startEven + step;
		while (startEven < size)
		{
			for (unsigned int i = 0; i < step; ++i)
			{
				nextInputs[startEven + i] = inputs[startEven + i] + W[i] * inputs[startOdd + i];
				nextInputs[startEven + i + step] = inputs[startEven + i] - W[i] * inputs[startOdd + i];
			}
			startEven += 2 * step;
			startOdd = startEven + step;
		}

		for (size_t i = 0; i < size; ++i)
		{
			inputs[i] = nextInputs[i];
		}
	}
}

void RecusiveInvertFFT(vector<complex<double>>& inputs, vector<complex<double>>& outputs, complex<double>& invertOmega)
{
	if (inputs.size() == 1)
	{
		outputs[0] = inputs[0];
		return;
	}

	// devide step
	size_t divideSize = inputs.size() / 2;
	vector<complex<double>> inputsEven(divideSize);
	vector<complex<double>> inputsOdd(divideSize);
	for (size_t i = 0; i < inputs.size(); i++)
	{
		if (i % 2 == 0)
		{
			inputsEven[i / 2] = inputs[i];
		}
		else
		{
			inputsOdd[i / 2] = inputs[i];
		}
	}

	// recursive call with omega^2 as (n/2)th primitive root of unity 
	complex<double> currentInvertOmega = pow(invertOmega, 2);
	vector<complex<double>> outputsEven(divideSize);
	RecusiveInvertFFT(inputsEven, outputsEven, currentInvertOmega);
	vector<complex<double>> outputsOdd(divideSize);
	RecusiveInvertFFT(inputsOdd, outputsOdd, currentInvertOmega);

	complex<double> x = 1; // storing power of omega
	
	// combine step, using x = omega^i
	for (size_t i = 0; i < divideSize; ++i)
	{
		outputs[i] = outputsEven[i] + x * outputsOdd[i];
		outputs[i] /= 2;
		outputs[i + divideSize] = outputsEven[i] - x * outputsOdd[i];
		outputs[i + divideSize] /= 2;
		x = x * invertOmega;
	}
}

void NonRecusiveInvertFFT(vector<complex<double>>& inputs, vector<unsigned int>& outputs)
{
	size_t size = inputs.size();
	if (size == 1)
	{
		outputs[0] = static_cast<unsigned int>(inputs[0].real() + 0.5);
		return;
	}

	unsigned int bitNum = CountBitFromSize(size);
	complex<double> tmp;
	size_t revertIndex;
	for (size_t i = 0; i < size; ++i)
	{
		revertIndex = ReverseBit(bitNum, i);
		if (i < revertIndex)
		{
			tmp = inputs[revertIndex];
			inputs[revertIndex] = inputs[i];
			inputs[i] = tmp;
		}
	}

	vector<complex<double>> nextInputs(size);
	vector<complex<double>> W(size);

	for (size_t step = 1; step < size; step <<= 1)
	{
		complex<double> x = 1;
		double angle = -1.0 * M_PI / step;
		complex<double> curentOmega(cos(angle), sin(angle));
		for (unsigned int i = 0; i < step; ++i)
		{
			W[i] = x;
			x *= curentOmega;
		}

		size_t startEven = 0;
		size_t startOdd = startEven + step;
		while (startEven < size)
		{
			for (unsigned int i = 0; i < step; ++i)
			{
				nextInputs[startEven + i] = inputs[startEven + i] + W[i] * inputs[startOdd + i];
				nextInputs[startEven + i + step] = inputs[startEven + i] - W[i] * inputs[startOdd + i];
			}
			startEven += 2 * step;
			startOdd = startEven + step;
		}

		for (size_t i = 0; i < size; ++i)
		{
			inputs[i] = nextInputs[i];
		}
	}

	for (size_t i = 0; i < outputs.size(); ++i)
	{
		outputs[i] = static_cast<unsigned int>((inputs[i].real() / (1.0 * size)) + 0.5);
	}
}
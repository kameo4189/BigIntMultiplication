#include "CommonValue.h"
#include "CommonMethod.h"
#include "BigIntMultipication_Convolution.h"
#include "BigIntMultipication_FFT.h"
#include "FFT.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <complex>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

enum ExecutionMethodMode
{
	CONVOLUTION = 0,
	RECUSIVE_FFT,
	NON_RECUSIVE_FFT
};

enum ExecutionMode
{
	NOT_MEASURE_TIME = 0,
	MEASURE_TIME
};

void NotMeasurementTimeExecution(ExecutionMethodMode methodMode,
	vector<vector<unsigned int>>& leftMultipliers,
	vector<vector<unsigned int>>& rightMultipliers,
	vector<vector<unsigned int>>& results,
	unsigned int base, double invertBase)
{
	vector<vector<complex<double>>> fftLeftInput(leftMultipliers.size());
	vector<vector<complex<double>>> fftRightInput(leftMultipliers.size());

	results.clear();
	results.resize(leftMultipliers.size());
	switch (methodMode)
	{
	case ExecutionMethodMode::CONVOLUTION:
		for (size_t i = 0; i < leftMultipliers.size(); i++)
		{
			size_t maxSize = max(leftMultipliers[i].size(), rightMultipliers[i].size());
			size_t resultSize = 2 * maxSize;
			leftMultipliers[i].resize(resultSize);
			rightMultipliers[i].resize(resultSize);
			results[i].resize(resultSize);
		}
		for (size_t i = 0; i < leftMultipliers.size(); i++)
		{
			MultiplyBigInt_Convolution(leftMultipliers[i], rightMultipliers[i], results[i], base, invertBase);
		}
		break;
	case ExecutionMethodMode::RECUSIVE_FFT:
		for (size_t i = 0; i < leftMultipliers.size(); i++)
		{
			MultiplyBigInt_RecusiveFFT(leftMultipliers[i], rightMultipliers[i], results[i], base, invertBase);
		}
		break;
	case ExecutionMethodMode::NON_RECUSIVE_FFT:
		for (size_t i = 0; i < leftMultipliers.size(); i++)
		{
			size_t maxSize = max(leftMultipliers[i].size(), rightMultipliers[i].size());
			size_t fftSize = 1;
			NormalizeSize(maxSize, fftSize);
			fftSize <<= 1;
			fftLeftInput[i].resize(fftSize);
			fftRightInput[i].resize(fftSize);
			for (size_t j = 0; j < leftMultipliers[i].size(); ++j)
			{
				fftLeftInput[i][j] = leftMultipliers[i][j];
			}

			for (size_t j = 0; j < rightMultipliers[i].size(); ++j)
			{
				fftRightInput[i][j] = rightMultipliers[i][j];
			}
			fftRightInput.resize(fftSize);

			results[i].resize(fftSize);
		}


		for (size_t i = 0; i < fftLeftInput.size(); i++)
		{
			MultiplyBigInt_NonRecusiveFFT(fftLeftInput[i], fftRightInput[i], results[i], base, invertBase);
		}
		break;
	default:
		break;
	}
}

long long MeasurementTimeExecution(ExecutionMethodMode methodMode,
	vector<vector<unsigned int>>& leftMultipliers,
	vector<vector<unsigned int>>& rightMultipliers,
	vector<vector<unsigned int>>& results,
	unsigned int base, double invertBase)
{
	long long executionTime;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;

	vector<vector<unsigned int>> orgLeftMultipliers = leftMultipliers;
	vector<vector<unsigned int>> orgRightMultipliers = rightMultipliers;
	vector<vector<complex<double>>> fftLeftInput(leftMultipliers.size());
	vector<vector<complex<double>>> fftRightInput(leftMultipliers.size());

	results.clear();
	results.resize(leftMultipliers.size());
	switch (methodMode)
	{
	case ExecutionMethodMode::CONVOLUTION:
		for (size_t i = 0; i < leftMultipliers.size(); i++)
		{
			size_t maxSize = max(leftMultipliers[i].size(), rightMultipliers[i].size());
			size_t resultSize = 2 * maxSize;
			leftMultipliers[i].resize(resultSize);
			rightMultipliers[i].resize(resultSize);
			results[i].resize(resultSize);
		}

		t1 = high_resolution_clock::now();
		for (size_t i = 0; i < leftMultipliers.size(); i++)
		{
			MultiplyBigInt_Convolution(leftMultipliers[i], rightMultipliers[i], results[i], base, invertBase);
		}
		t2 = high_resolution_clock::now();
		executionTime = duration_cast<microseconds>(t2 - t1).count();
		leftMultipliers = orgLeftMultipliers;
		rightMultipliers = orgRightMultipliers;
		break;
	case ExecutionMethodMode::RECUSIVE_FFT:
		t1 = high_resolution_clock::now();
		for (size_t i = 0; i < leftMultipliers.size(); i++)
		{
			MultiplyBigInt_RecusiveFFT(leftMultipliers[i], rightMultipliers[i], results[i], base, invertBase);
		}
		t2 = high_resolution_clock::now();
		executionTime = duration_cast<microseconds>(t2 - t1).count();
		leftMultipliers = orgLeftMultipliers;
		rightMultipliers = orgRightMultipliers;
		break;
	case ExecutionMethodMode::NON_RECUSIVE_FFT:
		for (size_t i = 0; i < leftMultipliers.size(); i++)
		{
			size_t maxSize = max(leftMultipliers[i].size(), rightMultipliers[i].size());
			size_t fftSize = 1;
			NormalizeSize(maxSize, fftSize);
			fftSize <<= 1;
			fftLeftInput[i].resize(fftSize);
			fftRightInput[i].resize(fftSize);
			for (size_t j = 0; j < leftMultipliers[i].size(); ++j)
			{
				fftLeftInput[i][j] = leftMultipliers[i][j];
			}

			for (size_t j = 0; j < rightMultipliers[i].size(); ++j)
			{
				fftRightInput[i][j] = rightMultipliers[i][j];
			}
			fftRightInput.resize(fftSize);
		}

		t1 = high_resolution_clock::now();
		for (size_t i = 0; i < fftLeftInput.size(); i++)
		{
			MultiplyBigInt_NonRecusiveFFT(fftLeftInput[i], fftRightInput[i], results[i], base, invertBase);
		}
		t2 = high_resolution_clock::now();
		executionTime = duration_cast<microseconds>(t2 - t1).count();
		break;
	default:
		break;
	}
	return executionTime;
}
// Command line: BigIntMultiplication.exe [Input file path] [ExecutionMode] [MethodMode] [BASE] [Number of execution];
// Arguments
// [Input file path] : path to input file for big int number of left multipliers and right multipliers, each line is a number. Input.txt is default if not input
// [ExecutionMode] : 0 is not measuring time and 1 is measuring time when execution. 0 is default if not input
// [MethodMode] : 0 is convolution and 1 is recusive FFT and 2 is non-recusive FFT. 0 is default if not input 
// [BASE] : base for splitting and multiply. Ex: base = 100, it will spliting and multiply with 2 digits.
//          It not input, default is in base.config. If base.config file doesn't exist, 10 is default.
// [Number of execution] : number of execution to run. 1 is default if not input 
int main(int argc, char *argv[])
{	
	vector<vector<unsigned int>> leftMultipliers;
	vector<vector<unsigned int>> rightMultipliers;
	vector<vector<unsigned int>> results;

	ExecutionMode executionMode;
	ExecutionMethodMode methodMode;

	unsigned int base = 10;
	InitializeBaseConfig(base);
	GetBaseFromFile("base.config");

	unsigned int numberOfExecution = 1;
	string inputPath = "Input.txt";

	if (argc >= 2)
	{
		inputPath = argv[1];
	}

	if (argc >= 3)
	{
		int argExecutionMode = stoi(argv[2]);
		executionMode = static_cast<ExecutionMode>(argExecutionMode);
	}

	if (argc >= 4)
	{
		int argMethodMode = stoi(argv[3]);
		methodMode = static_cast<ExecutionMethodMode>(argMethodMode);
	}

	if (argc >= 5)
	{
		base = stoul(argv[4]);
		InitializeBaseConfig(base);
	}

	if (argc >= 6)
	{
		numberOfExecution = stoul(argv[5]);
	}

	if (argc >= 7)
	{
		numberOfExecution = stoul(argv[5]);
	}

	ReadMultiBigIntFromFile(leftMultipliers, rightMultipliers, NDIGIT, inputPath);

	if (executionMode == ExecutionMode::NOT_MEASURE_TIME)
	{
		NotMeasurementTimeExecution(methodMode, leftMultipliers, rightMultipliers, results, BASE, INVERT_BASE);
	}
	else
	{
		vector<long long> executionTime(numberOfExecution);
		for (unsigned int i = 0; i < numberOfExecution; i++)
		{
			executionTime[i] = MeasurementTimeExecution(methodMode, leftMultipliers, rightMultipliers, results, BASE, INVERT_BASE);
			cout << "Finish at time " << i << ": " << executionTime[i] << endl;
		}

		string timeOutputPath = "MeasurementTime_" + to_string(methodMode) + "_" + to_string(base) + "_" + to_string(numberOfExecution) + ".txt";
		ofstream foutTime(timeOutputPath, ios::out);		
		for (size_t i = 0; i < executionTime.size(); i++)
		{
			foutTime << executionTime[i] << endl;
		}
	}

	string outputPath = "Output_" + to_string(methodMode) + "_" + to_string(base) + "_" + to_string(numberOfExecution) + ".txt";
	ofstream foutResult(outputPath, ios::out);
	for (size_t i = 0; i < results.size(); i++)
	{
		foutResult << ConvertBigIntToString(results[i], NDIGIT) << endl;
	}
	return 1;
}
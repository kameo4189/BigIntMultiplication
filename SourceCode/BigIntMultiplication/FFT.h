#pragma once
#include <vector>
#include <complex>
using namespace std;

void ExecuteRecusiveFFT(vector<unsigned int>& inputs, vector<complex<double>>& outputs);
void ExecuteRecusiveInvertFFT(vector<complex<double>>& inputs, vector<unsigned int>& outputs);
void RecusiveFFT(vector<complex<double>>& inputs, vector<complex<double>>& outputs, complex<double>& omega);
void NonRecusiveFFT(vector<complex<double>>& inputs);
void RecusiveInvertFFT(vector<complex<double>>& inputs, vector<complex<double>>& outputs, complex<double>& invertOmega);
void NonRecusiveInvertFFT(vector<complex<double>>& inputs, vector<unsigned int>& outputs);
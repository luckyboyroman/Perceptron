#pragma once
#include <math.h>
#include <time.h>
#include <random>
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;
struct neuron {
	double value;
	double error;
	void act() {
		value = 1 / (1 + pow(2.71828, -value));
	}
};
class NetWork
{
private:
	int n;
	int* size;
public:
	neuron** neurons;
	double*** weights;
	double sigm_pro(double x);
	void SetLayers(int n, int* size);
	void ShowWeights();
	void SaveWeights();
	void UploadWeights();
	void Show();
	void SetInput(double* values);
	double forward_feed();
	void BackPropogation(double expect);
	void WeightsUpdater(double lr);
};


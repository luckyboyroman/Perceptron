#include "NetWork.h"
using namespace std;

int main() {
	NetWork hi;
	int const n = 4;
	int* size = new int[n];
	size[0] = 3;
	size[1] = 5;
	size[2] = 3;
	size[3] = 1;
	hi.SetLayers(n,size);
	hi.ShowWeights();


	double* answers = new double[4];
	answers[0] = 0;
	answers[1] = 1;
	answers[2] = 1;
	answers[3] = 0;

	double** input_data;
	input_data = new double* [4];
	for (int i = 0; i < 4; i++) {
		input_data[i] = new double[size[0]];
	}
	input_data[0][0] = 0;
	input_data[0][1] = 0;
	input_data[0][2] = 1;

	input_data[1][0] = 1;
	input_data[1][1] = 1;
	input_data[1][2] = 1;

	input_data[2][0] = 1;
	input_data[2][1] = 0;
	input_data[2][2] = 1;


	input_data[3][0] = 0;
	input_data[3][1] = 0;
	input_data[3][2] = 1;

	bool study = true;
	double eps = 0.1;
	if (study) {
		double error;
		double result;
		do {
			error = 0.0;
			for (int i = 0; i < n; i++) {
				hi.SetInput(input_data[i]);
				result = hi.forward_feed();
				error += fabs(result-answers[i]);
				if (result != answers[i]) {
					hi.BackPropogation(answers[i]);
					hi.WeightsUpdater(0.05);
				}
			}
		} while (error>eps);
		hi.SaveWeights();
	}
	input_data[0][0] = 0.0;
	input_data[0][1] = 0.0;
	input_data[0][2] = 1;
	hi.SetInput(input_data[0]);
	hi.forward_feed();
	hi.Show();
	delete[] answers,size, input_data;
	return 0;
}
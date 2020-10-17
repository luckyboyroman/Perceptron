#include <iostream>
#include <math.h>
#include <time.h>
#include <random>
using namespace std;

struct neuron {
	double value;
	double error;
	void act() {
		value = 1 / (1 + pow(2.71828, -value));
	}
};

class network {
public:
	neuron** neurons;
	double *** weights;
	int* size;
	int n;
	double tmp;
	double sigm_pro(double x) {
		if (fabs(x) < 1e-9 || fabs(x - 1) < 1e-9) return 0;
		double res = x * (1 - x);
		return res;
	}
	void SetLayers(int n,int *p) {
		this->n = n;
		neurons = new neuron * [n];
		size = new int[n];
		weights = new double** [n - 1];
		for (int i = 0; i < n; i++) {
			neurons[i] = new neuron[p[i]];
			size[i] = p[i];
			if (i < n - 1) {
				weights[i] = new double* [p[i]];
				for (int j = 0; j < p[i]; j++) {
					weights[i][j] = new double[p[i + 1]];
					for (int k = 0; k < p[i + 1]; k++) {
						weights[i][j][k] = (rand() % 70) / 50.0;
					}
				}
			}
		}
	}
	void ShowWeights(int* p);
	void Show(int *p) {
		cout << "Shows neurons.values" << endl;
		for (int i = 0; i < n; i++) {
			cout << "Sloi" << i << endl;
			for (int j = 0; j < size[i]; j++) {
				cout <<"n["<< i << "]" << "[" << j << "]" << " " << neurons[i][j].value << endl;
			}
			cout << endl;
		}
	}
	void NeuronsCleaned() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < size[i]; j++) {
				neurons[i][j].value = 0;
			}
		}
	}
	void SetInput(double *values) {
		for (int i = 0; i < size[0]; i++) {
			neurons[0][i].value = values[i];
		}
	}
	void forward_feed() {
		for (int k = 1; k < n; k++) {
			for (int i = 0; i < size[k]; i++) {
				for (int j = 0; j < size[k - 1]; j++) {
					neurons[k][i].value += neurons[k - 1][j].value * weights[k - 1][j][i];
				}
				neurons[k][i].act();
			}
		}
	}
	void BackPropogation(double expect) {
		neurons[n - 1][0].error = expect - neurons[n - 1][0].value;
		for (int i = n - 2; i > 0; i--) {
			for (int j = 0; j < size[i]; j++) {
				double error = 0.0;
				for (int k = 0; k < size[i+1]; k++) {
					error += neurons[i+1][k].error * weights[i][j][k];
				}
				neurons[i][j].error = error;
			}
		}
	}
	void WeightsUpdater(double lr) {
		/*LayerNum=0*/
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < size[i]; j++) {
				for (int k = 0; k < size[i + 1]; k++) {
					weights[i][j][k] += neurons[i + 1][k].error * sigm_pro(neurons[i + 1][k].value) * neurons[i][j].value * lr;
				}
			}
		}
	}
	};
/*Определения ф-ций*/
void network::ShowWeights(int* p){
	cout << "Shows weights" << endl;
	for (int i = 0; i < n - 1; i++) {
		cout << "Layer:" << i << endl;
		for (int j = 0; j < p[i]; j++) {
			for (int k = 0; k < p[i + 1]; k++) {
				cout  <<"weights[" << i << "]" << "[" << j << "]" << "[" << k << "]\t" << weights[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

int main() {
	network hi;
	int const n = 4;
	int* size = new int[n];
	double* results = new double[n];
	size[0] = 1;
	size[1] = 3;
	size[2] = 3;
	size[3] = 1;
	double* input_data = new double[size[0]];
	input_data[0] = 1.0;
	hi.SetLayers(n,size);
	hi.NeuronsCleaned();
	hi.SetInput(input_data);
	hi.Show(size);
	hi.ShowWeights(size);
	hi.forward_feed();
	for (int i = 0; i < 5000; i++) {
		hi.BackPropogation(50.0);
		hi.WeightsUpdater(0.5);
		hi.forward_feed();
	}
	hi.Show(size);
}

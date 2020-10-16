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
	int layers;
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
		srand(time(NULL));
		this->n = n;
		layers = n;
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
						weights[i][j][k] = (rand() % 40) / 10.0;
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
	void forward_feed(int LayerNumber) {
		for (int i = 0; i < size[LayerNumber]; i++) {
			for (int j = 0; j < size[LayerNumber - 1]; j++) {
				neurons[LayerNumber][i].value += neurons[LayerNumber - 1][j].value*weights[LayerNumber-1][j][i];
			}
			neurons[LayerNumber][i].act();
		}
	}
	void BackPropogation(double pred,double expect,double lr) {
		double weights_delta, error;

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
	int const n = 3;
	int* size = new int[n];
	double* results = new double[n];
	size[0] = 3;
	size[1] = 2;
	size[2] = 2;
	double* input_data = new double[size[0]];
	for (int i = 0; i < size[0]; i++) {
		input_data[i] = i*0.5;
	}
	hi.SetLayers(n,size);
	hi.NeuronsCleaned();
	hi.SetInput(input_data);
	hi.Show(size);
	hi.ShowWeights(size);
	hi.forward_feed(1);
	hi.forward_feed(2);
	hi.Show(size);
}
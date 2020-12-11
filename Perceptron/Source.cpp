#include "NetWork.h"
using namespace std;
int n,k;
vector <double> answers;
vector<vector<double>> input_data;

void ReadInputData(int *&size) {
	ifstream fin;
	string str;
	fin.open("input__.txt");
	if (!fin.is_open()) {
		cout << "Error reading the file";
		system("pause");
	}
	while (!fin.eof()) {
		fin >> str;
		if (str == "NetWork") fin >> n;
		if (str == "Size") {
			size = new int[n];
			for (int i = 0; i < n; i++) {
				fin >> size[i];
			}
		}
		if (str == "Inputs") {
			fin >> k;
			input_data.resize(k);
			answers.resize(k);
			for (int i = 0; i < k; ++i) {
				input_data[i].resize(size[0]);
			}
			for (int i = 0; i < k; ++i) {
				for (int j = 0; j < size[0]; j++) {
					fin >> input_data[i][j];
				}
				fin >> answers[i];
			}
		}
	}
	fin.close();
}
void Transform(int* size) {
	for (int i = 0; i < k; ++i) {
		if (fabs(answers[i] < 1e-4)) answers[i] = 0.0;
		answers[i] += M_PI;
		answers[i] /= 2 * M_PI;
	}
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < size[0]; j++) {
			input_data[i][j] += M_PI;
			input_data[i][j] /= 2 * M_PI;
		}
	}
}
int main() {
	int* size;
	NetWork hi;
	int epoch = 0;
	ReadInputData(size);
	Transform(size);
	hi.SetLayers(n, size);
	bool study = true;
	cout << "Study? 1/0" << endl;
	cin >> study;
	double eps = 0.01;
	int begin, end, t;
	begin = clock();
	if (study) {
		cout << "Studying..." << endl;
		double error;
		double result;
		do {
			error = 0.0;
			for (int i = 0; i < k; ++i) {
				hi.SetInput(input_data[i]);
				result = hi.forward_feed();
				error += fabs(result - answers[i]);
				if (result != answers[i]) {
					hi.BackPropogation(answers[i]);
					hi.WeightsUpdater(0.05);
				}
			}
			epoch++;
		} while (error > eps);
		hi.SaveWeights();
	}
	else {
		hi.ReadWeights();
	}
	end = clock();
	t = end - begin;
	cout << "TIMEWORK= " << t << endl;
	input_data[0] = { 0.033, 0.661, 0.136 };

	for (int i = 0; i < size[0]; ++i) {
		input_data[0][i] += M_PI;
		input_data[0][i] /= 2* M_PI;
	}

	hi.SetInput(input_data[0]);
	double result;
	result= hi.forward_feed();
	result *= M_PI * 2;
	result -= M_PI;
	if (study) cout << "epoch=" << epoch << endl;
	printf("result= %.5f", result);
	answers.clear();
	for (int i = 0; i < k; ++i) {
		input_data[i].clear();
	}
	input_data.clear();
	delete[]size;
	return 0;
}

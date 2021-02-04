#include "NetWork.h"
using namespace std;
int n, k;
vector <double> answers;
vector<vector<double>> input_data;

void ReadInputData(int*& size) {
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

	double norm_j = 0.0,tmp=0.0;
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < size[0]; j++) {
			if (fabs(input_data[i][j] < 1e-4)) input_data[i][j] = 0.0;
			tmp = tmp + pow(input_data[i][j],2);
		}
		norm_j = sqrt(tmp);
		for (int j = 0; j < size[0]; ++j) {
			input_data[i][j] /= norm_j;
		}
		tmp = 0.0;
		norm_j = 0.0;
	}
}
int main() {
	NetWork hi;
	int* size;
	int epoch = 0, begin, end, t;
	bool study = true;
	double eps = 0.1, tmp=0.0;

	cout << "Study? 1/0" << endl;
	cin >> study;

	ReadInputData(size);
	Transform(size);
	hi.SetLayers(n, size);
	begin = clock();
	if (study) {
		cout << "Studying..." << endl;
		double error;
		double result;
		int jj = 0;
		do {
			error = 0.0;
			for (int i = 0; i < k; ++i) {
				hi.SetInput(input_data[i]);
				result = hi.forward_feed();
				error += fabs(result - answers[i]);
				//error -= (answers[i] * log(result)+(1-answers[i])*log(1-result))/answers.size();
					hi.BackPropogation(answers[i]);
					hi.WeightsUpdater(0.05);
			}
			epoch++;
			if (epoch % 15 == 0) cout << "Error= " << error << endl;
		} while (error > eps);
		hi.SaveWeights();
	}
	else {
		hi.ReadWeights();
	}
	end = clock();
	t = end - begin;
	input_data[0] = { 0.427, 0.283, 0.561 };
	cout << "Your initial data: " << endl;
	for (int i = 0; i < size[0]; ++i) {
		cout << input_data[0][i] << " ";
	}
	cout << endl;

	//Нормируем входные данные
	for (int i = 0; i < size[0]; ++i) {
		tmp = tmp + pow(input_data[0][i], 2);
	}

	for (int i = 0; i < size[0]; i++) {
		input_data[0][i] /= sqrt(tmp);
	}
	//

	hi.SetInput(input_data[0]);
	double result;
	result = hi.forward_feed();
	result *= M_PI * 2;
	result -= M_PI;
	if (study) {
		cout << "epoch=" << epoch << endl;
		cout << "TIMEWORK= " << t << endl;
	}
	printf("Prediction angle = %.5f", result);
	return 0;
}

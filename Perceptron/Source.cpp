#include "NetWork.h"
using namespace std;
int n,k;
double tmp = 3.14;
vector <double> answers;
vector<vector<double>> input_data;
map <vector <double>, double> myMap;

void ReadInputData(int *&size) {
	ifstream fin;
	string str;
	fin.open("Input_1.txt");
	while (!fin.eof()) {
		fin >> str;
		if (str == "NetWork") fin >> n;
		if (str == "Size") {
			size = new int[n];
			for (int i = 0; i < n; i++) {
				fin >> size[i];
			}
		}
		if (str == "Answers") {
			fin >> k;
			answers.resize(k);
			for (int i = 0; i < k; i++) {
				fin >> answers[i];
			}
		}

		if (str == "Input") {
			input_data.resize(k);
			for (int i = 0; i < k; i++) {
				input_data[i].resize(size[0]);
			}
			for (int i = 0; i < k; i++) {
				for (int j = 0; j < size[0]; j++) {
					fin >> input_data[i][j];
				}
			}
		}
	}
	fin.close();
}
void Transform(int *&size) {
	for (int i = 0; i < k; i++) {
		answers[i] += tmp;
		answers[i] /= 2*tmp;
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < size[0]; j++) {
			input_data[i][j] += tmp;
			input_data[i][j] /= 2*tmp;
		}
	}
}

int main() {
	int* size;
	NetWork hi;
	thread t2;
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
			for (int i = 0; i < k; i++) {
				hi.SetInput(input_data[i]);
				result = hi.forward_feed();
				error += fabs(result - answers[i])/answers.size();
				if (result != answers[i]) {
					hi.BackPropogation(answers[i]);
					hi.WeightsUpdater(0.05);
				}
			}
		} while (error > eps);
		hi.SaveWeights();
	}
	else {
		hi.ReadWeights();
	}
	end = clock();
	t = end - begin;
	cout << "TIME= " << t << endl;
	input_data[0] = { 0.287, 0.18, 0.227 };

	for (int i = 0; i < size[0]; i++) {
		input_data[0][i] += tmp;
		input_data[0][i] /= 2*tmp;
	}

	hi.SetInput(input_data[0]);
	double hell;
	hell= hi.forward_feed();
	hell *= tmp * 2;
	hell -= tmp;
	cout << hell;
	return 0;
}

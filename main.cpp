#include <iostream>
#include <string>
#include "Brownian.h"
#include "Price.h"
#include "MC.h"
#include <armadillo>
#include <ctime>

using namespace std;
using namespace arma;

int main(int argc, char const *argv[])
{
	
	if(argc!=2) {
		cout << "Error: usage is ./main <precision>" << endl;
		return 1;
	}

	vector<double> strike;
	strike.push_back(80);
	strike.push_back(90);
	strike.push_back(100);
	strike.push_back(110);
	strike.push_back(120);

	MC monteCarlo(strike, atof(argv[1]));

	cout << "MC estimator" << endl;
	monteCarlo.printResults();

	cout << endl << "Antithetic method" << endl;
	monteCarlo.printAntithetic();

	return 0;
}
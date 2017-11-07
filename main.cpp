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

/*	Price p;
	clock_t begin = clock();
	for(int i(0);i<100000;i++) {
		p();
	}
	cout << double(clock() - begin) / CLOCKS_PER_SEC << endl;

	begin = clock();
	for(int i(0);i<100000;i++) {
		p.antithetic();
	}
	cout << double(clock() - begin) / CLOCKS_PER_SEC << endl;
*/

/*	Price p;
	cout << p.antithetic() << endl;
*/
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
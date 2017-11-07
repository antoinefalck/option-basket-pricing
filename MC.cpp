#include "MC.h"

using namespace std;
using namespace arma;

MC::MC(vector<double> strike, double precision, string s_weights, int dimension, double maturity, string s_correlation, double interest_rate, string s_spot, string s_sigma): m_precision(precision), m_strike(strike) {
	Price p(dimension, maturity, s_correlation, interest_rate, s_spot, s_sigma);
	m_price = p;

	m_weights.load(s_weights, raw_ascii);

	int nbSim(10000);
	double option(0), squareOption(0), index;
	for(int i(0);i<nbSim;i++) {
		index = as_scalar(m_weights.t()*p());
		option += index;
		squareOption += index*index;
	}
	double var = 1/(double(nbSim)-1)*squareOption - nbSim/(double(nbSim)-1)/nbSim/nbSim*option*option;

	m_number_simulations = 4*var/m_precision/m_precision;
	m_number_simulations_antithetic = 2*var/m_precision/m_precision;
}

vector<double> MC::operator()() {
	vector<double> mc(m_strike.size());

	double index;
	for(int i(0);i<m_number_simulations;i++) {
		index = as_scalar(m_weights.t()*m_price());
		for(int j(0);j<mc.size();j++) {
			mc[j] += max(index-m_strike[j],0.0);
		}
	}
	for(int j(0);j<mc.size();j++) {
		mc[j] /= double(m_number_simulations);
		mc[j] = round(mc[j]/m_precision)*m_precision;
	}

	return mc;
}

vector<double> MC::antithetic() {
	vector<double> mc(m_strike.size());

	mat prices;
	double index, antiIndex;
	for(int i(0);i<m_number_simulations_antithetic;i++) {
		prices = m_price.antithetic();
		index = as_scalar(m_weights.t()*prices.col(0));
		antiIndex = as_scalar(m_weights.t()*prices.col(1));
		for(int j(0);j<mc.size();j++) {
			mc[j] += 0.5 * (max(index-m_strike[j],0.0)+max(antiIndex-m_strike[j],0.0));
		}
	}
	for(int j(0);j<mc.size();j++) {
		mc[j] /= double(m_number_simulations_antithetic);
		mc[j] = round(mc[j]/m_precision)*m_precision;
	}

	return mc;
}

/**
 *	\example output_mc.txt
 *	Here is an example of the output of MC estimation.
 */
void MC::printResults() {
	clock_t begin = clock();
	vector<double> estimator = operator()();
	double elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;

	cout << endl << "Strike\t|  ";
	for(int i(0);i<m_strike.size();i++) {
		cout << m_strike[i] << "\t\t";
	}
	cout << endl << "-----------------------------------------------------------------------------" << endl;
	cout << "Est.\t|  ";
	for(int i(0);i<estimator.size();i++) {
		cout << estimator[i] << "\t\t";
	}
	cout << endl << endl;
	cout << "Precision:\t\t" << m_precision << endl;
	cout << "Nb simulations:\t\t" << m_number_simulations << endl;
	cout << "Computation time:\t" << elapsed_secs << endl;
}

void MC::printAntithetic() {
	clock_t begin = clock();
	vector<double> estimator = antithetic();
	double elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;

	cout << endl << "Strike\t|  ";
	for(int i(0);i<m_strike.size();i++) {
		cout << m_strike[i] << "\t\t";
	}
	cout << endl << "-----------------------------------------------------------------------------" << endl;
	cout << "Est.\t|  ";
	for(int i(0);i<estimator.size();i++) {
		cout << estimator[i] << "\t\t";
	}
	cout << endl << endl;
	cout << "Precision:\t\t" << m_precision << endl;
	cout << "Nb simulations:\t\t" << m_number_simulations_antithetic << endl;
	cout << "Computation time:\t" << elapsed_secs << endl;
}

long MC::getNumberSimulations() {
	return m_number_simulations;
}

long MC::getNumberSimulationsAntithetic() {
	return m_number_simulations_antithetic;
}
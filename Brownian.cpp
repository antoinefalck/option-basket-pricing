#include "Brownian.h"

using namespace std;
using namespace arma;

Brownian::Brownian(int dimension, double maturity, string s_correlation): m_dimension(dimension), m_maturity(maturity) {
	m_correlation.load(s_correlation, raw_ascii);
}

vec Brownian::operator()() {
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<double> normal_density(0, m_maturity);

	vec Z(m_dimension);
	for(int i(0);i<m_dimension;i++) {
		Z[i] = normal_density(gen);			// N(0,I_d) gaussian vector
	}

	mat T(m_maturity*m_correlation);		// From correlation matrix to covariance matrix
	T = chol(T, "lower");					// Cholesky decomposition

	return T*Z;
}

mat Brownian::opposite() {
	mat B(m_dimension,2);

	B.col(0) = operator()();
	B.col(1) = -B.col(0);

	return B;
}

int Brownian::getDimension() {
	return m_dimension;
}

int Brownian::getMaturity() {
	return m_maturity;
}
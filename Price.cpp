#include "Price.h"

using namespace std;
using namespace arma;


Price::Price(int dimension, double maturity, string correlation, double interest_rate, string s_spot, string s_sigma): m_interest_rate(interest_rate) {
	Brownian b(dimension, maturity, correlation);
	m_brownian = b;

	m_spot.load(s_spot, raw_ascii);
	m_sigma.load(s_sigma, raw_ascii);
}

vec Price::operator()() {
	int dimension = m_brownian.getDimension();
	int maturity = m_brownian.getMaturity();

	vec P;
	P = m_spot % exp((m_interest_rate*ones(dimension) - 0.5*square(m_sigma))*maturity + m_sigma % m_brownian());

	return P;
}

mat Price::antithetic() {
	int dimension = m_brownian.getDimension();
	int maturity = m_brownian.getMaturity();
	mat P(dimension, 2);
	mat brownian = m_brownian.opposite();

	P.col(0) = m_spot % exp((m_interest_rate*ones(dimension) - 0.5*square(m_sigma))*maturity + m_sigma % brownian.col(0));
	P.col(1) = m_spot % exp((m_interest_rate*ones(dimension) - 0.5*square(m_sigma))*maturity + m_sigma % brownian.col(1));

	return P;
}

Brownian Price::getBrownian() {
	return m_brownian;
}
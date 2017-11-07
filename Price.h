#ifndef DEF_PRICE
#define DEF_PRICE

#include "Brownian.h"
#include <armadillo>
#include <string>

/**
 *	Price of a basket of underlyings.
 *	Prices of \f$d\f$ underlyings \f$(S^1,\dots,S^d)\f$ that follow a multidimentional Black-Scholes model, i.e.
 *	\f$\forall i\in\llbracket1,d\rrbracket\f$, the underlying \f$(S^i_t)_{t\in[0,T]}\f$ follows the SDE
 *	\f[
 *		\mathrm dS_t^i\ =\ rS_t^i\,\mathrm dt\ +\ \sigma_iS_t^i\,\mathrm dW_t^i\,,\qquad\qquad S_0^i=s_0^i\in\mathbb R\,,
 *	\f]
 *	where \f$r>0\f$ is the risk free interest rate and \f$\sigma_i\f$ is the volatility of the \f$i\f$-th underlying.
 */

class Price {
public:

	/**
	 *	Contructor of the price.
	 *	@param m_dimension the number of prices, by default 10.
	 *	@param m_maturity the maturity of the prices, by default one year.
	 *	@param s_correlation file name that contains the correlation matrix \f$\rho\f$ of the Brownian motion.
	 *	@param m_interest_rate the interest rate \f$r\f$, by default 0.1.
	 *	@param s_spot the file name that contains the spots \f$s_0^i\f$.
	 *	@param s_sigma the file name that contains the volatilities \f$\sigma_i\f$.
	 */
	Price(int m_dimension=10, double m_maturity=1, std::string s_correlation="./data/data_correlation.txt", double m_interest_rate=0.1, std::string s_spot="./data/data_spot.txt", std::string s_sigma="./data/data_sigma.txt");
	
	/**
	 *	Simulate the prices \f$(S_T^1,\dots,S_T^d)\f$.
	 *	The underlyings follow a Black and Scholes model, hence the price is
	 *	\f[
	 *		S_T^i\ =\ s_0^i\exp\left(\left(r-\frac{1}{2}\sigma_i^2\right)T\ +\ \sigma_iW_T^i\right)\,,\qquad\qquad\forall i\in\llbracket1,d\rrbracket.
	 *	\f]
	 */
	arma::vec operator()();

	/**
	 *	Simulate the prices for the antithetic method. The first column of the matrix is simulated with the Brownian motion \f$(W^1_T,\dots,W^d_T)\f$,
	 *	while the second is simulated with \f$(-W^1_T,\dots,-W^d_T)\f$.
	 */
	arma::mat antithetic();

	/**
	 *	Return the Brownian motion \f$(W_T^1,\dots,W_T^d)\f$.
	 */
	Brownian getBrownian();

private:
	double m_interest_rate;
	arma::vec m_spot;
	arma::vec m_sigma;
	Brownian m_brownian;
};

#endif
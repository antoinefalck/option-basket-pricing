#ifndef DEF_MC
#define DEF_MC

#include <ctime>
#include <vector>
#include <string>
#include <armadillo>
#include <cmath>
#include "Price.h"

/**
 *	Monte Carlo estimator of the option basket.
 *	We define a call option on an index \f$I_t\f$ defined by for all \f$t\in[0,T]\f$,
 *	\f[
 *		I_t\ :=\ \sum_{i=1}^da_iS_t^i\,,
 *	\f]
 *	with \f$\sum_{i=1}^da_i=1\f$. The payoff is \f$(I_T-K)^+\f$, we then want to estimate the price without
 *	actualisation, i.e.
 *	\f[
 *		\mathbb E\left[(I_T-K)^+\right].
 *	\f]
 */

class MC {
public:

	/**
	 *	Constructor of the Monte Carlo estimator.
	 *	The estimator is in the interval \f$I_M\f$ at a level \f$\alpha\approx95\%\f$, defined by
	 *	\f[
	 *		I_M\ =\ \left[\bar X_M-q_\alpha\sqrt{\frac{\bar V_M}{M}},\bar X_M+q_\alpha\sqrt{\frac{\bar V_M}{M}}\right]\,,
	 *	\f]
	 *	with \f$M\f$ the number of simulations, \f$q_\alpha=2\f$ the quantile associated to \f$\mathbb P\{|\mathcal N(0,1)|<q_\alpha\}=\alpha\f$ and
	 *	\f{eqnarray*}{
	 *		\bar X_M&:=&\frac{1}{M}\sum_{i=1}^MX_i\ ;\\
	 *		\bar V_M&:=&\frac{1}{M-1}\sum_{i=1}^M\left(X_i-\bar X_i\right)^2.
	 *	\f}
	 *	Then the price of the option is in the interval \f$[m-\varepsilon,m+\varepsilon]\f$ with a confidence level \f$\alpha\f$
	 *	iff \f$M=\frac{q_\alpha^2\sigma_X}{\varepsilon^2}\f$, so for our computation with \f$\alpha=95\%\f$,
	 *	\f[
	 *		M(\varepsilon)\ =\ \frac{4\bar V_{10000}}{\varepsilon^2}.
	 *	\f]
	 *	@param m_strike the vector of strikes we want to calculate the price on.
	 *	@param m_precision the precision \f$\varepsilon\f$ of the prices desired, by default 0.1
	 *	@param s_weights the file name that contains the weights \f$a_i\f$.
	 *	@param m_dimension the number of underlyings in the basket, by default 10.
	 *	@param m_maturity the maturity of the option, by default one year.
	 *	@param s_correlation the file name that contains the correlation matrix of the Brownian motion.
	 *	@param m_interest_rate the risk free interest rate, by default 0.1.
	 *	@param s_spot the file name that contains the spots of the underlying.
	 *	@param s_sigma the file name that contains the volatilities of the underlyings.
	 */
	MC(std::vector<double> m_strike, double m_precision=1e-1, std::string s_weights="./data/data_weights.txt", int m_dimension=10, double m_maturity=1, std::string s_correlation="./data/data_correlation.txt", double m_interest_rate=0.1, std::string s_spot="./data/data_spot.txt", std::string s_sigma="./data/data_sigma.txt");
	
	/**
	 *	Compute the Monte Carlo estimator for each strike.
	 */
	std::vector<double> operator()();

	/**
	 *	Compute the Monte Carlo estimator with the antithetic method. We apply the Monte Carlo method on \f$\chi:=\frac{X+X'}{2}\f$, where
	 *	\f$X:=\left(S_T^1-K\right)^+\f$ and \f$X':=\left(S_T^2-K\right)^+\f$. The prices \f$S_T^1\f$ and \f$S_T^1\f$ are computed with
	 *	Price::antithetic(), i.e. with the Brownian motion \f$(W_T^1,\dots,W_T^d)\f$, respectively \f$(-W_T^1,\dots,-W_T^d)\f$. With this method
	 *	for a same precision the number of simulations is reduced by two, without additional computing cost, for details see
	 *	getNumberSimulationsAntithetic().
	 */
	std::vector<double> antithetic();	

	/**
	 *	Print the results of the estimation.
	 *	Print the prices of calls for different strikes with the precision \f$\varepsilon\f$, also prints the number of simulation
	 *	needed to perform the estimation and the time of computation.
	 */
	void printResults();

	/**
	 *	Print the results of the estimation.
	 *	See the printResults() method for details.
	 */
	void printAntithetic();

	/**
	 *	Return the number of simulation \f$M(\varepsilon)\f$ associated to the precision \f$\varepsilon\f$.
	 */
	long getNumberSimulations();

	/**
	 *	Return the number of simulation \f$M(\varepsilon)\f$ for the antithetic method. One can show that for the antithetic method, for a
	 *	given precision \f$\varepsilon\f$, the number of simulations associated is
	 *	\f{eqnarray*}{
	 *		M&=&\left(\frac{q_\alpha}{\varepsilon}\right)^2\mathrm{Var}(\chi)\\
	 *			&=&\left(\frac{q_\alpha}{\varepsilon}\right)^2\frac{\mathrm{Var}(X)+\mathrm{Cov}(X,X')}{2}\,,
	 *	\f}
	 *	with \f$\chi:=\frac{X+X'}{2}\f$. For specifications on \f$X\f$ and \f$X'\f$ see antithetic(). We just recall that \f$\mathrm{Cov}(X,X')=-1\f$,
	 *	hence for our computation with \f$\alpha=95\%\f$,
	 *	\f{eqnarray*}{
	 *		M_{anti}&=&\frac{2(\bar V_{10000}-1)}{\varepsilon^2}\\
	 *			&\approx&\frac{M_{MC}}{2}.
	 *	\f}
	 */
	long getNumberSimulationsAntithetic();

private:
	long m_number_simulations;
	long m_number_simulations_antithetic;
	double m_precision;
	arma::vec m_weights;
	Price m_price;
	std::vector<double> m_strike;
};

#endif
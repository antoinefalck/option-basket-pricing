#ifndef DEF_BROWNIAN
#define DEF_BROWNIAN

#include <iostream>
#include <string>
#include <random>
#include <armadillo>

/** 
 *	Multi-dimensional brownian motion.
 *	Simulates the result at the maturity \f$T\f$ of a \f$d\f$-dimensional Brownian motion on \f$\mathbb R^d\f$,
 *  centered and with correlation matrix \f$\rho\in[-1,1]^{2d}\f$ s.t.
 *  \f[ 
 *		\mathrm d\langle W^i,W^j\rangle_t\ =\ \rho_{i,j}\,\mathrm dt\ ,\qquad\qquad\rho_{i,j}\in[-1,1].
 *  \f]
 */

class Brownian {
public:

	/**
	 *	Constructor of the Brownian motion.
	 *	@param m_dimension by default sets the dimension to 10.
	 *	@param m_maturity by default sets the maturity to one year.
	 *	@param s_correlation the file name that contains the correlation matrix.
	 */
	Brownian(int m_dimension=10, double m_maturity=1, std::string s_correlation="./data/data_correlation.txt");

	/**
	 *	Simulate the vector \f$(W^1_T,\dots,W^d_T)\f$.
	 */
	arma::vec operator()();

	/**
	 *	Simulate the Brownian motion and its opposite. The first column of the matrix is the simulation of \f$(W^1_T,\dots,W^d_T)\f$ and the second
	 *	is \f$(-W^1_T,\dots,-W^d_T)\f$, hence without additional cost. This method is used for the antithetic method of estimation.
	 */
	arma::mat opposite();

	/**
	 *	Return the dimension \f$d\f$ of the Brownian motion.
	 */
	int getDimension();

	/**
	 *	Return the maturity \f$T\f$ of the simulation.
	 */
	int getMaturity();

private:
	int m_dimension;
	double m_maturity;
	arma::mat m_correlation;
};

#endif
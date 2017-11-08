# Option Basket pricing

This program enables you to price an option basket, *i.e.* an option on an index. It uses a 
classic Monte Carlo estimator and the antithetic method.

## Compile

### Prerequisite

Note that you have to have `C++11` installed on your computer. If you're working on Linux it is possible that you have
to specify the option `-std=c++11` in the Makefile.

To run the program you also need the linear algebra library `Armadillo` that you can download [here](http://arma.sourceforge.net/download.html).

### Make

To use the program, download this repository, in a terminal `cd` to the right folder, for GNU/Linux and Mac type `make`.

Then to exectute with the preloaded datas:
```
./main <precision>
```

For a first test I suggest to use the precision `1e-1`.

## Data

I preloaded some data, *e.g.* the correlation matrix, the spot prices, *etc.* which are in the `data` folder. These data are stored in
`.txt` files.

By default the basket dimension is 10, you can change this in the constructors, but of cours you will also have to change the 
matrix and vectors dimensions. For further details see the complete documentation on my [website](http://www.antoine-falck.fr) in the section
`Other Probability and Statistics work`.

## The estimators

The Monte Carlo object has two methods for estimating the price
- a classic Monte Carlo estimator using the Law of Large Numbers
- the antithetic method, by considering the opposite Brownian motion
For details on the code, all the information you need is in the complete documentation on my [website](http://www.antoine-falck.fr)
in the section `Other Probability and Statistics work`.

If you want more details on the maths behind these estimation methods, you can read the lecture note for `Numerical Probability
for Finance` also on my [website](http://www.antoine-falck.fr).

## Outputs

The price outputs are in a very simple format
```
Strike	|  80		90		100		110		120	
-----------------------------------------------------------------------------
Est.	|  31.2		22.7		15.5		10.1		6.2	

Precision:		0.1
Nb simulations:		250731
Computation time:	4.7775
```

## Contact

For issues don't hesitate to [email](mailto:antoine.falck@gmail.com) me.

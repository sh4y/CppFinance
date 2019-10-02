// QuoteGetter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "portfolio_object.h"

using std::cout;
using std::endl;


int main()
{
	string stock_name = "KO";
	string index_name = "SPY";

	// Build stock objects
	StockObject stock(stock_name);
	StockObject index(index_name);

	PortfolioObject KO(stock, 35, "2016-06-06");
	PortfolioObject SPY(index, 35, "2016-06-06");

	Portfolio pf;
	pf.AddHolding(KO);
	pf.AddHolding(SPY);

	/*double ogVal = pf.getPortfolioValueAtDate("2016-06-06");
	double newVal = pf.getPortfolioValueAtDate("2017-06-06");*/

	auto ss = stock.GetDataSubsetBetweenDates("2016-06-06", "2017-06-06");
	auto percentChanges = ss.Close.GetPercentChangesFromDateToDate("2016-06-06", "2017-06-06");
	auto var = Variance(percentChanges);
	auto std = StandardDev(percentChanges);
	return 0; 
}
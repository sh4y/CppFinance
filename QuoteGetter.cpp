// QuoteGetter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stock_object.h"

using std::cout;
using std::endl;


int main()
{
	string stock_name = "KO";
	string index_name = "SPY";

	// Build stock objects
	StockObject stock(stock_name);
	StockObject index(index_name);

	//stock.getDataAtDate("2010-10-14");
<<<<<<< HEAD
	auto result = stock.getMonthlyClosingPrices();

	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}
=======
	StockObject ss = stock.GetDataSubsetBetweenDates("2010-10-14", "2010-10-26");
	auto date = ss.Date;

	double cr = ss.Close.CumulativeReturn();
>>>>>>> 7fa938c3f023961116d9e4bc22a52d88f7a1cce9
	
	return 0;
}
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
	StockObject ss = stock.GetDataSubsetBetweenDates("2010-10-14", "2013-10-23");

	auto weeklyDate = getNDayDatapoints(7, ss.Date);
	auto weeklyPrices = ss.Close.getNDayDatapoints(7);

	return 0;
}
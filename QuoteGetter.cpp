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
	auto result = stock.GetPercentChanges();
	

	
	return 0;
}
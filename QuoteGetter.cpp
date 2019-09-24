// QuoteGetter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stock_object.h"

using std::cout;
using std::endl;


int main()
{
	string stock_name = "KO";
	string index_name = "SPY";

	stock_object stock(stock_name);
	stock_object index(index_name);

	
	
	return 0;
}
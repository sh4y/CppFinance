#pragma once
#include "stock_object.h"

struct PortfolioObject {
private:
	double purchasePrice;
	string purchaseDate;

public:
	StockObject stock;
	double quantity;

	double getHoldingValueAtDate(string _date) {
		auto data = stock.getDataPointAtDate(_date);
		double closingPrice = data[3];
		return closingPrice * quantity;
	}

	double getPurchaseValue() {
		return purchasePrice * quantity;
	}

	/* Constructors */

	PortfolioObject() {

	}

	PortfolioObject(StockObject _stock, double _quantity, string _date) {
		purchaseDate = _date;
		purchasePrice = _stock.getDataPointAtDate(_date)[3];
		stock = _stock;
		quantity = _quantity;
	}
};

struct Portfolio {
public:
	vector<PortfolioObject> holdings;

	void AddHolding(PortfolioObject h) {
		holdings.push_back(h);
	}

	double getPortfolioValueAtDate(string _date) {
		if (holdings.empty())
			return 0.0;

		double result = 0;		
		for (int i = 0; i < holdings.size(); i++) {
			result += holdings[i].getHoldingValueAtDate(_date);
		}

		return result;
	}

	/* Constructors */

	Portfolio() {

	}
};
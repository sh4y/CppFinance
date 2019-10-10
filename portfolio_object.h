#pragma once
#include "stock_object.h"

struct PortfolioObject {
private:
	double purchasePrice{};
	string purchaseDate;

public:
	StockObject stock;
	double quantity;

	string getPurchaseDate() {
		return purchaseDate;
	}

	double getHoldingValueAtDate(string _date) {
		auto data = stock.getDataPointAtDate(_date);
		double closingPrice = data[3];
		return closingPrice * quantity;
	}

	double getPurchaseValue() {
		return purchasePrice * quantity;
	}

	double ParkinsonVolatility() {
		int numDays = stock.Date.size();
		double innerSum = 0;
		for (int i = 0; i < numDays; i++) {
			innerSum += pow(log(stock.High.data[i] / stock.Low.data[i]),2);
		}
		return (innerSum / (4 * numDays * log(2)));
	}

	/* Constructors */

	PortfolioObject(): purchasePrice(0), quantity(0)
	{
	}

	PortfolioObject(StockObject _stock, double _quantity, string _date) {
		purchaseDate = _date;
		purchasePrice = _stock.getDataPointAtDate(_date)[3];
		stock = _stock;
		quantity = _quantity;
	}
};

struct Portfolio {
private:
	vector<double> getPortfolioWeights(string date) {
		//string _date = "2017-06-06";
		double pfValue = getPortfolioValueAtDate(date);
		vector <double> weights;
		for (int i = 0; i < holdings.size(); i++) {
			auto holdingValue = holdings[i].getHoldingValueAtDate(date);
			auto weight = holdingValue / pfValue;

			weights.push_back(weight);
		}

		return weights;
	}
public:
	vector<PortfolioObject> holdings{};

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

	double getPortfolioReturnsAtDate(string endDate) {
		auto weights = getPortfolioWeights(endDate);
		double finalReturn = 0;
		double pfoReturn, weightedReturn;
		for (int i = 0; i < holdings.size(); i++) {
			auto purchaseDate = holdings[i].getPurchaseDate();

			pfoReturn = holdings[i].stock.Close.CumulativeReturn(purchaseDate, endDate);
			weightedReturn = pfoReturn * weights[i];

			finalReturn += weightedReturn;
		}

		return finalReturn;
	}

	/* Constructors */

	Portfolio() {

	}
};
#pragma once
#include <numeric>
#include "datatools.h"

// only closing prices for now

struct DataContainer
{
private:
	vector<double> PercentChangeFromDate(string date, vector<double> _closing_prices, vector<string> dates, bool asPercent = false) {

		if (_closing_prices.size() != dates.size()) {
			throw;
		}

		int index = getIndexOfDate(date, dates);
		vector<double> percents;
		auto closing_prices = vector<double>(_closing_prices.begin() + index, _closing_prices.end());
		double today, tomorrow, pct;
		for (int i = index; i < closing_prices.size() - 1; i++) {
			today = closing_prices[i];
			tomorrow = closing_prices[i + 1];
			pct = (tomorrow - today) / today;
			pct = asPercent ? pct * 100.0 : pct;
			percents.push_back(pct);
		}
		return percents;
	}

	double Sum(vector<double> data) {
		return std::accumulate(data.begin(), data.end(), 0.0);
	}

	double MomentSum(vector<double> data, int n) {
		double mean = SampleMean(data);
		vector<double> diff;
		for (int i = 0; i < data.size(); i++) {
			diff.push_back(pow(data[i] - mean, n));
		}
		return Sum(diff);
	}

public:
	vector<double> data;
	vector<string> Date;

	DataContainer()
	{

	}

	DataContainer(vector<double> _data, vector<string> _date)
	{
		Date = _date;
		data = _data;
	}

	vector<double> GetPercentChanges(bool asPercent = false) {
		return PercentChangeFromDate(Date[0], data, Date, asPercent);
	}

	vector<double> GetPercentChangesFromDate(string date, bool asPercent = false) {
		return PercentChangeFromDate(date, data, Date, asPercent);
	}

	vector<double> LogPercentChangeFromDate(string date, vector<string> dates) {
		auto percents = PercentChangeFromDate(date, data, dates);
		for (int i = 0; i < percents.size(); i++) {
			percents[i] = log(percents[i]);
		}

		return percents;
	}

	vector<double> GrossReturnsChange(vector<double> _closing_prices)
	{
		vector<double> returns;
		for (int i = 0; i < _closing_prices.size() - 1; i++)
		{
			returns.push_back(_closing_prices[i + 1] - _closing_prices[i]);
		}

		return returns;
	}

	double CumulativeReturn()
	{
		double cumulativeReturn = 1;
		auto _pctchange = GetPercentChanges();
		
		for (int i = 0; i < _pctchange.size(); i++)
		{
			cumulativeReturn *= (1 + _pctchange[i]);
		}

		return cumulativeReturn;
	}

	double SampleMean(vector<double> data) {
		auto sum = Sum(data);
		return sum / data.size();
	}

	double Variance(vector<double> data) {
		double denom = data.size() - 1;
		double num = MomentSum(data, 2);
		return num / denom;
	}

	double StandardDev(vector<double> data) {
		return sqrt(Variance(data));
	}

	double Skewness(vector<double> data) {
		double stdev = StandardDev(data);
		double num = MomentSum(data, 3);
		double dem = (data.size() - 1) * pow(stdev, 3);
		return num / dem;
	}

	double Kurtosis(vector<double> data) {
		double stdev = StandardDev(data);
		double num = MomentSum(data, 4);
		double dem = (data.size() - 1) * pow(stdev, 4);
		return num / dem;
	}
};
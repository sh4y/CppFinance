#pragma once
#include <numeric>
#include "datatools.h"

// only closing prices for now

struct DataContainer
{
private:
	vector<double> PercentChangeFromDateToDate(string fromDate, string toDate, vector<double> _closing_prices, vector<string> dates, bool asPercent = false) {

		if (_closing_prices.size() != dates.size()) {
			throw;
		}

		int startIndex = getIndexOfDate(fromDate, dates);
		int endIndex = getIndexOfDate(toDate, dates);

		vector<double> percents;
		auto closing_prices = vector<double>(_closing_prices.begin() + startIndex, _closing_prices.begin() + endIndex +1);
		double today, tomorrow, pct;
		for (int i = 0; i < closing_prices.size()-1; i++) {
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
		double mean = SampleMean();
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
		return PercentChangeFromDateToDate(Date[0], Date.back(), data, Date, asPercent);
	}

	vector<double> GetPercentChangesFromDateToDate(string date1, string date2, bool asPercent = false) {
		return PercentChangeFromDateToDate(date1, date2, data, Date, asPercent);
	}

	vector<double> LogPercentChangeFromDateToDate(string date1, string date2, vector<string> dates) {
		auto percents = PercentChangeFromDateToDate(date1, date2, data, dates);
		for (int i = 0; i < percents.size(); i++) {
			percents[i] = log(percents[i]);
		}

		return percents;
	}


	vector<double> getNDayDatapoints(int n) {
		if (n <= data.size()) {
			return data;
		}

		vector<double> result;
		for (int i = 0; i < data.size(); i += n) {
			result.push_back(data[i]);
		}

		return result;
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

	double CumulativeReturn(string fromDate, string toDate)
	{
		vector<double> _pctchange;
		_pctchange = GetPercentChangesFromDateToDate(fromDate, toDate);

		double cumulativeReturn = 1;
		
		for (int i = 0; i < _pctchange.size(); i++)
		{
			cumulativeReturn *= (1 + _pctchange[i]);
		}

		return cumulativeReturn;
	}

	double SampleMean() {
		auto sum = Sum(data);
		return sum / data.size();
	}

	double Variance() {
		double denom = data.size() - 1;
		double num = MomentSum(data, 2);
		return num / denom;
	}

	double StandardDev() {
		return sqrt(Variance());
	}

	double Skewness() {
		double stdev = StandardDev();
		double num = MomentSum(data, 3);
		double dem = (data.size() - 1) * pow(stdev, 3);
		return num / dem;
	}

	double Kurtosis() {
		double stdev = StandardDev();
		double num = MomentSum(data, 4);
		double dem = (data.size() - 1) * pow(stdev, 4);
		return num / dem;
	}
};
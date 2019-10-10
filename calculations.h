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

	vector<double> GetPercentChanges(bool asPercent = true) {
		return PercentChangeFromDateToDate(Date[0], Date.back(), data, Date, asPercent);
	}

	vector<double> GetPercentChangesFromDateToDate(string date1, string date2, bool asPercent = true) {
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
};


double Sum(vector<double> data) {
	return std::accumulate(data.begin(), data.end(), 0.0);
}

double SampleMean(vector<double> _data) {
	auto sum = Sum(_data);
	return sum / _data.size();
}

double MomentSum(vector<double> _data, int n) {
	double mean = SampleMean(_data);
	vector<double> diff;
	for (int i = 0; i < _data.size(); i++) {
		diff.push_back(pow(_data[i] - mean, n));
	}
	return Sum(diff);
}

double Variance(vector<double> _data) {
	double denom = _data.size() - 1;
	double num = MomentSum(_data, 2);
	return num / denom;
}

double Covariance(vector<double> _data1, vector<double> _data2) {
	if (_data1.size() != _data2.size())
		throw;

	double d1Mean = SampleMean(_data1);
	double d2Mean = SampleMean(_data2);
	int n =  _data1.size();
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (_data1[i] - d1Mean) * (_data2[i] - d2Mean);
	}
	return sum / (n - 1);
}

//TODO: Build Covariance Matrix	


double StandardDev(vector<double> _data) {
	return sqrt(Variance(_data));
}

double Skewness(vector<double> _data) {
	double stdev = StandardDev(_data);
	double num = MomentSum(_data, 3);
	double dem = (_data.size() - 1) * pow(stdev, 3);
	return num / dem;
}

double Kurtosis(vector<double> _data) {
	double stdev = StandardDev(_data);
	double num = MomentSum(_data, 4);
	double dem = (_data.size() - 1) * pow(stdev, 4);
	return num / dem;
}
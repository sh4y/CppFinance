#include <fstream>
#include <iostream>
#include "datatools.h"
#include "calculations.h"

using std::ifstream;

struct StockObject {
	private:
		void fillStockDataFromFile() {
			bool opened_header = false;
			ifstream stock_file("data/" + ticker + ".csv");
			std::string line;

			if (stock_file.is_open()) {
				while (std::getline(stock_file, line)) {
					if (!opened_header) {
						opened_header = !opened_header;
						continue;
					}
					else {
						line_object lineObj = parseLine(line);
						vector<double> line_data = lineObj.data;
						string line_date = lineObj.date;

						Date.push_back(line_date);
						Open.push_back(line_data[0]);
						High.push_back(line_data[1]);
						Low.push_back(line_data[2]);
						Close.push_back(line_data[3]);
						Volume.push_back(line_data[4]);
					}
				}

				stock_file.close();
			}
		}

	public:
		string ticker;
		vector<string> Date;
		vector<double> Open;
		vector<double> Close;
		vector<double> Volume;
		vector<double> High;
		vector<double> Low;

		vector<double> getDataPointAtDate(string date) {
			vector<double> result;
			int index = getIndexOfDate(date, Date);
			if (index == -1)
				throw;

			result.push_back(Open[index]);
			result.push_back(High[index]);
			result.push_back(Low[index]);
			result.push_back(Close[index]);
			result.push_back(Volume[index]);
			

			return result;
		}

		// Percent change of stock price

		vector<double> GetPercentChanges(bool asPercent=false) {
			return PercentChangeFromDate(Date[0], Close, Date, asPercent);
		}

		vector<double> GetPercentChangesFromDate(string date, bool asPercent = false) {
			return PercentChangeFromDate(date, Close, Date, asPercent);
		}

		vector<double> GetLogChanges() {
			return LogPercentChangeFromDate(Date[0], Close, Date);
		}		
		
		vector<double> GetLogChangesFromDate(string date) {
			return LogPercentChangeFromDate(date, Close, Date);
		}

		double GetCumulativeReturnClosingPrices()
		{
			return CumulativeReturn(GetPercentChanges());
		}
		
		StockObject GetDataSubsetBetweenDates(string date1, string date2, bool inclusiveEnd=true) {
			int modifier = inclusiveEnd ? 1 : 0;

			int startIndex = getIndexOfDate(date1, Date);
			int endIndex = getIndexOfDate(date2, Date) + modifier;


			auto dateSubset = vector<string>(Date.begin() + startIndex, Date.begin() + endIndex);
			auto closeSubset = vector<double>(Close.begin() + startIndex, Close.begin() + endIndex);
			auto openSubset = vector<double>(Open.begin() + startIndex, Open.begin() + endIndex);
			auto volSubset = vector<double>(Volume.begin() + startIndex, Volume.begin() + endIndex);
			auto lowSubset = vector<double>(Low.begin() + startIndex, Low.begin() + endIndex);
			auto highSubset = vector<double>(High.begin() + startIndex, High.begin() + endIndex);

			return StockObject(ticker, dateSubset, closeSubset, openSubset,
				highSubset, lowSubset, volSubset);
		}

		double PriceChangeBetweenDate(string date1, string date2) {
			double p1 = getDataPointAtDate(date1)[3];
			double p2 = getDataPointAtDate(date2)[3];

			return (p2 - p1) / p1;
		}

		/* Constructors */
		
		StockObject(string stock_name) {
			ticker = stock_name;
			fillStockDataFromFile();
		}

		StockObject(string stock_name, vector<string> _date, vector<double> _close, vector<double> _open,
			vector<double> _high, vector<double> _low, vector<double> _vol) {
			ticker = stock_name;
			Close = _close;
			Open = _open;
			High = _high;
			Date = _date;
			Volume = _vol;
			Low = _low;
		}
};


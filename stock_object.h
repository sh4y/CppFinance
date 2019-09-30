#include <fstream>
#include <iostream>
#include "calculations.h"

using std::ifstream;

struct StockObject {
	private:
		vector<double> MonthlyDates;
		vector<double> MonthlyClosingPrices;

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

						char dt[11];
						strcpy_s(dt, line_date.c_str());
						string day = "";
						day = string(1, dt[8]) + string(1, dt[9]);

						if (day == "01") {
							MonthlyClosingPrices.push_back(line_data[3]);
						}

						Date.push_back(line_date);
						
						Open.data.push_back(line_data[0]);
						High.data.push_back(line_data[1]);
						Low.data.push_back(line_data[2]);
						Close.data.push_back(line_data[3]);
						Volume.data.push_back(line_data[4]);
					}
				}

				Open.Date = Date;
				High.Date = Date;
				Low.Date = Date;
				Close.Date = Date;
				Volume.Date = Date;

				stock_file.close();
			}
		}

	public:
		string ticker;
		vector<string> Date;
		
		DataContainer Open;
		DataContainer Close;
		DataContainer Volume;
		DataContainer High;
		DataContainer Low;

		vector<double> getDataPointAtDate(string date) {
			vector<double> result;
			int index = getIndexOfDate(date, Date);
			if (index == -1)
				throw;

			result.push_back(Open.data[index]);
			result.push_back(High.data[index]);
			result.push_back(Low.data[index]);
			result.push_back(Close.data[index]);
			result.push_back(Volume.data[index]);
			

			return result;
		}
		
		StockObject GetDataSubsetBetweenDates(string date1, string date2, bool inclusiveEnd = true) {
			int modifier = inclusiveEnd ? 1 : 0;

			int startIndex = getIndexOfDate(date1, Date);
			int endIndex = getIndexOfDate(date2, Date) + modifier;

			auto dateSubset = vector<string>(Date.begin() + startIndex, Date.begin() + endIndex);
			auto closeSubset = vector<double>(Close.data.begin() + startIndex, Close.data.begin() + endIndex);
			auto openSubset = vector<double>(Open.data.begin() + startIndex, Open.data.begin() + endIndex);
			auto volSubset = vector<double>(Volume.data.begin() + startIndex, Volume.data.begin() + endIndex);
			auto lowSubset = vector<double>(Low.data.begin() + startIndex, Low.data.begin() + endIndex);
			auto highSubset = vector<double>(High.data.begin() + startIndex, High.data.begin() + endIndex);

			return StockObject(ticker, dateSubset, closeSubset, openSubset,
				highSubset, lowSubset, volSubset);
		}

		vector<double> getMonthlyClosingPrices() {
			return MonthlyClosingPrices;
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
			Close = DataContainer(_close, Date);
			Open = DataContainer(_open, Date);
			High = DataContainer(_high, Date);
			Date = _date;
			Volume = DataContainer(_vol, Date);;
			Low = DataContainer(_low, Date);;
		}
};


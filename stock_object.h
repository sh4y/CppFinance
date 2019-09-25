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
		
		StockObject(string stock_name) {
			ticker = stock_name;
			fillStockDataFromFile();
		}
};


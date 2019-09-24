#include <fstream>
#include <iostream>
#include "datatools.h"

using std::ifstream;

struct stock_object {
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

						Date = line_date;
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

		string Date;
		vector<double> Open;
		vector<double> Close;
		vector<double> Volume;
		vector<double> High;
		vector<double> Low;

		stock_object(string stock_name) {
			ticker = stock_name;
			fillStockDataFromFile();
		}
};


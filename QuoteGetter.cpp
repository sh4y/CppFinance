// QuoteGetter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "stdio.h"
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;

vector<double> parseLine(string line) {
	cout << line << endl;
	int line_length = line.size();
	char* characters = &line[0];
	vector<double> data;
	string temp = "";
	for (int i = 0; i < line_length + 1; i++) {
		if (characters[i] != ',' && characters[i] != '\n') {
			temp += characters[i];
		}
		else {
			double value = std::stod(temp);
			data.push_back(value);
		}
	}
	return data;
}

int main()
{
	ifstream stock_file ("data/ABBV.csv");
	ifstream index_file ("data/SPY.csv");

	int headers[2] = { false, false };

	std::string line;

	if (stock_file.is_open()) {
		while (std::getline(stock_file, line)) {
			if (!headers[0]) {
				headers[0] = !headers[0];
				continue;
			} else {
				vector<double> line_data = parseLine(line);
				
			}
		}

		stock_file.close();
	}
	return 0;
}
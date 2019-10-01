#include <vector>
#include <string>

using std::vector;
using std::string;

struct line_object {
public:
	string date;
	vector<double> data;

	line_object(string _date, vector<double> _data) {
		data = _data;
		date = _date;
	}
};

vector<string> getNDayDatapoints(int n, vector<string> data) {
	if (n >= data.size()) {
		return data;
	}

	vector<string> result;
	for (int i = 0; i < data.size(); i += n) {
		result.push_back(data[i]);
	}

	return result;
}

line_object parseLine(string line) {
	//cout << line << endl;
	int line_length = line.size();
	bool first_comma_hit = false;
	char* characters = &line[0];
	vector<double> data;
	string temp = "";
	string date = "";
	for (int i = 0; i < line_length + 1; i++) {
		if (characters[i] != ',' && characters[i] != '\n') {
			temp += characters[i];
		}
		else {
			if (!first_comma_hit) {
				first_comma_hit = true;
				date = temp;
			}
			else {
				double value = std::stod(temp);
				data.push_back(value);
			}
			temp = "";
		}
	}
	line_object result(date, data);
	return result;
}

int getIndexOfDate(string date, vector<string> Date) {
	vector<string>::iterator iter = std::find(Date.begin(), Date.end(), date);
	if (iter != Date.end()) {
		int index = std::distance(Date.begin(), iter);
		return index;
	}
	return -1;
}
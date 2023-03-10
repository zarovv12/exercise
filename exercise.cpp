
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::ifstream;
using std::string;
using std::vector;
using std::cout;
using std::endl;

#define XML_OPEN(STR) ("<" + (STR) + ">")
#define XML_CLOSE(STR) ("</" + (STR) + ">")

void parseXmlFile(const string& path, vector<vector<string> > &data) {

	/* Assuming same xml attributes we define constants */
	static const string _catalogStr = "CATALOG";
	static const string _cdStr = "CD";
	static const vector<string> _titles = {"TITLE"};

	ifstream file(path);
	string line;


	bool cdBlock = false;

	if (file.is_open()) {
		while (std::getline(file, line)) {

			if (line.find(XML_OPEN(_cdStr)) != string::npos) {
				data.emplace_back();
			} else if (line.find(XML_OPEN(_titles[0])) != string::npos) {

			}
		}

		file.close();

	} else {
		cout << "Failed opening file" << endl;
	}

//	std::stringstream ss(xmlString);
//	std::string line;
//	while (std::getline(ss, line)) {
//		if (line.find("<CD>") != std::string::npos) {
//			data.emplace_back();
//		} else if (line.find("<TITLE>") != std::string::npos) {
//			std::string title = line.substr(line.find(">") + 1,
//					line.rfind("<") - line.find(">") - 1);
//			data.back().push_back(title);
//		} else if (line.find("<ARTIST>") != std::string::npos) {
//
//		}
//	}
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Please provide xml path" << endl;
        return 1;
    }

    string path = argv[1];
    cout << "path: " << path << endl;

	vector<vector<string> > data;
	parseXmlFile(path, data);

	return 0;
}

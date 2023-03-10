
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::ifstream;
using std::string;
using std::vector;
using std::cerr;
using std::cout;
using std::endl;

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

void parseXmlFile(const string& path, vector<vector<string> > &data) {

	rapidxml::file<> file(path.c_str());
	if (!file.data()) {
	    cerr << "Could not open XML file" << endl;
	    return;
	}

	rapidxml::xml_document<> doc;
	doc.parse<0>(file.data());

	for (rapidxml::xml_node<> *cd = doc.first_node("CATALOG")->first_node("CD"); cd; cd = cd->next_sibling()) {

	    string title = cd->first_node("TITLE")->value();
	    string artist = cd->first_node("ARTIST")->value();
	    string company = cd->first_node("COMPANY")->value();
	    string country = cd->first_node("COUNTRY")->value();
	    double price = std::stod(cd->first_node("PRICE")->value());
	    int year = std::stoi(cd->first_node("YEAR")->value());

	    cout << "Title: " << title << endl;
	    cout << "Artist: " << artist << endl;
	    cout << "Company: " << company << endl;
	    cout << "Country: " << country << endl;
	    cout << "Price: " << price << endl;
	    cout << "Year: " << year << endl;
	}

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

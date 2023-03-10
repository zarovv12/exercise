
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>

using std::ifstream;
using std::ostream;
using std::string;
using std::vector;
using std::cerr;
using std::cout;
using std::endl;

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

#include "HTMLBuilder/HTML.h"

void parseXmlToHtml(const string& path) {

	rapidxml::file<> file(path.c_str());
	if (!file.data()) {
	    cerr << "Could not open XML file" << endl;
	    return;
	}

	rapidxml::xml_document<> doc;
    try {
        doc.parse<0>(file.data());
    } catch (const rapidxml::parse_error& e) {
        cerr << "Parsing failed of " << path << ": " << e.what() << endl;
        return;
    }

    static const vector<string> cols = {"TITLE", "ARTIST", "COMPANY", "COUNTRY", "PRICE", "YEAR"};

    HTML::Document htmlDoc("CDs");

    HTML::Table table;

    HTML::Row headerRow;
    for (const string& col : cols) {
    	headerRow << HTML::ColHeader(col.c_str());
    }

    /* Move to function parameter instead of copying the string */
    table << std::move(headerRow);

	for (rapidxml::xml_node<> *cd = doc.first_node("CATALOG")->first_node("CD"); cd; cd = cd->next_sibling()) {

		HTML::Row row;

		for (const string& col : cols) {
			rapidxml::xml_node<> *child = cd->first_node(col.c_str());
			if (child != nullptr) {
				row << HTML::Col(child->value());
			} else {
				/* No column so just setting N/A */
				row << HTML::Col("N/A");
			}
		}

		table << std::move(row);
	}

	htmlDoc << std::move(table);

	std::ofstream htmlFile("cds.html");
	htmlFile << htmlDoc << endl;
	htmlFile.close();
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Please provide xml path" << endl;
        return 1;
    }

    string path = argv[1];
	parseXmlToHtml(path);

	return 0;
}

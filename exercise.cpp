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
using std::runtime_error;
using std::stringstream;

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

#include "HTMLBuilder/HTML.h"

#define HTMLPath "cds.html"

void parseXmlToHtml(const string &path) {

	ifstream f(path.c_str());
	if (!f.good()) {
		stringstream ss;
		ss << "File " << path << " doesnt exists";
		throw runtime_error(ss.str());
	}

	f.close();

	rapidxml::file<> file(path.c_str());
	if (!file.data()) {
		throw runtime_error("Could not open XML file");
	}

	rapidxml::xml_document<> doc;
	try {
		doc.parse<0>(file.data());
	} catch (const rapidxml::parse_error &e) {
		stringstream ss;
		ss << "Parsing failed of " << path << ": " << e.what();
		throw runtime_error(ss.str());
	}

	static const vector<string> cols = { "TITLE", "ARTIST", "COMPANY",
			"COUNTRY", "PRICE", "YEAR" };

	HTML::Document htmlDoc("CDs");

	HTML::Table table;
	table.addAttribute("border", "1");

	HTML::Row headerRow;
	for (const string &col : cols) {
		headerRow << HTML::ColHeader(col.c_str());
	}

	/* Move to function parameter instead of copying the string */
	table << std::move(headerRow);

	for (rapidxml::xml_node<> *cd = doc.first_node("CATALOG")->first_node("CD");
			cd; cd = cd->next_sibling()) {

		HTML::Row row;

		for (const string &col : cols) {
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

	std::ofstream htmlFile(HTMLPath);
	htmlFile << htmlDoc << endl;
	htmlFile.close();
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		cout << "Please provide xml path" << endl;
		return 1;
	}

	string path = argv[1];
	cout << "Running parse on path " << path << endl;

	try {
		parseXmlToHtml(path);
	} catch (const std::exception &e) {
		cerr << e.what() << endl;
		return 1;
	} catch (...) {
		cerr << "Unknown exception" << endl;
		return 1;
	}

	cout << "All done. HTML file " << string(HTMLPath) << " created" << endl;

	return 0;
}

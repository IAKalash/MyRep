#include "HtmlGen.h"
#include <algorithm>

void HtmlGen::upperColontitul(int pageNum, ostream& out) {
    out << "<h1>Page " << pageNum << "</h1>\n";
    out << "<table>\n";
    out << "<tr><th>Key</th><th>Value</th></tr>\n";
}

void HtmlGen::lowerColontitul(int pageNum, ostream& out) {
    out << "</table>\n";
    out << "\n<p>Page " << pageNum << "</p>\n<hr>\n";
}

void HtmlGen::printLine(const pair<string, string>& line, ostream& out) {
    string key = line.first;
    string value = line.second;
    transform(key.begin(), key.end(), key.begin(), 
        [](unsigned char a) {return toupper(a);});
    transform(value.begin(), value.end(), value.begin(), 
        [](unsigned char a) {return tolower(a);});
    out << "<tr><td class=\"key\">" << key << "</td><td class=\"value\">" << value << "</td></tr>\n";
}

void HtmlGen::separator(ostream& out) {
    out << "<tr><td colspan=\"2\"><hr></td></tr>\n";
}

int HtmlGen::linesOnPage() const {
    return 5;
}

void HtmlGen::generate(const string &inputFile, const string &outputFile) {
    
    ofstream outFile(outputFile);

    outFile << "<html>\n<head>\n<style>\n";
    outFile << "body { font-family: Arial, sans-serif; }\n";
    outFile << "table { border-collapse: collapse; width: 50%; margin: 20px 0; }\n";
    outFile << "th, td { border: 1px solid black; padding: 8px; text-align: left; }\n";
    outFile << "th { background-color:rgb(179, 179, 179); }\n";
    outFile << ".key { color: navy; font-weight: bold; }\n";
    outFile << ".value { color: darkgreen; font-style: italic; }\n";
    outFile << "</style>\n</head>\n<body>\n";

    Generator::generate(inputFile, outFile);

    outFile << "</body>\n</html>\n";
    outFile.close();
}
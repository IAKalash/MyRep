#include "TextGen.h"
#include <algorithm>

void TextGen::upperColontitul(int pageNum, ostream& out) {
    out << "        " << pageNum << "\n\n";
}

void TextGen::lowerColontitul(int pageNum, ostream& out) {
    out << "        " << pageNum << "\n\n";
}

void TextGen::printLine(const pair<string, string>& line, ostream& out) {
    string key = line.first;
    string value = line.second;

    transform(key.begin(), key.end(), key.begin(), 
        [](unsigned char a) {return toupper(a);});
    transform(value.begin(), value.end(), value.begin(), 
        [](unsigned char a) {return tolower(a);});

    out << key << ":" << value << endl;
}

void TextGen::separator(ostream& out) {
    out << "-----------------------\n";
}

int TextGen::linesOnPage() const {
    return 5;
}

void TextGen::generate(const string &inputFile, const string &outputFile) {
    
    ofstream outFile(outputFile);
    Generator::generate(inputFile, outFile);

    outFile.close();
}
#include "Generator.h"

void Generator::parse(const string &input) {

    ifstream inFile(input);
    if (!inFile.is_open()) {
        throw runtime_error("Cannot open input file:" + input);
    }

    data.clear();
    string line;

    while (getline(inFile, line)) {
        int splitter = line.find(':');

        if (splitter == string::npos) {
            continue;
        }

        string key = line.substr(line.find_first_not_of(" "), splitter);
        string value = line.substr(++splitter, line.find_last_not_of(" "));

        data.emplace_back(key, value);
    }
    inFile.close();
}

void Generator::generate(const string &input, ostream &output) {
    parse(input);
    
    int lines = linesOnPage();
    int page = 1;

    for (int i = 0; i < data.size(); i += lines) {

        upperColontitul(page, output);

        for (int j = i; j < i + lines && j < data.size(); ++j) {
            printLine(data[j], output);
            if (j < i + lines - 1 && j < data.size() - 1) {
                separator(output);
            }
        }

        lowerColontitul(page++, output);
    }
}
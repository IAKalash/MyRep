#ifndef GEN_H
#define GEN_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Generator {
protected:
    vector<pair<string, string>> data;

    virtual void upperColontitul(int pageNum, ostream& out) = 0;
    virtual void lowerColontitul(int pageNum, ostream& out) = 0;
    virtual void printLine(const pair<string, string>& entry, ostream& out) = 0;
    virtual void separator(ostream& out) = 0;
    virtual int linesOnPage() const = 0;

    void parse(const string& inputFile);

public:
    virtual ~Generator() = default;
    virtual void generate(const string &input, ostream &output = cout);
};

#endif
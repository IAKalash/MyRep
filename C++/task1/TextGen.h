#ifndef TEXTGEN_H
#define TEXTGEN_H

#include "Generator.h"

class TextGen : public Generator {
protected:

    void upperColontitul(int pageNum, ostream& out) override;
    void lowerColontitul(int pageNum, ostream& out) override;
    void printLine(const pair<string, string>& entry, ostream& out) override;
    void separator(ostream& out) override;
    int linesOnPage() const override;

public:
    void generate(const string& inputFile, const string& outputFile);
};

#endif
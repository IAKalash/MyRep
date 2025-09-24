#ifndef HTMLGEN_H
#define HTMLGEN_H

#include "Generator.h"

class HtmlGen : public Generator {
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
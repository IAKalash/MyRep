#ifndef CONSOLEGEN_H
#define CONSOLEGEN_H

#include "Generator.h"

class ConsoleGen : public Generator {
protected:
    void upperColontitul(int pageNum, ostream& out) override;
    void lowerColontitul(int pageNum, ostream& out) override;
    void printLine(const pair<string, string>& entry, ostream& out) override;
    void separator(ostream& out) override;
    int linesOnPage() const override;
};

#endif
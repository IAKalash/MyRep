#include "ConsoleGen.h"

void ConsoleGen::upperColontitul(int pageNum, ostream& out) {
    return;
}

void ConsoleGen::lowerColontitul(int pageNum, ostream& out) {
    return;
}

void ConsoleGen::printLine(const pair<string, string>& line, ostream& out){
    out << line.first << "-" << line.second << endl;
}

void ConsoleGen::separator(ostream& out) {
    return;
}

int ConsoleGen::linesOnPage() const {
    return 5;
}
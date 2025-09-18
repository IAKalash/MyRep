#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    list<string> lines;
    map<string, int> res;
    int total_words = 0;

    string line;
    while (getline(input, line)) {
        lines.push_back(line);
    }
    input.close();

    for (string l : lines) {
        string word;
        string line = l + " ";
        
        for (char c : line) {
            if (isalnum(c)) {
                word += c;
            } else if (!word.empty()) {
                transform(word.begin(), word.end(), word.begin(), 
                    [](unsigned char a) {return tolower(a);});
                res[word]++;
                total_words++;
                word.clear();
            }
        }
    }

    vector <pair<string, int>> vec;

    copy(res.begin(), res.end(), back_inserter(vec));

    sort(vec.begin(), vec.end(), 
        [](const pair<string, int>& a, const pair<string, int>& b) {return a.second > b.second; });

    output << "Word, Frequency, Frequency (%)\n";
    for (auto [key, value] : vec) {
        output << key << "," << value << "," << float(value)/total_words*100 << "%\n";
    }

    output.close();
    return 0;
}
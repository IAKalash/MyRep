#include <iostream>
#include <math.h>
#include <cctype>
using namespace std;

void eval(int a, int b, int c) {
    double d = b * b - 4 * a * c;
    if (a == 0) {
        cout << "a = 0\n";
        return;
    }
    if (d > 0) {
        d = sqrt(d);
        cout << (-b - d) / (2 * a);
        cout << " ";
        cout << (-b + d) / (2 * a);
        cout << "\n";
        return;
    }
    else if (d == 0) {
        cout << -b / (2 * a);
        cout << "\n";
        return;
    }
    else {
        cout << "No roots\n";
        return;
    }
}

int main() {

    string str;
    int a, b, c;

    cout << "Write three numbers of your quadratic equation\n";
    cout << "(for ex. if your equation is 2X^2 - 4X + 5 = 0 write 2 -4 5)\n";

    cin >> a >> b >> c;

    if (cin.fail()) {
        cout << "Incorrect input\n";
    }
    else {
        eval(a, b, c);
    }

    return 0;
}
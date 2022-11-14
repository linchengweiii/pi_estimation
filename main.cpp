#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>

#include "baker.h"

using namespace std;

class ArgumentParser {
public:
    ArgumentParser() {}

    void add_argument(string key, string default_value) {
        args[key] = default_value;
    }

    void parse_args(int argc, char* argv[]) {
        for (int i = 1; i < argc; i+=2)
            args[argv[i]+1] = argv[i+1];
    }

    string operator[](string key) {
        return args[key];
    }

private:
    unordered_map<string, string> args;
};

bool isCorrect(vector<int>& digits, int index) {
    return digits[index] / 10 == digits[index-1] % (int)(1e8);
}

int maxPrecision(vector<int>& digits) {
    for (int i = 1; i < digits.size(); i++)
        if (!isCorrect(digits, i)) return i-1;
    return digits.size() - 1;
}

void printPI(vector<int>& digits) {
    for (int i = 0; i < digits.size(); i++) {
        if (i == 1) cout << '.';
        cout << (digits[i] / (int)(1e8));
    }
    cout << endl;
}

void bakingPI(int n_precision) {
    vector<int> digits(n_precision+1, 314159265);
    for (int i = 1; i <= n_precision; i++) {
        digits[i] = bake(i);
    }

    int maxp = maxPrecision(digits);
    if (maxp < n_precision) {
        cout << "This program can only handle " << maxp << " precision." << endl;
    } else {
        printPI(digits);
    }
}

int main(int argc, char* argv[]) {
    ArgumentParser args;
    args.add_argument("p", "100000");
    args.parse_args(argc, argv);

    bakingPI(stoi(args["p"]));
}

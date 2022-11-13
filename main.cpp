#include <iostream>
#include <iomanip>
#include <unordered_map>

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


string bakingPI(int n_precision) {
    string pi = "";
    // TODO
    return pi;
}

int main(int argc, char* argv[]) {
    ArgumentParser args;
    args.add_argument("p", "100000");
    args.parse_args(argc, argv);

    string pi = bakingPI(stoi(args["p"]));
    cout << pi.at(0) << '.' << pi.substr(1) << endl;
}

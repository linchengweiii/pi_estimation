#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <unordered_map>

class ArgumentParser {
private:
    std::unordered_map<std::string, std::string> args;

public:
    ArgumentParser() {}

    void add_argument(std::string key, std::string default_value) {
        args[key] = default_value;
    }

    void parse_args(int argc, char* argv[]) {
        for (int i = 1; i < argc; i+=2)
            args[argv[i]+1] = argv[i+1];
    }

    std::string operator[](std::string key) {
        return args[key];
    }
};


#endif // ARGUMENT_PARSER_H

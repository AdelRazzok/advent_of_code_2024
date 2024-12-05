#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

int     get_line_result(const string &line) {
    regex           main_pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    regex           mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    sregex_iterator it(line.begin(), line.end(), main_pattern);
    sregex_iterator end;
    smatch          main_match;
    smatch          mul_match;
    string          instruction;
    bool            is_calculating = true;
    int             sum = 0;

    while (it != end) {
        main_match = *it;
        instruction = main_match.str();

        if (instruction == "do()") {
            is_calculating = true;
        } else if (instruction == "don't()") {
            is_calculating = false;
        } else {
            if (regex_match(instruction, mul_match, mul_pattern) && is_calculating) {
                sum += stoi(mul_match[1].str()) * stoi(mul_match[2].str());
            }
        }
        it++;
    }
    return sum;
}

void    handle_file(ifstream &file) {
    stringstream    buf;
    string          line;
    int             result;

    buf << file.rdbuf();
    line = buf.str();
    result = get_line_result(line);
    cout << "Result: " << result << endl;
}

int     main(int argc, char **argv) {
    ifstream    file;
    string      line;

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    file.open(argv[1], ifstream::in);
    if (!file.is_open()) {
        cerr << "Error: cannot open file " << argv[1] << endl;
        return 1;
    }

    handle_file(file);
    file.close();

    return 0;
}

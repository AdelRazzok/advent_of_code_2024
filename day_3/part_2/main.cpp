#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int     get_line_result(const string &line) {
    regex           main_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    regex           state_pattern(R"(do\(\)|don't\(\))");
    sregex_iterator it(line.begin(), line.end(), main_pattern);
    sregex_iterator end;
    bool            is_calculating = true;
    int             sum = 0;

    while (it != end) {
        smatch match = *it;
        string instruction = match.str();

        if (instruction == "do()") {
            is_calculating = true;
        } else if (instruction == "don't()") {
            is_calculating = false;
        } else {
            smatch mul_match;
            if (regex_match(instruction, mul_match, main_pattern)) {
                int x = stoi(mul_match[1].str());
                int y = stoi(mul_match[2].str());
                if (is_calculating) {
                    sum += x * y;
                }
            }
        }
        ++it;
    }
}

void    handle_file(ifstream &file) {
    string  line;
    int     result = 0;

    while (getline(file, line)) {
        result += get_line_result(line);
    }
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

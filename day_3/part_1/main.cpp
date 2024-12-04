#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int     get_line_result(const string &line) {
    string::const_iterator  it(line.cbegin());
    regex                   pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    smatch                  matches;
    int                     sum = 0;

    while (regex_search(it, line.cend(), matches, pattern)) {
        sum += stoi(matches[1]) * stoi(matches[2]);
        it = matches.suffix().first;
    }
    return sum;
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
